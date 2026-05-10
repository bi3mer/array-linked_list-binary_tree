# Arrays, Linked Lists, and Binary Trees

---

## What is an Array?

- Fixed size, homogeneous linear data structure
- Foundation of most programs

---

## Array in C++

```cpp
std::array<int, 5> a{};
```

```
┌───┬───┬───┬───┬───┐
│ 0 │ 0 │ 0 │ 0 │ 0 │
└───┴───┴───┴───┴───┘
  0   1   2   3   4
```

---

## Populating an Array

```cpp
for (int i = 0; i < 5; ++i)
{
    a[i] = (i + 1) * 10;
}
```

---

## Populating an Array

```cpp
for (int i = 0; i < 5; ++i)
{
    a[i] = (i + 1) * 10;
}
```

```
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │ 50 │
└────┴────┴────┴────┴────┘
   0    1    2    3    4
```

---

## What if we want to change the last value?

```cpp
a[4] = 0; // safer -> a.at(4) = 0;
```

```
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │  0 │
└────┴────┴────┴────┴────┘
   0    1    2    3    4
```

---

## What if wanted to change the front of the array, but preserve the rest?

```
┌────┬────┬────┬────┬────┐
│ 10 │ 20 │ 30 │ 40 │  0 │
└────┴────┴────┴────┴────┘
  0    1    2    3    4

Shift right:

┌───┬────┬────┬────┬────┐
│ X │ 10 │ 20 │ 30 │ 40 │
└───┴────┴────┴────┴────┘
  0    1    2    3    4
```

---

## Complexity



---

## `insert_back`

```cpp
void Array::insert_back(int value)
{
  data[size] = value;
  ++size;
}
```

- `size` - number of currently elements in the array
- `capacity` - max number of elements in the array

<br/>
<div class="fragment">
What is the problem with this function?
</div>

---


