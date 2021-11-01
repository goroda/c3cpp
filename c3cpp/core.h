#ifndef CORE_C3_CPP_H
#define CORE_C3_CPP_H

namespace c3core
{
    extern "C" {

        enum poly_type      {LEGENDRE, CHEBYSHEV, HERMITE, STANDARD, FOURIER};
        enum C3ATYPE        {CROSS, REGRESS, C3UNSPEC };
        enum function_class {PIECEWISE, POLYNOMIAL, CONSTELM, LINELM, KERNEL};
        enum c3opt_alg      {BFGS, LBFGS, BATCHGRAD, BRUTEFORCE, SGD};
        enum REGTYPE        {ALS,AIO,REGNONE};
        enum REGOBJ         {FTLS,FTLS_SPARSEL2,REGOBJNONE};
        
        struct OpeOpts;        
        struct OneApproxOpts;
        struct MultiApproxOpts;
        struct C3Approx;
        struct FunctionTrain;
        struct Fwrap;
        struct FunctionMonitor;
        struct c3Opt;
        struct FTRegress;
        struct C3SobolSensitivity;
        
        // Not sure about below
        void function_train_sobol_sensitivities(const struct FunctionTrain *,double*,double*,size_t);

        // Done
        struct OpeOpts * ope_opts_alloc(enum poly_type);
        void ope_opts_set_lb(struct OpeOpts *, double);
        double ope_opts_get_lb(const struct OpeOpts *);
        void ope_opts_set_ub(struct OpeOpts *, double);
        double ope_opts_get_ub(const struct OpeOpts *);
        void ope_opts_set_start(struct OpeOpts *, size_t);
        void ope_opts_set_nparams(struct OpeOpts *, size_t);
        void ope_opts_set_maxnum(struct OpeOpts *,size_t);
        void ope_opts_set_tol(struct OpeOpts *, double);
        
        struct OneApproxOpts * one_approx_opts_alloc(enum function_class, void *);
        void one_approx_opts_set_nparams(struct OneApproxOpts *, size_t);
        void one_approx_opts_set_maxnum(struct OneApproxOpts *, size_t);
        size_t one_approx_opts_get_nparams(const struct OneApproxOpts *);
        void one_approx_opts_free_deep(struct OneApproxOpts **);

        
        struct MultiApproxOpts * multi_approx_opts_alloc(size_t);
        void multi_approx_opts_free(struct MultiApproxOpts *);
        void multi_approx_opts_set_dim(struct MultiApproxOpts *,size_t,struct OneApproxOpts *);
        // General approximation options

        struct C3Approx * c3approx_create(enum C3ATYPE, size_t dim);
        void c3approx_destroy(struct C3Approx *);
        void c3approx_set_approx_opts_dim(struct C3Approx *,size_t,
                                          struct OneApproxOpts *);

        //setting cross approximation arguments
        void c3approx_init_cross(struct C3Approx * c3a, size_t init_rank, int verbose,
                                 double ** startin);
        void c3approx_set_round_tol(struct C3Approx *, double);
        void c3approx_set_cross_tol(struct C3Approx *, double);
        void c3approx_set_verbose(struct C3Approx *, int);
        void c3approx_set_adapt_kickrank(struct C3Approx *, size_t);
        void c3approx_set_adapt_maxrank_all(struct C3Approx *, size_t);
        //void c3approx_set_adapt_maxiter(struct C3Approx *, size_t);
        void c3approx_set_cross_maxiter(struct C3Approx *, size_t);
        struct MultiApproxOpts * c3approx_get_approx_args(const struct C3Approx *);


        size_t function_train_get_dim(const struct FunctionTrain *);
        size_t function_train_get_nparams(const struct FunctionTrain *);
        size_t * function_train_get_ranks(const struct FunctionTrain *);
        double function_train_get_avgrank(const struct FunctionTrain *);
        size_t function_train_get_maxrank(const struct FunctionTrain *);

        void function_train_free(struct FunctionTrain *);
        struct FunctionTrain * function_train_copy(const struct FunctionTrain *);
        
        void function_train_scale(struct FunctionTrain *, double);
        
        double function_train_eval(struct FunctionTrain *, const double *);
        double function_train_integrate(const struct FunctionTrain *);
        double function_train_integrate_weighted(const struct FunctionTrain *);

    
        double function_train_inner(const struct FunctionTrain *, 
                                    const struct FunctionTrain * );
        double function_train_inner_weighted(const struct FunctionTrain *, 
                                             const struct FunctionTrain * );

        struct FunctionTrain *
        function_train_integrate_weighted_subset(
            const struct FunctionTrain * ft, size_t ndim_contract,size_t * dims_contract);
        
        struct FunctionTrain * 
        function_train_sum(const struct FunctionTrain *,const struct FunctionTrain *);

        struct FunctionTrain *
        function_train_product(const struct FunctionTrain *, 
                               const struct FunctionTrain *);

        int function_train_save(struct FunctionTrain *,char * filename);

        struct FunctionTrain * c3approx_do_cross(struct C3Approx *,struct Fwrap *,int);
        struct FunctionTrain * function_train_constant(double, struct MultiApproxOpts *);
        struct FunctionTrain *
        function_train_round(struct FunctionTrain *, double,struct MultiApproxOpts *);        

        void c3axpy (double a, struct FunctionTrain *x, struct FunctionTrain **y, double epsilon, struct MultiApproxOpts * opts);
        
        // function wrapping
        struct Fwrap * fwrap_create(size_t, const char *);
        void fwrap_set_fvec(struct Fwrap*,int(*)(size_t,const double*,double*,void*),void*);
        void fwrap_set_f(struct Fwrap * fwrap, double(*f)(const double*,void*),void*arg);
        void fwrap_destroy(struct Fwrap *);

        // function (hashing)
        void function_monitor_free(struct FunctionMonitor *);
        double function_monitor_eval(const double *, void *);
        struct FunctionMonitor * 
        function_monitor_initnd( double (*f)(const double *, void *), void *, size_t dim, size_t table_size);

        // optimizer
        struct c3Opt * c3opt_create(enum c3opt_alg);
        void c3opt_set_relftol(struct c3Opt *, double);
        void c3opt_set_gtol(struct c3Opt *, double);
        void c3opt_set_verbose(struct c3Opt *, int);
        void c3opt_set_maxiter(struct c3Opt *, size_t);
        void c3opt_ls_set_maxiter(struct c3Opt *, size_t);
        void c3opt_set_absxtol(struct c3Opt *, double);
        void c3opt_free(struct c3Opt *);

        // Sobol indices
        struct C3SobolSensitivity *
        c3_sobol_sensitivity_calculate(const struct FunctionTrain * ft, size_t order);
        void c3_sobol_sensitivity_free(struct C3SobolSensitivity * si);
        double c3_sobol_sensitivity_get_variance(const C3SobolSensitivity * sobol);
        double c3_sobol_sensitivity_get_total(const C3SobolSensitivity * sobol, size_t var);
        double c3_sobol_sensitivity_get_interaction(
            const C3SobolSensitivity * sobol, size_t ninteract, const size_t * vars);
        

        
        

        // regression -TODO
        struct FTRegress * ft_regress_alloc(size_t dim, struct MultiApproxOpts *,size_t * ranks);
        size_t ft_regress_get_dim(const struct FTRegress *);
        void ft_regress_set_adapt(struct FTRegress *, int);
        void ft_regress_set_maxrank(struct FTRegress *, size_t);
        void ft_regress_set_kickrank(struct FTRegress *, size_t);
        void ft_regress_set_roundtol(struct FTRegress *, double);
        void ft_regress_set_kfold(struct FTRegress *, size_t);
        void ft_regress_set_finalize(struct FTRegress *, int);
        void ft_regress_set_opt_restrict(struct FTRegress *, int);

        void ft_regress_free(struct FTRegress *);
        void ft_regress_reset_param(struct FTRegress*, struct MultiApproxOpts *, size_t *);
        void ft_regress_set_type(struct FTRegress *, enum REGTYPE);
        void ft_regress_set_obj(struct FTRegress *, enum REGOBJ);
        void ft_regress_set_alg_and_obj(struct FTRegress *, enum REGTYPE, enum REGOBJ);
        void ft_regress_set_stoch_obj(struct FTRegress *, int);

        void ft_regress_set_als_conv_tol(struct FTRegress *, double);
        void ft_regress_set_max_als_sweep(struct FTRegress *, size_t);
        void ft_regress_set_verbose(struct FTRegress *, int);
        void ft_regress_set_regularization_weight(struct FTRegress *, double);
        double ft_regress_get_regularization_weight(const struct FTRegress *);
        double * ft_regress_get_params(struct FTRegress *, size_t *);
        void ft_regress_update_params(struct FTRegress *, const double *);

        void ft_regress_set_seed(struct FTRegress *, unsigned int);

        struct FunctionTrain *
        ft_regress_run(struct FTRegress *,struct c3Opt *,size_t,const double* xdata, const double * ydata);
    }


}

#endif
