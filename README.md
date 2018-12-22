# cpp_array
Standard array implemented with all constexpr implementations from up to C++20.

This library implements the class `std::array` in its entirety as is documented on cppreference.com.

The only feature that this library does not implement is `constexpr` for `swap`.

This class is placed inside `namespace ed`.

## Compiler support

This library compiles under following compilers:

GCC 5.1 or newer

- Until version 5.5, you need to provide `std=c++14` flag
- Versions 6.1 and newer do not require any language specific flags

Clang 3.5 or newer

- Until version 6.0.0, you need to provide `std=c++14` flag
- Newer versions do not need to provide any language specific flags

Visual Studio 2017

- Supported from version 19.10(Editor version 15.1) until 19.16(Editor version 15.9.4)
- All future versions of the IDE/compiler are expected to be supported, considering this library doesn't leverage any compiler-specific behaviour
- No need to provide any language specific flags for any compiler version

## Example

```cpp
#include "Array.hpp"

constexpr auto getArr() {
    ed::array<int, 10> ar{};
    ed::array ar2{ 5, 2, 3, 4, 5, 9, 7, 4, 8, 7 };  //Deduction guides, C++17
    auto res = ar < ar2 || ar == ar2;
    ar.fill(55);
    ar[4] = 81 + (res ? 3 : 0);
    return ar;
}

constexpr auto ar = getArr();

#include <iostream>

int main() {
    auto v1 = ar[4];
    auto v2 = ar[6];
    std::cout << v1 << " ";
    std::cout << v2 << "\n";
}
```

Output:

```
84 55
```