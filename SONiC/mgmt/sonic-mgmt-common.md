https://deepwiki.com/sonic-net/sonic-mgmt-common

The sonic-mgmt-common repository is organized as a layered architecture with clear separation of concerns. The following diagram illustrates the high-level architecture and the interaction between key components:


![[Pasted image 20260108144544.png]]

![[Pasted image 20260108144659.png]]

### TransLib (Transaction Library)

TransLib serves as the primary entry point for client applications, handling data management operations such as Create, Read, Update, and Delete (CRUD). It provides a common application framework with features like transaction management, data translation, and validation.

### Transformers

Transformers handle bidirectional translation between YANG data models and Redis database format. This includes:

- Field transformers
- Key transformers
- Table transformers
- Subtree transformers

### YANG Models

YANG models define the configuration and state data structures, enabling:

- Schema-based validation
- Standard data representation
- Machine-readable interface definitions

```bash

dipankarpal@AZUHPS-SONIC-01:/work/users/dipankarpal/sonic-buildimage/src/sonic-mgmt-common/models/yang/sonic$ ls
common  import.mk  sonic-acl.yang  sonic-interface.yang  sonic-port.yang  sonic-show-techsupport.yang
dipankarpal@AZUHPS-SONIC-01:/work/users/dipankarpal/sonic-buildimage/src/sonic-mgmt-common/models/yang/sonic$

```

Refer to this tree from all sonic YANGS: dipankarpal@AZUHPS-SONIC-01:/work/users/dipankarpal/sonic-buildimage/src/sonic-mgmt-common/models/yang$ vi **sonic_allyangs.tree**

### CVL (Configuration Validation Library)

CVL validates configuration data against YANG models to ensure syntactic and semantic correctness before committing changes to the database. It supports various validation types including:

- Syntax validation (data types, ranges, patterns)
- Semantic validation (dependencies, constraints)
- Custom validation hooks for platform-specific requirements

### DB Layer

The DB layer provides a unified abstraction over Redis, handling operations like:

- Table and entry management
- Transaction processing
- Subscription for configuration changes
- Database caching

Its like external request will go to management framework first and reach mgmt-common then via application routing then the application will call these DB layer to access the actual DBs


- **Translib**: sonic-buildimage/src/sonic-mgmt-common/translib
- **Transformer**: sonic-buildimage/src/sonic-mgmt-common/translib/transformer$
- **DB layer**: sonic-buildimage/src/sonic-mgmt-common/translib/db$
- **CVL**: sonic-buildimage/src/sonic-mgmt-common/cvl



