#include <iostream>

#include "c3_cpp.h"

using namespace c3;

c3::SobolIndices::SobolIndices(const FunctionTrain &ft, size_t order) {
    sobol = c3core::c3_sobol_sensitivity_calculate(ft.ft, order);
}

c3::SobolIndices::~SobolIndices() {
    c3core::c3_sobol_sensitivity_free(sobol);
}

// Move constructor
c3::SobolIndices::SobolIndices(SobolIndices &&other) {
    std::cout << "SobolIndices Move" << std::endl;
    sobol = other.sobol;
    other.sobol = nullptr;
}

// Move assignment
c3::SobolIndices & c3::SobolIndices::operator=(SobolIndices &&other) {
    std::cout << "SobolIndices Move Assignment" << std::endl;
    if (this != &other) {
        c3core::c3_sobol_sensitivity_free(sobol);
        sobol = other.sobol;
        other.sobol = nullptr;
    }
    return *this;
}    

double c3::SobolIndices::get_variance() const {
    return c3core::c3_sobol_sensitivity_get_variance(sobol);
}

double c3::SobolIndices::get_total_effect(size_t dim) const {
    return c3core::c3_sobol_sensitivity_get_total(sobol, dim);
}

double c3::SobolIndices::get_interaction(size_t num_interact, const size_t * vars) const
{
    return c3core::c3_sobol_sensitivity_get_interaction(sobol, num_interact, vars);
}
