#include <iostream>

#include "core.h"

#include "functions.h"

using namespace c3;

// Options for type: "general" "general-vec" 
c3::Fwrap::Fwrap(size_t dim, std::string type)
{
    fwrap = c3core::fwrap_create(dim, type.c_str());
}

// Move constructor
c3::Fwrap::Fwrap(Fwrap && other)
{
    std::cout << "Fwrap Move Constructor" << std::endl;
    fwrap = other.fwrap;
    other.fwrap = nullptr;
}

c3::Fwrap &c3::Fwrap::operator=(Fwrap && other)
{
    std::cout << "Fwrap Move Assignment" << std::endl;
    if (this != &other) {
        c3core::fwrap_destroy(fwrap);
        fwrap = other.fwrap;
        other.fwrap = nullptr;
    }

    return *this;
}

c3::Fwrap::~Fwrap()
{
    std::cout << "Fwrap Destructor " << std::endl;
    c3core::fwrap_destroy(fwrap);
    fwrap = nullptr;
}

void c3::Fwrap::set_fvec(int(*f)(size_t,const double*,double*,void*),void* args)
{
    c3core::fwrap_set_fvec(fwrap, f, args);
}

void c3::Fwrap::set_f(double(*f)(const double*,void*),void*args)
{
    c3core::fwrap_set_f(fwrap, f, args);
}

c3::FunctionMonitor::FunctionMonitor(double (*func)(const double *, void *), void * args, size_t dim,
                    size_t table_size)
{
    monitor = c3core::function_monitor_initnd(func, args, dim, table_size);
}

c3::FunctionMonitor::~FunctionMonitor()
{
    c3core::function_monitor_free(monitor);
    monitor = nullptr;
}


c3::FunctionMonitor::FunctionMonitor(FunctionMonitor && other)
{
    std::cout << "FunctionMonitor Move Constructor" << std::endl;
    monitor = other.monitor;
    other.monitor = nullptr;
}

c3::FunctionMonitor &c3::FunctionMonitor::operator=(FunctionMonitor && other)
{
    std::cout << "FunctionMonitor Move Assignment" << std::endl;
    if (this != &other) {
        c3core::function_monitor_free(monitor);
        monitor = other.monitor;
        other.monitor = nullptr;
    }

    return *this;
}

double c3::FunctionMonitor::eval(const double * pt)
{
    return c3core::function_monitor_eval(pt, monitor);
}
