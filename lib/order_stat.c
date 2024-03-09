#include <assert.h>

#include "basics.h"
#include "order_stat.h"


void *minimum(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  size_t imin = 0;

  for(size_t i = 1; i<len; ++i)
    if(comp_fn(generic_at(a, imin), generic_at(a, i)) > 0)
      imin = i;

  return generic_at(a, imin);
}


void minimum_maximum(void *a, size_t len, size_t stride, compare_fn_t *comp_fn, void **min, void **max)
{
  size_t imin, imax;
  assert(len>0 && "Array must have a length.");

  if(len == 1) {
    *min = *max = a;
    return;
  }

  if(comp_fn(generic_at(a, 0), generic_at(a, 1)) < 0) {
    imin = 0;
    imax = 1;
  } else {
    imin = 1;
    imax = 0;
  }

  size_t itend = len-(len%2);
  for(size_t i = 2; i<itend; i+=2) {
    size_t smaller, larger;
    if(comp_fn(generic_at(a, i), generic_at(a, i+1)) < 0) {
      smaller = i;
      larger = i+1;
    } else {
      smaller = i+1;
      larger = i;
    }
    if(comp_fn(generic_at(a, imin), generic_at(a, smaller)) > 0)
      imin = smaller;
    if(comp_fn(generic_at(a, imax), generic_at(a, larger)) < 0)
      imax = larger;
  }
  if(itend != len) {
    if(comp_fn(generic_at(a, imin), generic_at(a, len-1)) > 0)
      imin = len-1;
    if(comp_fn(generic_at(a, imax), generic_at(a, len-1)) < 0)
      imax = len-1;
  }

  *min = generic_at(a, imin);
  *max = generic_at(a, imax);
}

/* The input is modified regarding its order! */
void *randomized_select(size_t ith, void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  size_t div = rand_partition(a, len, stride, comp_fn);
  if(div == ith)
    return generic_at(a, ith);

  if(div < ith)
    return randomized_select(ith-div-1, generic_at(a, div+1), len-div-1, stride, comp_fn);
  else
    return randomized_select(ith, a, div, stride, comp_fn);
}
