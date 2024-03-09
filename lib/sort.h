#ifndef __SORT_H__
#define __SORT_H__

#include <stdlib.h>

#include "basics.h"

void insertion_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void merge_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void heap_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void quick_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void rand_quick_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn);

void counting_sort(void *a, size_t len, size_t stride, to_idx_fn_t to_idx);
void bucket_sort(void *a, size_t len, size_t stride, to_uni_dist_fn_t to_uni_dist);
void bucket_sort_mine(void *a, size_t len, size_t stride, to_uni_dist_fn_t to_uni_dist, compare_fn_t comp_fn);

#endif
