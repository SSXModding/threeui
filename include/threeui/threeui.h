/* SPDX-License-Identifier: MIT */
#ifndef THREEUI_PUBLIC_H
#define THREEUI_PUBLIC_H

#include <stdint.h>

//! This file declares the C API of the threeui library.
//! Threeui also comes with a C++ API, but it's easier for
//! bindings to use this C repressentation.

#include <threeui/threeui_config.h>

#ifdef __cplusplus
extern "C" {
#endif

    /// Initializes the threeui library. THREEUI_ABI_VERSION must be provided to this function.
    bool threeuiInit(uint32_t abiVersion);

    /// Call when done using the threeui library.
    void threeuiFini();

#ifdef __cplusplus
}
#endif


#endif