## 🔗 Why Your C Code Compiles But Won't Link: A Classic Gotcha

https://www.linkedin.com/in/david-zhu-3a68a855/recent-activity/all/


Ever had code that compiles perfectly but explodes during linking? Here's a real-world example that trips up even experienced developers:
The Scenario 🎯

You're implementing optimized memory operations for a performance-critical system. You write:

```
void* fast_memcpy(void* dest, const void* src, size_t n) 
{ 
/* your implementation */ 
}
void* fast_memset(void* ptr, int value, size_t n)
 { 
/* your implementation */
 }
```

**Result:** ✅ Compiles successfully, ❌ Links with errors like "unresolved external symbol memcpy"

Why This Happens 🤔

**Compilation Phase:** The 𝐜𝐨𝐦𝐩𝐢𝐥𝐞𝐫 only cares about 𝐬𝐲𝐧𝐭𝐚𝐱 𝐚𝐧𝐝 𝐬𝐞𝐦𝐚𝐧𝐭𝐢𝐜𝐬. Your fast_memcpy and fast_memset functions are 𝐩𝐞𝐫𝐟𝐞𝐜𝐭𝐥𝐲 𝐯𝐚𝐥𝐢𝐝 𝐂 𝐜𝐨𝐝𝐞.

**Linking Phase:** The linker tries to resolve symbol references. Standard libraries and other code expect functions named exactly memcpy, memset, and memmove - not your custom names.

The Fix 🛠️

Provide wrapper functions with the expected names:

```
void* memcpy(void* dest, const void* src, size_t n) {
 return fast_memcpy(dest, src, n);
}
```
```
void* memset(void* ptr, int value, size_t n) {
 return fast_memset(ptr, value, n);
}
```
Key Takeaway 💡

𝐂𝐨𝐦𝐩𝐢𝐥𝐚𝐭𝐢𝐨𝐧 𝐬𝐮𝐜𝐜𝐞𝐬𝐬 ≠ 𝐋𝐢𝐧𝐤 𝐬𝐮𝐜𝐜𝐞𝐬𝐬

```
The compiler checks syntax and generates object code.
The linker resolves symbols across modules. Both must succeed for a working executable.
This distinction is crucial when working with:
Third-party libraries expecting specific function names
Custom implementations of standard library functions
Performance-optimized versions of common operations
Complex build systems with multiple translation units
Have you encountered similar linking mysteries? Share your war stories! 👇
```
<img width="800" height="604" alt="image" src="https://github.com/user-attachments/assets/56c6dbbd-3bc6-469b-85ba-b12099b33732" />
