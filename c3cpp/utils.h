#ifndef UTILS_C3_CPP_H
#define UTILS_C3_CPP_H
#include <stdexcept>

namespace c3 {
    class NotImplemented : public std::logic_error
    // https://stackoverflow.com/a/36851059
    {
    public:
        NotImplemented();
    };
}

#endif
