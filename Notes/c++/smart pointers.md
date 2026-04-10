## Smart Pointers (Modern C++)
Manual memory management (`new` and `delete`) is error-prone. Modern C++ uses **Smart Pointers** from the `<memory>` header to handle memory automatically.

1.  **`std::unique_ptr`**: For exclusive ownership. When the pointer goes out of scope, the memory is deleted automatically.
2.  **`std::shared_ptr`**: For shared ownership. It uses **reference counting**; the memory is only deleted when the last pointer to it is destroyed.
3.  **`std::weak_ptr`**: Used alongside `shared_ptr` to observe an object without increasing its reference count (prevents memory cycles).


Smart pointers are the modern way to handle memory in C++. They are essentially wrappers around raw pointers that follow the **RAII** (Resource Acquisition Is Initialization) principle, ensuring that memory is automatically deallocated when it’s no longer needed.

---

## 1. `std::unique_ptr` (Exclusive Ownership)
A `unique_ptr` strictly "owns" the object it points to. There can only be **one** `unique_ptr` for any given resource.

* **Behavior:** It cannot be copied, only moved. This ensures that only one pointer is responsible for deleting the memory.
* **Performance:** Zero overhead. It is just as fast as a raw pointer.
* **Use Case:** Use this by default for internal class members or local resources.

### Example:
```cpp
#include <iostream>
#include <memory>

struct Player {
    void play() { std::cout << "Playing!" << std::endl; }
};

int main() {
    // Allocation
    std::unique_ptr<Player> p1 = std::make_unique<Player>();
    
    // p1.play(); // Works
    
    // std::unique_ptr<Player> p2 = p1; // ERROR: Cannot copy unique_ptr
    
    std::unique_ptr<Player> p2 = std::move(p1); // Transfer ownership
    // p1 is now null, p2 owns the Player object
    
    if (!p1) std::cout << "p1 is empty." << std::endl;
    p2->play();
} // Memory for Player is automatically deleted here
```

---

## 2. `std::shared_ptr` (Shared Ownership)
A `shared_ptr` allows multiple pointers to point to the same resource. It uses **Reference Counting** to track how many pointers are looking at the object.

* **Behavior:** Every time you copy a `shared_ptr`, the "reference count" increases by 1. When a pointer goes out of scope, the count decreases.
* **Deallocation:** The memory is deleted only when the reference count reaches **zero**.
* **Use Case:** Use this when an object needs to be shared across multiple parts of a system (e.g., a texture used by multiple sprites in a game).



### Example:
```cpp
#include <iostream>
#include <memory>

int main() {
    // Create a shared pointer
    std::shared_ptr<int> s1 = std::make_shared<int>(42);
    
    {
        std::shared_ptr<int> s2 = s1; // Count becomes 2
        std::cout << "Count: " << s1.use_count() << std::endl; // Prints 2
    } // s2 goes out of scope, Count becomes 1
    
    std::cout << "Count: " << s1.use_count() << std::endl; // Prints 1
} // s1 goes out of scope, Count becomes 0, memory is freed
```

---

## 3. The `std::weak_ptr` (The Observer)
If two objects have `shared_ptr`s to each other, they create a **circular dependency**, and the memory will *never* be freed (a memory leak). `weak_ptr` solves this.

* **Behavior:** It points to an object managed by `shared_ptr` but **does not** increase the reference count.
* **Access:** You cannot use it directly; you must convert it back to a `shared_ptr` using `.lock()` to check if the object still exists.



---

## Summary Table for Interviews

| Feature | `unique_ptr` | `shared_ptr` | `weak_ptr` |
| :--- | :--- | :--- | :--- |
| **Ownership** | Sole (Exclusive) | Shared | None (Observer) |
| **Copyable?** | No (Move only) | Yes | Yes |
| **Overhead** | None | Memory for Ref Count | Minimal |
| **Typical Use** | Default choice | Shared resources | Breaking cycles |

**Interview Tip:** Always prefer `std::make_unique` and `std::make_shared` over using the `new` keyword. They are safer and, in the case of `shared_ptr`, more efficient because they perform a single memory allocation for both the object and the control block.

Do you want to see what a "Circular Dependency" looks like in code so you can recognize it during a technical screening?

---

## Common Interview Trap: `const` with Pointers
Pay close attention to where the `const` keyword is placed:
* `const int* ptr`: The **data** is constant. You can't change the value, but you can move the pointer.
* `int* const ptr`: The **pointer** is constant. You can change the value, but the pointer must always point to the same address.
* `const int* const ptr`: **Everything** is constant.

