#ifndef SOBOL_CPP_H
#define SOBOL_CPP_H

#include <iostream>

#include "core.h"

namespace c3
{

    class SobolIndices
    {
    public:
        struct c3core::C3SobolSensitivity *sobol;

        // maximum order rof interactions
        SobolIndices(const FunctionTrain &ft, size_t order);
        ~SobolIndices();

        // No copying!
        SobolIndices(const SobolIndices &other) = delete; 
        SobolIndices& operator=(const SobolIndices &other) = delete;         

        // Moving
        SobolIndices(SobolIndices &&other);
        SobolIndices& operator=(SobolIndices &&other);
        
        double get_variance() const;
        double get_total_effect(size_t dim) const;
        double get_interaction(size_t num_interact, const size_t * vars) const;
            
    };

};

#endif
