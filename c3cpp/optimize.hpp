#ifndef C3_OPTIMIZE_H
#define C3_OPTIMIZE_H

#include <iostream>
#include "core.h"

namespace c3
{
    class C3Opt {

        struct c3core::c3Opt * opt;
    public:

        C3Opt(enum c3core::c3opt_alg alg);
        
        // delete default constructors
        C3Opt(const C3Opt &other)             =delete;
        C3Opt& operator=(const C3Opt &other)  =delete;
        C3Opt(const C3Opt &&other)            =delete;
        C3Opt& operator=(const C3Opt &&other) =delete;

        ~C3Opt();

        void set_relftol(double val);
        void set_gtol(double val);
        void set_verbose(int verbosity);
        void set_maxiter(size_t maxiter);
        void ls_set_maxiter(size_t maxiter);
        void set_absxtol(double tol);
        
    };
}

#endif
