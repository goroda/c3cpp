#include <iostream>

#include "c3_cpp.h"

using namespace c3;


c3::FunctionTrain::FunctionTrain(const c3::C3Approx &approx,
                                 const c3::Fwrap &fwrap, int adapt)
{
    ft = c3core::c3approx_do_cross(approx.opts, fwrap.fwrap, adapt);
}

c3::FunctionTrain& c3::FunctionTrain::operator=(const FunctionTrain &other){
    // std::cout << "FunctionTrain Assignment" << std::endl;
    if (this != &other) {
        c3core::function_train_free(ft);
        ft = c3core::function_train_copy(other.ft);
    }
    return *this;
}

// Move constructor
c3::FunctionTrain::FunctionTrain(FunctionTrain &&other) {
    // std::cout << "FunctionTrain Move" << std::endl;
    ft = other.ft;
    other.ft = nullptr;
}

// Move assignment
c3::FunctionTrain & c3::FunctionTrain::operator=(FunctionTrain &&other) {
    // std::cout << "FunctionTrain Move Assignment" << std::endl;
    if (this != &other) {
        c3core::function_train_free(ft);
        ft = other.ft;
        other.ft = nullptr;
    }
    return *this;
}    
    
c3::FunctionTrain::~FunctionTrain(){
    // std::cout << "FunctionTrain Destructor" << std::endl;
    c3core::function_train_free(ft);
    ft = nullptr;
}

c3::FunctionTrain & c3::FunctionTrain::constant(double value, const MultiApproxOpts &opts)
{
    c3core::function_train_free(ft);
    ft = c3core::function_train_constant(value, opts.opts);
    return *this;
}

c3::FunctionTrain c3::FunctionTrain::round(double eps, const MultiApproxOpts &opts)
{
    return c3::FunctionTrain(c3core::function_train_round(ft, eps, opts.opts));
}

size_t c3::FunctionTrain::get_dim() const { return c3core::function_train_get_dim(ft); }
size_t c3::FunctionTrain::get_nparams() const { return c3core::function_train_get_nparams(ft); }
size_t* c3::FunctionTrain::get_ranks() const { return c3core::function_train_get_ranks(ft); }
double c3::FunctionTrain::get_avgrank() const { return c3core::function_train_get_avgrank(ft); }
double c3::FunctionTrain::get_maxrank() const { return c3core::function_train_get_maxrank(ft); }


FunctionTrain & c3::FunctionTrain::scale(double val) {
    c3core::function_train_scale(ft, val);
    return *this;
}

double c3::FunctionTrain::eval(const double * pt) const {return c3core::function_train_eval(ft, pt); }
double c3::FunctionTrain::integrate() const {return c3core::function_train_integrate(ft); }
double c3::FunctionTrain::integrate_weighted() const {return c3core::function_train_integrate(ft); }
    
double c3::FunctionTrain::inner(const FunctionTrain &other) const {
    return c3core::function_train_inner(ft, other.ft);
}
double c3::FunctionTrain::inner_weighted(const FunctionTrain &other) const {
    return c3core::function_train_inner_weighted(ft, other.ft);
}

FunctionTrain c3::FunctionTrain::sum(const FunctionTrain &other) const {
    return FunctionTrain(c3core::function_train_sum(ft, other.ft));
};

FunctionTrain c3::FunctionTrain::product(const FunctionTrain &other) const {
    return FunctionTrain(c3core::function_train_product(ft, other.ft));
};

FunctionTrain c3::FunctionTrain::integrate_weighted_subset(size_t ndim_contract, size_t *dims_contract) const
{
    return FunctionTrain(
        c3core::function_train_integrate_weighted_subset(ft, ndim_contract,dims_contract)
        );
};

int c3::FunctionTrain::save(std::string filename) const {
    return c3core::function_train_save(ft, const_cast<char*>(filename.c_str()));
}

void c3::FunctionTrain::axpy(double a, const FunctionTrain & x, double epsilon, const MultiApproxOpts &opts) {

    c3core::c3axpy(a, x.ft, &ft, epsilon, opts.opts);
}
