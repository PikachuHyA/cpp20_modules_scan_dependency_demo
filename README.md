# cpp20_modules_scan_dependency_demo

This repo show how to scan C++20 Modules dependencies with different compiler.

I prepare `foo.cppm` which provide a named module `foo` and an entry `demo.cc` which consume the module `foo`.

- foo.cppm
```
module;
#include <iostream>
export module foo;

export void hello() {
    std::cout << "Hello from C++20 Modules foo" << std::endl;
}
```

- demo.cc

```
import foo;

int main() {
    hello();
    return 0;
}
```

you can see the result from the [CI (GitHub Action)](https://github.com/PikachuHyA/cpp20_modules_scan_dependency_demo/actions)

## Clang

use `clang-scan-deps -format=p1689 -- clang xxx`

```
clang-scan-deps-17 -format=p1689 -- clang++-17 -c -std=c++20 -MD -MF demo.cc.d demo.cc -o demo.o
clang-scan-deps-17 -format=p1689 -- clang++-17 -c -std=c++20 -MD -MF foo.cppm.d foo.cppm -o foo.o
```

the result of scanning `demo.cc`
```
{
    "revision": 0,
    "rules": [
        {
            "primary-output": "demo.o",
            "requires": [
                {
                    "logical-name": "foo"
                }
            ]
        }
    ],
    "version": 1
}
```
the result of scanning `foo.cppm`

```
{
    "revision": 0,
    "rules": [
        {
            "primary-output": "foo.o",
            "provides": [
                {
                    "is-interface": true,
                    "logical-name": "foo",
                    "source-path": "foo.cppm"
                }
            ]
        }
    ],
    "version": 1
}
```

see also `.github/workflows/clang.yml`


## MSVC

use `cl /std:c++latest /scanDependencies- xxx`

```
cl /std:c++latest /scanDependencies- demo.cc /Fodemo.obj
cl /std:c++latest /scanDependencies- /TP foo.cppm /ifcOutput foo.pcm /Fofoo.obj
```

the result of scanning `demo.cc`
```
{
    "version": 1,
    "revision": 0,
    "rules": [
        {
            "primary-output": "demo.obj",
            "outputs": [
                "-"
            ],
            "requires": [
                {
                    "logical-name": "foo"
                }
            ]
        }
    ]
}
```
the result of scanning `foo.cppm`

```
{
    "version": 1,
    "revision": 0,
    "rules": [
        {
            "primary-output": "foo.obj",
            "outputs": [
                "-",
                "foo.pcm"
            ],
            "provides": [
                {
                    "logical-name": "foo",
                    "source-path": "d:\\a\\cpp20_modules_scan_dependency_demo\\cpp20_modules_scan_dependency_demo\\foo.cppm",
                    "is-interface": true
                }
            ],
            "requires": []
        }
    ]
}
```


see also `.github/workflows/msvc.yml`

## GCC
TODO

(I failed to install GCC 14.)

## References

- Clang [Standard C++ Modules](https://clang.llvm.org/docs/StandardCPlusPlusModules.html)
- MSVC [Using C++ Modules in MSVC from the Command Line Part 1: Primary Module Interfaces](https://devblogs.microsoft.com/cppblog/using-cpp-modules-in-msvc-from-the-command-line-part-1/)
- [import CMake; C++20 Modules](https://www.kitware.com/import-cmake-c20-modules/)
