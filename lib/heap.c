#include <stdlib.h>

#include "basics.h"
#include "heap.h"


void heapify(struct heap *res, compare_fn_t comp_fn, size_t idx)
{
  size_t largest = idx;
  size_t left = HEAP_LEFT(idx);
  size_t right = HEAP_RIGHT(idx);
  size_t stride = res->stride;

  if(res->len > left && comp_fn(generic_at(res->data, largest), generic_at(res->data, left)) < 0)
    largest = left;
  if(res->len > right && comp_fn(generic_at(res->data, largest), generic_at(res->data, right)) < 0)
    largest = right;

  if(largest != idx) {
    generic_xchg(generic_at(res->data, largest), generic_at(res->data, idx));
    heapify(res, comp_fn, largest);
  }
}

void make_heap(struct heap *res, compare_fn_t comp_fn)
{
  for(ssize_t i = res->len/2-1; i>=0; --i)
    heapify(res, comp_fn, i);
}

void *heap_extract_max(struct heap *res, compare_fn_t comp_fn)
{
  if(res->len == 1) {
    res->len--;
    return res->data;
  }
  if(res->len == 0)
    return NULL;

  size_t stride = res->stride;
  generic_xchg(res->data + (res->len-1)*res->stride, res->data);
  res->len--;
  heapify(res, comp_fn, 0);
  return res->data + res->len*res->stride;
}
