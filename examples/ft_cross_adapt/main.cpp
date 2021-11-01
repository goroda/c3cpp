#include <iostream>
#include <vector>
#include <cmath>
#include <assert.h>

#include "c3_cpp.h"

int sin10d(size_t n, const double * x, double * out, void * args)
{
    
    (void)(args);
    for (size_t jj = 0; jj < n; jj++ ){
        out[jj] = 0.0;
        for (size_t ii = 0; ii < 10; ii++){
            out[jj] += x[jj*10+ii];
        }
        out[jj] = sin(out[jj]);        
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

    size_t dim = 10;
    c3::Fwrap fw(dim, "general-vec");
    fw.set_fvec(&sin10d, nullptr);


    double lb = 0.0;
    double ub = 1.0;    
    c3::OpeOpts opts(c3core::LEGENDRE);
    opts.set_lb(lb);
    opts.set_ub(ub);
    
    c3::OneApproxOpts qmopts(opts);    
    c3::C3Approx approx(c3core::CROSS, dim);
    int verbose = 1;
    size_t init_rank = 2;
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

    double intval = ft.integrate();
    double should = -0.62993525905472629935874873250680615583558172687;
    double relerr = fabs(intval-should)/fabs(should);
    assert (relerr < 1e-12);
    
    for (size_t ii = 0; ii < dim; ii++){
        delete[] start[ii];
    }
    delete[] start;



    // TODO:
    // Evaluation and Sobol Indices

    
    // the below should not be possible
    // struct c3core::OpeOpts * opts_c3 = c3core::ope_opts_alloc(c3core::LEGENDRE);

    
}
