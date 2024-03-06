#include <stdlib.h>

#include "basics.h"
#include "heap.h"

#define HEAP_SCALING_FACTOR 1.4

int heapify(struct heap *res, compare_fn_t comp_fn, size_t idx)
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
    return 1;
  }
  return 0;
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
  generic_xchg(generic_at(res->data, res->len-1), res->data);
  res->len--;
  heapify(res, comp_fn, 0);
  return res->data + res->len*res->stride;
}

void heap_change_value(struct heap *res, compare_fn_t comp_fn, size_t idx, void *value)
{
  size_t stride = res->stride;
  int cmp = comp_fn(value, generic_at(res->data, idx));

  if(cmp == 0)
    return;

  generic_assign(generic_at(res->data, idx), value);
  if(cmp > 0) {  /* new value is larger -> can only transverse up */
    while(idx) {
      idx = HEAP_PARENT(idx);
      if(!heapify(res, comp_fn, idx))
		break;
    }	
  } else {  /* new value is smaller -> can only transverse down */
    heapify(res, comp_fn, idx);
  }
}

void heap_insert_value(struct heap *res, compare_fn_t comp_fn, void *value)
{
  size_t stride = res->stride;
  if(res->size <= res->len) {
	res->size = (size_t)(res->size * HEAP_SCALING_FACTOR)+1;
    res->data = realloc(res->data, res->size);
  }
  generic_assign(generic_at(res->data, res->len), value);
  size_t idx = res->len++;
  while(idx) {
    idx = HEAP_PARENT(idx);
    if(!heapify(res, comp_fn, idx))
  	break;
  }	
}
