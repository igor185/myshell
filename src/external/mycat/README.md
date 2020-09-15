# Lab 2: mycat 

## Team

 - [Igor Babin](https://github.com/igor185)

## Prerequisites

 - **C++ compiler** - needs to support **C++17** standard
 - **CMake** 3.10+
 
The rest prerequisites (such as development libraries) can be found in the [packages file](./apt_packages.txt) in the form of the apt package manager package names.

## Installing

1. Clone the project.
    ```bash
    git clone https://github.com/igor185/mycat.git
    ```
2. Install required libraries. On Ubuntu:
   ```bash
   sed 's/\r$//' apt_packages.txt | sed 's/#.*//' | xargs sudo apt-get install -y
   ```
3. Build.
    ```bash
    mkdir build
    cmake ./ -G "Unix Makefiles" -Bbuild
    cmake --build build
    ```

## Usage

```bash
./build/mycat [--spec-sym|-A] [--help|-h] <file1> <file2> ... <fileN>    
```

Help flags `-h`/`--help` support is available.
