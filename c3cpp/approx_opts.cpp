#include <iostream>

#include "core.h"
#include "c3_cpp.h"

#include "utils.h"

using namespace c3;

c3::OpeOpts::OpeOpts(enum c3core::poly_type ptype) : C3Opts(c3core::POLYNOMIAL) {
    opts = c3core::ope_opts_alloc(ptype);
    void_opts = opts;
}

void c3::OpeOpts::set_lb(double lb) {
    c3core::ope_opts_set_lb(opts, lb);
}

void c3::OpeOpts::get_lb() const {
    c3core::ope_opts_get_lb(opts);
}                        

void c3::OpeOpts::set_ub(double ub) {
    c3core::ope_opts_set_ub(opts, ub);
}
        
void c3::OpeOpts::get_ub() const {
    c3core::ope_opts_get_ub(opts);
}

void c3::OpeOpts::set_start(size_t start) {
    c3core::ope_opts_set_start(opts, start);
}

void c3::OpeOpts::set_nparams(size_t nparams) {
    c3core::ope_opts_set_nparams(opts, nparams);
}        

void c3::OpeOpts::set_maxnum(size_t maxnum) {
    c3core::ope_opts_set_maxnum(opts, maxnum);
}        
        
void c3::OpeOpts::set_tol(double tol) {
    c3core::ope_opts_set_tol(opts, tol);
}        


c3::OneApproxOpts::OneApproxOpts(C3Opts &opts_in) {
    opts = c3core::one_approx_opts_alloc(opts_in.fc, opts_in.void_opts);
}
c3::OneApproxOpts::~OneApproxOpts() {
    if (opts != nullptr) {
        c3core::one_approx_opts_free_deep(&opts);
    }
}

void c3::OneApproxOpts::set_nparams(size_t nparams) {
    c3core::one_approx_opts_set_nparams(opts, nparams);
}

void c3::OneApproxOpts::set_maxnum(size_t nparams) {
    c3core::one_approx_opts_set_maxnum(opts, nparams);
}        

size_t c3::OneApproxOpts::get_nparams() const {
    return c3core::one_approx_opts_get_nparams(opts);
}

c3::MultiApproxOpts::MultiApproxOpts(size_t dim) {
    opts = c3core::multi_approx_opts_alloc(dim);
    alloc = true;
}

c3::MultiApproxOpts::MultiApproxOpts(const C3Approx & c3approx) : alloc(false)
{
    opts = c3core::c3approx_get_approx_args(c3approx.opts);
}


// // Copy Constructor: initialize previously uninitialized
// c3::MultiApproxOpts::MultiApproxOpts(const c3::MultiApproxOpts &other) {
//     opts = other.opts;
//     alloc = false;
// }


// // Copy assignment operator: replace previously initialized
// c3::MultiApproxOpts& MultiApproxOpts::operator=(const c3::MultiApproxOpts &other){

//     if (alloc == true) {
//         c3core::multi_approx_opts_free(opts);
//         alloc = false;
//     }
//     opts = other.opts;
//     return *this;
// }

// Move constructor
c3::MultiApproxOpts::MultiApproxOpts(c3::MultiApproxOpts &&other) {
    // std::cout << "MultiApproxOpts Move" << std::endl;
    opts = other.opts;
    other.opts = nullptr;
}

// Move assignment
c3::MultiApproxOpts& MultiApproxOpts::operator=(c3::MultiApproxOpts &&other) {
    // std::cout << "MultiApproxOpts Move Assignment" << std::endl;
    if (this != &other) {
        if (alloc == true) {
            c3core::multi_approx_opts_free(opts);
        }
        opts = other.opts;
        other.opts = nullptr;
    }
    return *this;
}    
    
c3::MultiApproxOpts::~MultiApproxOpts(){
    // std::cout << "MultiApproxOpts Destructor" << std::endl;
    if (alloc == true) {
        c3core::multi_approx_opts_free(opts);
    }
    opts = nullptr;
}




void c3::MultiApproxOpts::set_dim(size_t dim, const OneApproxOpts &one_opts){
    c3core::multi_approx_opts_set_dim(opts, dim, one_opts.opts);
}


// 

c3::C3Approx::C3Approx(enum c3core::C3ATYPE type, size_t dim)
{
    // std::cout << "Approx Constructor" << std::endl;
    opts = c3core::c3approx_create(type, dim);
}        

// // Copy assignment operator: replace previously initialized
// c3::C3Approx& C3Approx::operator=(const c3::C3Approx &other){
//     std::cout << "C3Approx Assignment" << std::endl;
//     NotImplemented e;
//     throw e;
// }

// Move constructor
c3::C3Approx::C3Approx(c3::C3Approx &&other) {
    // std::cout << "C3Approx Move" << std::endl;
    opts = other.opts;
    other.opts = nullptr;
}

// Move assignment
c3::C3Approx& C3Approx::operator=(c3::C3Approx &&other) {
    // std::cout << "C3Approx Move Assignment" << std::endl;
    if (this != &other) {
        c3core::c3approx_destroy(opts);
        opts = other.opts;
        other.opts = nullptr;
    }
    return *this;
}

c3::C3Approx::~C3Approx(){
    // std::cout << "C3Approx Destructor" << std::endl;
    c3core::c3approx_destroy(opts);
    opts = nullptr;
}
    

void c3::C3Approx::init_cross(size_t init_rank, int verbose, double **startin)
{
    c3core::c3approx_init_cross(opts, init_rank, verbose, startin);
}

void c3::C3Approx::set_round_tol(double tol)
{
    c3core::c3approx_set_round_tol(opts, tol);
}
void c3::C3Approx::set_cross_tol(double tol)
{
    c3core::c3approx_set_cross_tol(opts, tol);
}
void c3::C3Approx::set_verbose(int verbosity)
{
    c3core::c3approx_set_verbose(opts, verbosity);
}
void c3::C3Approx::set_adapt_kickrank(size_t kickrank)
{
    c3core::c3approx_set_adapt_kickrank(opts, kickrank);
}
void c3::C3Approx::set_adapt_maxrank_all(size_t maxrank)
{
    c3core::c3approx_set_adapt_maxrank_all(opts, maxrank);
}
void c3::C3Approx::set_cross_maxiter(size_t maxiter)
{
    c3core::c3approx_set_cross_maxiter(opts, maxiter);
}

void c3::C3Approx::set_approx_opts_dim(size_t dim, const OneApproxOpts &one_opts){
    c3core::c3approx_set_approx_opts_dim(opts, dim, one_opts.opts);
}

