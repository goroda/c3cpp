# C3CPP
C++11 wrapper for the compressed-continuous-computation (c3) [library](https://github.com/goroda/compressed-continuous-computation). This is intended to be a very thin wrapper. It has two goals:

1. Provide lifetime management to avoid manual memory allocation and deallocation.
2. Wrap c3 in a namespace to avoid conflicts when using it in C++ code. 

## Installation 

### Prerequisites

The external pre-requisites are any BLAS and LAPACK implmentation

### C3 and C3CPP installation instructions

1. Install c3 and ~cd~ into the directory
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
3. Clone c3cpp 
```
git clone https://github.com/goroda/c3cpp
cd c3cpp
```
5. Create a build subdirectory and run CMake
```
mkdir build
cd build
cmake -DC3_LIB_PATH=<enter_path> ..
make -j4
```
6. Run the examples in `build/examples`

## Examples and tests

Examples are provided in the `examples` subdirectory. Here we describe some of the main ideas

### `ft_cross_adapt`

This example provides the basic approach to generating an approximation to a blackbox function. The code is developed to wrap functions with the following signature

```
int sin10d(size_t n, const double * x, double * out, void * args)
```
where `n` is the number of evaluations, `x` is an (n,d) array that is flattened in row-order denoting the locations at which to evaluate the function, `out` is the (n,) array at which to write the outputs, and `args` is a void pointer containing any extra arguments you need.

#### Step 1: wrap the function in an `Fwrap`
Here we take the sin function and wrap it in a class that C3 will understand.
```
size_t dim = 10;
c3::Fwrap fw(dim, "general-vec");
fw.set_fvec(&sin10d, nullptr);
```
#### Step 2: setup the univariate approximation arguments
Here we specify that each dimension will be approximated using Legendre polynomials.
```
double lb = 0.0;
double ub = 1.0;
c3::OpeOpts opts(c3core::LEGENDRE);
opts.set_lb(lb);
 opts.set_ub(ub);
```

#### Step 3: setup the multivariate approximation arguments
Here we simultaneously assign the options above to each dimension, and provide a linearly spaced set of points of size `init_rank` at which to begin the sampling
```
    c3::OneApproxOpts qmopts(opts);
    c3::C3Approx approx(c3core::CROSS, dim);
    int verbose = 1;
    size_t init_rank = 2;
    double ** start = new double*[dim];
    for (size_t ii = 0; ii < dim; ii++) {
        start[ii] = new double[dim];
        linspace(lb, ub, init_rank, start[ii]);
        approx.set_approx_opts_dim(ii, qmopts);
    }
```

#### Step 4: Initialize the cross approximation arguments
We initialize with the samples located in `start` and set some tolerances
```
    approx.init_cross(init_rank, verbose, start);
    approx.set_cross_tol(1e-5);
    approx.set_cross_maxiter(10);
 ```
 
#### Step 5: Generate the approximation
This is one function call to the `FunctionTrain` constructor
```
    c3::FunctionTrain ft(approx, fw, 0);
```

#### Step 6: Computation
Now we are ready to compute with the function train. This particular example
performs integration
```
double intval = ft.integrate();
```



### Available functions for computation

The following getters and computers are available for the `FunctionTrain` class.
```
// Getters
        size_t get_dim() const;
        size_t get_nparams() const;
        size_t *get_ranks() const;
        double get_avgrank() const;
        double get_maxrank() const;
        
// Computers
        FunctionTrain &scale(double val);
        double eval(const double * pt) const;
        double integrate() const;
        double integrate_weighted() const;
        double inner(const FunctionTrain &other) const;
        double inner_weighted(const FunctionTrain &other) const;
        FunctionTrain sum(const FunctionTrain &other) const;
        FunctionTrain product(const FunctionTrain &other) const;
        FunctionTrain integrate_weighted_subset(size_t ndim_contract, size_t *dims_contract) const;

        int save(std::string filename) const;

        // this = a * x + this
        void axpy(double a, const FunctionTrain & x, double epsilon, const MultiApproxOpts &opts);
```
    


## Namespaces

This wrapper provides two namespaces

1. `c3` which provides the C++ wrappers, in `c3_cpp.h`
2. `c3core` which provides the C signatures for the wrapped functions, in `core.h`

## Struct wrapping and lifetimes

Here we document the status of each wrapped struct. Below we document whether copy and move constructors and assignment operators have been created. For each operation we either implement both constructor and assignment, or neither. The current implementation handles the same usage patterns as the underlying C code. In other words, if there is no copying or moving done in normal usage of C3, then these operations are not supported in C3CPP.

In the tables below we also provide the /public/ member variable that provides the raw pointer to the unwrapped struct. This is useful if one wants to call functions that have not yet been wrapped.


### `struct FunctionTrain` &rarr; `FunctionTrain`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :heavy_check_mark: |
| Move      | :heavy_check_mark: |
| var name  | `ft`               |


### `struct OpeOpts` &rarr; `OpeOpts`
| Operation | Status |
|-----------|--------|
| Copy      | :x:    |
| Move      | :x:    |
| var name  | `opts` |

### `struct OneApproxOpts` &rarr; `OneApproxOpts`
| Operation | Status |
|-----------|--------|
| Copy      | :x:    |
| Move      | :x:    |
| var name  | `opts` |

### `struct C3Approx` &rarr;  `C3Approx`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |
| var name  | `opts`             |

### `struct MultiApproxOpts` &rarr;  `MultiApproxOpts`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |
| var name  | `opts`             |


### `struct Fwrap` &rarr;  `Fwrap`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |
| var name  | `fwrap`            |

### `struct FunctionMonitor` &rarr;  `FunctionMonitor`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |
| var name  | `monitor`          |


### `struct C3Opt` &rarr;  `C3Opt`
| Operation | Status |
|-----------|--------|
| Copy      | :x:    |
| Move      | :x:    |
| var name  | `opt`  |

### `struct C3SobolSensitivity` &rarr;  `SobolIndices`
| Operation | Status             |
|-----------|--------------------|
| Copy      | :x:                |
| Move      | :heavy_check_mark: |
| var name  | `sobol`            |

## LICENSE
BSD-3 

## Author
Alex Gorodetsky alex@alexgorodetsky.com
