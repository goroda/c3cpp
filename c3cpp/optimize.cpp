#include <iostream>

#include "c3_cpp.h"

using namespace c3;

c3::C3Opt::C3Opt(enum c3core::c3opt_alg alg) {
    opt = c3core::c3opt_create(alg);
}

c3::C3Opt::~C3Opt() {
    c3opt_free(opt);
    opt = nullptr;
}

void c3::C3Opt::set_relftol(double val) {
    c3core::c3opt_set_relftol(opt, val);
}

void c3::C3Opt::set_gtol(double val) {
    c3core::c3opt_set_gtol(opt, val);
}

void c3::C3Opt::set_verbose(int verbosity) {
    c3core::c3opt_set_verbose(opt, verbosity);
}

void c3::C3Opt::set_maxiter(size_t maxiter) {
    c3core::c3opt_set_maxiter(opt, maxiter);
}

void c3::C3Opt::ls_set_maxiter(size_t maxiter) {
    c3core::c3opt_ls_set_maxiter(opt, maxiter);
}

void c3::C3Opt::set_absxtol(double tol) {
    c3core::c3opt_set_absxtol(opt, tol);
}
