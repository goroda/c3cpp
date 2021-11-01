#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

#include "c3_cpp.h"


int rosenbrock(size_t N, const double * x, double * out, void * args)
{
    (void)(args);
    for (size_t ii = 0; ii < N; ii++){
        out[ii] = 100.0 * pow( x[ii*2 + 1] - pow(x[ii*2],2), 2) + pow(1.0-x[ii*2],2);
    }
    return 0;
}

void linspace(double lb, double ub, size_t num, double *out)
{
    double dt = (ub - lb) / static_cast<double>(num-1);
    out[0] = lb;
    for (size_t ii = 1; ii < num; ii++){
        out[ii] = lb + dt * ii;
    }
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    size_t dim = 2;
    c3::Fwrap fw(dim, "general-vec");
    fw.set_fvec(&rosenbrock, nullptr);


    double lb = -2.0;
    double ub = 2.0;    
    c3::OpeOpts opts(c3core::LEGENDRE);
    opts.set_lb(lb);
    opts.set_ub(ub);
    
    c3::OneApproxOpts qmopts(opts);    
    c3::C3Approx approx(c3core::CROSS, dim);
    int verbose = 0;
    size_t init_rank = 5;
    double ** start = new double*[dim];
    for (size_t ii = 0; ii < dim; ii++) {
        start[ii] = new double[init_rank];
        linspace(lb, ub, init_rank, start[ii]);
        approx.set_approx_opts_dim(ii, qmopts);
    }
    approx.init_cross(init_rank, verbose, start);
    approx.set_cross_tol(1e-5);
    approx.set_cross_maxiter(10);

    c3::FunctionTrain ft(approx, fw, 1);

    c3::SobolIndices sobol(ft, dim);

    double var = sobol.get_variance();
    
    assert(std::fabs(7.0363551328e-01 - sobol.get_total_effect(0)) < 1e-9);
    assert(std::fabs(5.0253108617e-01 - sobol.get_total_effect(1)) < 1e-9);

    size_t main_effect = 0;
    assert(std::fabs(4.9746891383e-01 - sobol.get_interaction(1, &main_effect)/var) <  1e-9);

    main_effect = 1;
    assert(std::fabs(2.9636448672e-01 - sobol.get_interaction(1, &main_effect)/var) <  1e-9);    
    
    size_t main_effects[2] = {0,1};
    assert(std::fabs(2.0616659946e-01 - sobol.get_interaction(2, main_effects)/var) < 1e-9);
    
                      
    for (size_t ii = 0; ii < dim; ii++){
        delete[] start[ii];
    }
    delete[] start;



    // TODO:
    // Evaluation and Sobol Indices

    
    // the below should not be possible
    // struct c3core::OpeOpts * opts_c3 = c3core::ope_opts_alloc(c3core::LEGENDRE);

    
}
