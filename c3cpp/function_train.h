#ifndef FUNCTION_TRAIN_CPP_H
#define FUNCTION_TRAIN_CPP_H

#include <iostream>

#include "core.h"

namespace c3
{
        
    class FunctionTrain
    {
    public: 
        struct c3core::FunctionTrain * ft;
    
        FunctionTrain(): ft(nullptr) {};
    
        FunctionTrain(struct c3core::FunctionTrain *ft) : ft(ft) {
            std::cout << "FunctionTrain Constructor" << std::endl;
        }

        FunctionTrain(const c3::C3Approx &approx, const c3::Fwrap &fwrap, int adapt);

        // Copy Constructor: initialize previously uninitialized
        FunctionTrain(const FunctionTrain &other); 

        // Copy assignment operator: replace previously initialized
        FunctionTrain& operator=(const FunctionTrain &other); 

        // Move constructor
        FunctionTrain(FunctionTrain &&other);

        // Move assignment
        FunctionTrain& operator=(FunctionTrain &&other);
    
        ~FunctionTrain();

        FunctionTrain & constant(double value, const c3::MultiApproxOpts &opts);
        FunctionTrain round(double eps, const c3::MultiApproxOpts &opts);
            
        size_t get_dim() const;
        size_t get_nparams() const;
        size_t *get_ranks() const;
        double get_avgrank() const;
        double get_maxrank() const;

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
    };
}

#endif
