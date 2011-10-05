#pragma once
#ifndef SCHEDULERMEMORY_H_
#define SCHEDULERMEMORY_H_

#ifdef CPPUTEST_USE_MEM_LEAK_DETECTION
#include <CppUTest/TestHarness_c.h>
#define acquire(s) cpputest_malloc_location((s), __FILE__, __LINE__)
#define release(s) cpputest_free_location((s), __FILE__, __LINE__)
#else
#define acquire(s) malloc((s))
#define release(s) free((s))
#endif

#include <stdlib.h>

#endif
