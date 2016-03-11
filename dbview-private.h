/**
 * @file dbview-private.h
 * @brief Declarations for DbView class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_DBVIEW_PRIVATE_H_INCLUDE
#define GUARD_DBVIEW_PRIVATE_H_INCLUDE

#include <dbview/dbview-config.h>

#if 0
#    define DBVIEW_DEBUGM printf
#else
#    define DBVIEW_DEBUGM black_hole
#endif

#if 0
#    define DBVIEW_TRACE_ENTRY printf("DBVIEW ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define DBVIEW_TRACE_ENTRY
#endif

#if 0
#    define DBVIEW_TRACE_EXIT printf("DBVIEW EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define DBVIEW_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

#endif // GUARD_DBVIEW_PRIVATE_H_INCLUDE
