# Myshell

## Team

 - [Igor Babin](https://github.com/igor185)

## Prerequisites

 - **C++ compiler** - needs to support **C++17** standard
 - **CMake** 3.15+
 
The rest prerequisites (such as development libraries) can be found in the [packages file](./apt_packages.txt) in the form of the apt package manager package names.

## Installing

1. Build to ./build/myshell. With -r run after build 
    ```bash
    bash ./scripts/build.sh -r
    ```
Run tests: 

    ./build/myshell ./scripts/run_tests.msh
