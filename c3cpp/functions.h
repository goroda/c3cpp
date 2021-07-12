#ifndef FUNCTIONS_CPP_H
#define FUNCTIONS_CPP_H

#include <string>

#include "core.h"


namespace c3
{

    class Fwrap
    {
    public:
        struct c3core::Fwrap * fwrap;

        Fwrap(size_t dim, std::string type);

        Fwrap(const Fwrap &other) = delete;
        Fwrap& operator=(const Fwrap &other) = delete;
        Fwrap(Fwrap &&other);
        Fwrap& operator=(Fwrap &&other);

        void set_fvec(int(* f)(size_t,const double*,double*,void*),void* args);
        void set_f(double(*f)(const double*,void*),void*args);
        ~Fwrap();
        
    };

    class FunctionMonitor
    {
    public:
        struct c3core::FunctionMonitor * monitor;
        
        FunctionMonitor(double (*)(const double *, void *), void *, size_t, size_t);
    

        FunctionMonitor(const FunctionMonitor &other) = delete;
        FunctionMonitor& operator=(const FunctionMonitor &other) = delete;
        FunctionMonitor(FunctionMonitor &&other);
        FunctionMonitor& operator=(FunctionMonitor &&other);

        double eval(const double * pt);
        ~FunctionMonitor();
        
    };

}

#endif
