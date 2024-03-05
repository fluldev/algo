#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include "basics.h"

#define HEAP_PARENT(i) (i>>1)
#define HEAP_LEFT(i) (2*i)
#define HEAP_RIGHT(i) (2*i+1)

struct heap {
  void *data;
  size_t stride;
  size_t len;
  size_t size;
};

void heapify(struct heap *res, compare_fn_t comp_fn, size_t idx);
void make_heap(struct heap *res, compare_fn_t comp_fn);
#define heap_max(h) (h->len ? h->data : NULL)
void *heap_extract_max(struct heap *res, compare_fn_t comp_fn);

#endif
