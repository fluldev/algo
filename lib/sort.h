#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>

#include "basics.h"

void insertion_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void merge_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void heap_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);

int test_sort_algo(sort_fn_t algo, size_t input_size, const char *algo_name);

#endif
