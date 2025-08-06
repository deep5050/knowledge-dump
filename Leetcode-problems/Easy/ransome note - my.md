```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

bool func(string ran, string mag)
{
    map<char, int> memory;
    size_t i = 0;
    for (char c : mag) memory[c[[remove more than 2 duplicates]]]++;
    for (i; i < ran.length(); i++)
    {
        if (memory.find(ran[i]) != memory.end())
        {
            if (memory[ran[i]] == 0) return false;
            memory[ran[i]]--;
        }
        else return false;
    }
    if (i == ran.length()) return true;
    else return false;
}

int main()
{
    string ransome = "a";
    string magazine = "ba";
    if (func(ransome, magazine)) cout << "OK" << endl;
    else cout << "NOT OK" << endl;
    return 0;
}
```

**PS: Internet tells a different solution. i don’t know why !! this works just fine**
