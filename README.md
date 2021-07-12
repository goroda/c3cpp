# c3cpp
C++11 wrapper for the compressed-continuous-computation (c3) [library](https://github.com/goroda/compressed-continuous-computation)

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

## LICENSE
BSD-3 

## Author
Alex Gorodetsky alex@alexgorodetsky.com
