# Organization

- What is an array?
  - A fixed size, homogeneous linear data structure
  - It is the main data structure that makes programs work
  - int a[5];
  - In c++, you can use std::array<TYPE, SIZE> name;
    - Introduced in c++11
    - Main benefit is that size is passed around rather than a raw pointer without size. Safer.

- Example `std::array<int, 20> a;`
  - Values in a are undefined at this point, so can be anything unless we:
    1. `std::array<int, 20> a = {};` we explicitly initialize with default values
    2. `a.fill(0)` fill after the fact
  - Access via bracket operator: `a[2]`
    - We can be safer with `a.at(2)`, which has bounds checking (safer)
  - Populating it is simple (for loop with `i = 0; i < 20; ++i`)
  - If we set memory past or before the `size`, then are accessing memory we shouldn't. The OS may terminate the program or we may be able to set memory that we shouldn't.
  - We can't change the size without reallocating memory (out of scope)
    - You can use std::vector if you want a homogeneous linear data structure where the size can change

- Problem: If an array isn't full, how do we add to the back of an array?

```c++
void Array::insert_back(int value)
{
    if (size >= capacity)
    {
        throw std::length_error("array is full");
    }

    data[size] = value;
    ++size;
}
```



# Future

- Why is `insert_front` and `remove_front` slow for arrays?
- If the algorithm for `remove_index` and `find` the same for each data structure (same time complexity), why is the runtime not the same?
- What is the worst case for a BST? (input as a sorted array, makes it a linked list)
- Balancing a BST (What if we add everything in a sorted order?)
- Why is `sorted_array` slower than `bst` for `insert_sorted`?
- Why is `remove_back` slow with linked_list tail? This gets us to doubly linked lists
- Why is doubly linked list slower than linked list for `find`, `insert_back`, and `insert_sorted`?
- ...