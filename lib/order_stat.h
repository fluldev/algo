#ifndef __ORDER_STAT_H__
#define __ORDER_STAT_H__

#include "basics.h"

void *minimum(void *a, size_t len, size_t stride, compare_fn_t comp_fn);
void minimum_maximum(void *a, size_t len, size_t stride, compare_fn_t comp_fn, void **min, void **max);
void *randomized_select(size_t ith, void *a, size_t len, size_t stride, compare_fn_t comp_fn);

#endif

