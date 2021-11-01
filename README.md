# C3CPP
C++11 wrapper for the compressed-continuous-computation (c3) [library](https://github.com/goroda/compressed-continuous-computation). This is intended to be a very thin wrapper. It has two goals:

1. Provides lifetime management to avoid manual memory allocation and deallocation 
2. To wrap c3 in a namespace to avoid conflicts when using it in C++ code. 

## Installation 

1. Install c3 and cd into the directory
```
git clone https://github.com/goroda/compressed-continuous-computation c3
cd c3
```
2. Build c3 as a static library and hide symbols
```
mkdir build
cd build
cmake -DBUILD_STATIC_LIB:bool=true -DLIB_VISIBILITY_OFF:bool=true ..
make -j4
```
3. Clone c3cpp into a parallel directory with c3
```
git clone https://github.com/goroda/c3cpp
cd c3cpp
```
4. Adjust the compilers and blas/lapack locations in `c3cpp/Makefile` and `tests/Makefile`
5. Run `make all`
6. Check if it works `./c3cpp_tests`


## Struct wrapping and lifetimes

Here we document the status of each wrapped struct. Below we document whether copy and move constructors and assignment operators have been created. For each operation we either implement both constructor and assignment, or neither. The current implementation handles the same usage patterns as the underlying C code. In other words, if there is no copying or moving done in normal usage of C3, then these operations are not supported in C3CPP.


### `struct FunctionTrain` &rarr; FunctionTrain
Operation | Status 
:-------- | :----------
Copy  | :heavy_check_mark:
Move  | :heavy_check_mark:

### `struct OpeOpts` &rarr; OpeOpts
Operation | Status 
:-------- | :----------
Copy  | :x:
Move  | :x:

### `struct OneApproxOpts` &rarr; OneApproxOpts
Operation | Status 
:-------- | :----------
Copy  | :x:
Move  | :x:


### `struct C3Approx` &rarr;  C3Approx
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |

### `struct MultiApproxOpts` &rarr;  MultiApproxOpts

| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |




## LICENSE
BSD-3 

## Author
Alex Gorodetsky alex@alexgorodetsky.com
