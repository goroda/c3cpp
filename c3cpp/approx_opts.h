#ifndef APPROX_OPTS_CPP_H
#define APPROX_OPTS_CPP_H

#include <iostream>
#include "core.h"

namespace c3
{


    class C3Opts
    {

    public:

        enum c3core::function_class fc;
        void *void_opts;
        
        C3Opts(enum c3core::function_class fc): fc(fc) {};
    };

    class OpeOpts : public C3Opts
    {

    public:        
        struct c3core::OpeOpts *opts;
        
        // Note this class must be immediately passed to C3OneApproxOpts,
        // which handles the destruction
        OpeOpts(enum c3core::poly_type ptype);

        void set_lb(double lb);
        void get_lb() const;     
        void set_ub(double ub);
        void get_ub() const;
        void set_start(size_t start);
        void set_nparams(size_t nparams);
        void set_maxnum(size_t maxnum);
        void set_tol(double tol);
    };
        
    class OneApproxOpts
    {

    public:
        // Currently only takes OpeOpts, should ammend this
        struct c3core::OneApproxOpts *opts;
        
        OneApproxOpts(C3Opts &opts_in);
        
        ~OneApproxOpts();

        void set_nparams(size_t nparams);
        void set_maxnum(size_t nparams);
        size_t get_nparams() const;
    };

    class C3Approx
    {

    public:        
        struct c3core::C3Approx * opts;

        C3Approx(enum c3core::C3ATYPE type, size_t dim);

        // Copy Constructor: initialize previously uninitialized
        C3Approx(const C3Approx &other);


        // Copy assignment operator: replace previously initialized
        C3Approx& operator=(const C3Approx &other) =delete ;

        // Move constructor
        C3Approx(C3Approx &&other);

        // Move assignment
        C3Approx& operator=(C3Approx &&other);
            
        ~C3Approx();

        void init_cross(size_t init_rank, int verbose, double **startin);
        void set_round_tol(double tol);
        void set_cross_tol(double tol);
        void set_verbose(int verbosity);
        void set_adapt_kickrank(size_t);
        void set_adapt_maxrank_all(size_t);
        void set_cross_maxiter(size_t);
        void set_approx_opts_dim(size_t dim, const OneApproxOpts &opts);


    };
    
    // This should not handle the memory for multiapprox opts
    class MultiApproxOpts
    {

    public: 
        struct c3core::MultiApproxOpts * opts;
        bool alloc;

        MultiApproxOpts(): opts(nullptr), alloc(false) {};
        MultiApproxOpts(size_t dim);

        MultiApproxOpts(struct c3core::MultiApproxOpts * opts): opts(opts), alloc(false) {};
        
        MultiApproxOpts(const C3Approx & c3approx);

        // The below constructurs employ shallow copies, not deep
        // Copy Constructor: initialize previously uninitialized
        MultiApproxOpts(const MultiApproxOpts &other) = delete;

        // Copy assignment operator: replace previously initialized
        MultiApproxOpts& operator=(const MultiApproxOpts &other) = delete;

        // Move constructor
        MultiApproxOpts(MultiApproxOpts &&other);

        // Move assignment
        MultiApproxOpts& operator=(MultiApproxOpts &&other);

        void set_dim(size_t dim, const OneApproxOpts &opts);
 
        ~MultiApproxOpts();
       
    };


}

#endif
