// Copyright (C) 2018-2019 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

/**
 * @brief A header file for the Inference Engine plugins destruction mechanism
 * @file ie_irelease.hpp
 */
#pragma once

#include "ie_no_copy.hpp"
#include <memory>

/* Obtain a backtrace and print it to stdout. */
#include <execinfo.h>
inline void print_trace (void)
{
    void *array[10];
    size_t size;
    char **strings;
    size_t i;

    size = backtrace (array, 10);
    strings = backtrace_symbols (array, size);

    printf ("Obtained %zd stack frames.\n", size);

    for (i = 0; i < size; i++)
        printf ("bt[%i] %s\n", int(i), strings[i]);

    free (strings);
}

namespace InferenceEngine {
namespace details {
/**
 * @brief This class is used for objects allocated by a shared module (in *.so)
 */
class IRelease : public no_copy {
public:
    /**
     * @brief Releases current allocated object and all related resources.
     * Once this method is called, the pointer to this interface is no longer valid
     */
    virtual void Release() noexcept = 0;

 protected:
    /**
     * @brief Default destructor
     */
    ~IRelease() override = default;
};



template <class T> inline std::shared_ptr<T> shared_from_irelease(T * ptr) {
    std::shared_ptr<T> pointer(ptr, [](IRelease *p) {
        std::cerr << __PRETTY_FUNCTION__ << "releasing:" << (void*)p << "\n";
        print_trace();
        p->Release();
    });
    return pointer;
}

}  // namespace details
}  // namespace InferenceEngine
