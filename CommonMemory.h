#pragma once
#ifndef SCHEDULERMEMORY_H_
#define SCHEDULERMEMORY_H_

#ifdef CPPUTEST_USE_MEM_LEAK_DETECTION
#include <CppUTest/TestHarness_c.h>
#define acquire(s) cpputest_malloc_location((s), __FILE__, __LINE__)
#define release(s) if(s != NULL) cpputest_free_location((s), __FILE__, __LINE__)
#else
#include <memory.h>
#include <stddef.h>
#define acquire(s) malloc((s))
#define release(s) if(s != NULL) free(s)
#endif

#include <stdlib.h>

#endif
