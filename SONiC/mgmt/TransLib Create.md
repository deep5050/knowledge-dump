https://deepwiki.com/search/explain-func-createreq-setrequ_2752a289-d762-478a-adf8-f7854bf52565

https://deepwiki.com/search/explain-func-createreq-setrequ_2752a289-d762-478a-adf8-f7854bf52565

https://deepwiki.com/search/explain-func-createreq-setrequ_2752a289-d762-478a-adf8-f7854bf52565


![[Pasted image 20260106125035.png]]

## TransLib Create Function - Complete CRUD Operation Flow
Complete flow of TransLib's Create function from authorization through database commit. Key phases include security validation [1a], YANG-to-Redis transformation [3c], transaction management [4a], and actual Redis operations [5c].
### 1. Authorization and Request Validation
Initial security check and request preprocessing before database operations
### 1a. Authorization Check (`translib.go:161`)
Validates user permissions for Create operation
```text
if !isAuthorizedForSet(req) {
```
### 1b. App Module Selection (`translib.go:171`)
Finds appropriate handler based on path and version
```text
app, appInfo, err := getAppModule(path, req.ClientVersion)
```
### 1c. App Initialization (`translib.go:178`)
Sets up app module with request data and operation type
```text
err = appInitialize(app, appInfo, path, &payload, nil, CREATE)
```
### 2. Concurrency Control and Database Setup
Thread safety mechanisms and Redis connection establishment
### 2a. Write Lock Acquisition (`translib.go:185`)
Ensures thread safety for write operations
```text
writeMutex.Lock()
```
### 2b. Database Connection (`translib.go:188`)
Creates connection to Redis ConfigDB
```text
d, err := db.NewDB(getDBOptions(db.ConfigDB))
```
### 2c. Cleanup Registration (`translib.go:195`)
Ensures database connection cleanup
```text
defer d.DeleteDB()
```
### 3. YANG to Database Translation
Transforms YANG-based request into Redis database operations
### 3a. Translation Initiation (`translib.go:197`)
Starts YANG-to-DB translation process
```text
keys, err = (*app).translateCreate(d)
```
### 3b. Common Translation Handler (`common_app.go:99`)
Delegates to shared translation logic
```text
keys, err = app.translateCRUDCommon(d, CREATE)
```
### 3c. Core Transformation (`common_app.go:578`)
Performs actual YANG to Redis mapping via transformer
```text
result, defValMap, auxMap, err := transformer.XlateToDb(app.pathInfo.Path, opcode, d, (*app).ygotRoot, (*app).ygotTarget, (*app).body, txCache, &app.skipOrdTableChk)
```
### 3d. Watch Key Generation (`common_app.go:630`)
Creates keys for transaction monitoring
```text
keys, err = app.generateDbWatchKeys(d, false)
```
### 4. Transaction Management
Database transaction lifecycle with proper error handling
### 4a. Transaction Start (`translib.go:204`)
Begins Redis transaction with watch keys
```text
err = d.StartTx(keys, appInfo.tablesToWatch)
```
### 4b. Create Processing (`translib.go:211`)
Executes actual database create operations
```text
resp, err = (*app).processCreate(d)
```
### 4c. Transaction Abort (`translib.go:214`)
Rolls back transaction on error
```text
d.AbortTx()
```
### 4d. Transaction Commit (`translib.go:219`)
Commits successful transaction to database
```text
err = d.CommitTx()
```
### 5. Database Operation Execution
Low-level Redis operations with proper ordering and validation
### 5a. Common Processing (`common_app.go:367`)
Delegates to shared processing logic
```text
if err = app.processCommon(d, CREATE); err != nil {
```
### 5b. CRU Operation Handler (`common_app.go:653`)
Handles Create/Update/Replace database operations
```text
err = app.cmnAppCRUCommonDbOpn(d, CREATE, app.cmnAppTableMap[CREATE][db.ConfigDB])
```
### 5c. Redis Create Entry (`common_app.go:761`)
Creates actual entry in Redis database
```text
err = d.CreateEntry(cmnAppTs, db.Key{Comp: []string{tblKey}}, tblRw)
```
### 6. Error Handling and Response
Comprehensive error management with source tracking
### 6a. Protocol Error (`translib.go:174`)
Marks errors from infrastructure layer
```text
resp.ErrSrc = ProtoErr
```
### 6b. Application Error (`translib.go:181`)
Marks errors from application logic
```text
resp.ErrSrc = AppErr
```
### 6c. Response Return (`translib.go:225`)
Returns final response with error information
```text
return resp, err
```


## Database Entry Handling in TransLib

The actual database entry creation is handled by the **DB layer's `CreateEntry` method**, which is called from the CommonApp's processing logic [1](#3-0) . The `db.NewDB(getDBOptions(db.ConfigDB))` call creates a new Redis database connection specifically configured for the ConfigDB with proper separators and options [2](#3-1) .

---

## Detailed Flow

### Who Handles Database Entry Creation

1. **TransLib Create function** calls `(*app).processCreate(d)` [3](#3-2) 
2. **CommonApp.processCreate()** delegates to `processCommon()` [4](#3-3) 
3. **processCommon()** calls `cmnAppCRUCommonDbOpn()` for CREATE operations [5](#3-4) 
4. **CRU handler** eventually calls `d.CreateEntry()` to create the actual Redis entry [1](#3-0) 

The `CreateEntry` method in the DB struct is the final handler that writes to Redis [6](#3-5) .

### What `db.NewDB(getDBOptions(db.ConfigDB))` Does

This function performs several key operations:

1. **Creates Redis Client**: Establishes a connection to Redis using `redis.NewClient()` [7](#3-6) 
2. **Sets Database Options**: Configures connection parameters including:
   - Database number (ConfigDB = 4) [8](#3-7) 
   - Table name separator ("|") [9](#3-8) 
   - Key separator ("|") [9](#3-8) 
3. **Initializes Internal State**: Sets up transaction state, command buffers, and CVL validation structures [10](#3-9) 
4. **Validates Configuration**: Checks for incompatible options (like cache with onChange) [11](#3-10) 

The `getDBOptions()` function specifically returns options tailored for ConfigDB with pipe separators, which is the standard format for SONiC configuration data [12](#3-11) .

## Notes

- The DB layer provides an abstraction over Redis, mimicking sonic-py-swsssdk for easier porting from Python [13](#3-12) 
- All database operations are transactional to ensure atomicity and data consistency
- The ConfigDB (database 4) is specifically used for configuration storage in SONiC [14](#3-13) 

Wiki pages you might want to explore:
- [Overview (sonic-net/sonic-mgmt-common)](/wiki/sonic-net/sonic-mgmt-common#1)

### Citations

**File:** translib/common_app.go (L360-372)
```go
func (app *CommonApp) processCreate(d *db.DB) (SetResponse, error) {
	var err error
	var resp SetResponse

	log.Info("processCreate:path =", app.pathInfo.Path)
	targetType := reflect.TypeOf(*app.ygotTarget)
	log.Infof("processCreate: Target object is a <%s> of Type: %s", targetType.Kind().String(), targetType.Elem().Name())
	if err = app.processCommon(d, CREATE); err != nil {
		log.Warning(err)
		resp = SetResponse{ErrSrc: AppErr}
	}

	return resp, err
```

**File:** translib/common_app.go (L652-653)
```go
	if _, ok := app.cmnAppTableMap[CREATE][db.ConfigDB]; ok {
		err = app.cmnAppCRUCommonDbOpn(d, CREATE, app.cmnAppTableMap[CREATE][db.ConfigDB])
```

**File:** translib/common_app.go (L761-765)
```go
						err = d.CreateEntry(cmnAppTs, db.Key{Comp: []string{tblKey}}, tblRw)
						if err != nil {
							log.Warning("CREATE case - d.CreateEntry() failure")
							return err
						}
```

**File:** translib/db/db.go (L20-26)
```go
/*
Package db implements a wrapper over the go-redis/redis.

There may be an attempt to mimic sonic-py-swsssdk to ease porting of
code written in python using that SDK to Go Language.

Example:
```

**File:** translib/db/db.go (L140-148)
```go
	ConfigDB                   // 4
	FlexCounterDB              // 5
	StateDB                    // 6
	SnmpDB                     // 7
	ErrorDB                    // 8
	EventDB                    // 9
	// All DBs added above this line, please ----
	MaxDB //  The Number of DBs
)
```

**File:** translib/db/db.go (L388-410)
```go
func NewDB(opt Options) (*DB, error) {

	var e error

	if glog.V(3) {
		glog.Info("NewDB: Begin: opt: ", opt)
	}

	// Time Start
	var now time.Time
	var dur time.Duration
	now = time.Now()

	d := DB{client: redis.NewClient(adjustRedisOpts(&opt)),
		Opts:              &opt,
		txState:           txStateNone,
		txCmds:            make([]_txCmd, 0, InitialTxPipelineSize),
		cvlEditConfigData: make([]cmn.CVLEditConfigData, 0, InitialTxPipelineSize),
		dbStatsConfig:     getDBStatsConfig(),
		stats:             DBStats{Tables: make(map[string]Stats, InitialTablesCount), Maps: make(map[string]Stats, InitialMapsCount)},
		dbCacheConfig:     getDBCacheConfig(),
		cache:             dbCache{Tables: make(map[string]Table, InitialTablesCount), Maps: make(map[string]MAP, InitialMapsCount)},
	}
```

**File:** translib/db/db.go (L418-428)
```go
	if opt.IsCacheEnabled && opt.IsOnChangeEnabled {
		glog.Error("Per Connection cache cannot be enabled with OnChange cache")
		glog.Error("Disabling Per Connection caching")
		opt.IsCacheEnabled = false
	}

	if opt.IsOnChangeEnabled && !opt.IsWriteDisabled {
		glog.Errorf("NewDB: IsEnableOnChange cannot be set on write enabled DB")
		e = tlerr.TranslibDBCannotOpen{}
		goto NewDBExit
	}
```

**File:** translib/db/db.go (L1335-1343)
```go
// CreateEntry creates an entry(row) in the table.
func (d *DB) CreateEntry(ts *TableSpec, key Key, value Value) error {

	if !d.IsOpen() {
		return ConnectionClosed
	}

	return d.setEntry(ts, key, value, true)
}
```

**File:** translib/translib.go (L211-217)
```go
	resp, err = (*app).processCreate(d)

	if err != nil {
		d.AbortTx()
		resp.ErrSrc = AppErr
		return resp, err
	}
```

**File:** translib/transformer/xlate_utils.go (L617-628)
```go
func getDBOptions(dbNo db.DBNum) db.Options {
	var opt db.Options

	switch dbNo {
	case db.ApplDB, db.CountersDB, db.FlexCounterDB, db.AsicDB:
		opt = getDBOptionsWithSeparator(dbNo, "", ":", ":")
	case db.ConfigDB, db.StateDB:
		opt = getDBOptionsWithSeparator(dbNo, "", "|", "|")
	}

	return opt
}
```
