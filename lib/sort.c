#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "basics.h"
#include "sort.h"
#include "heap.h"

/* 
 * Simple in place O(n^2) sorting algorithm.
 * Can be imagined like sorting a deck of cards, 
 * have a always sorted pile in your hand and pull
 * cards from the unsorted pile. Put those cards in 
 * the place of the sorted pile so that it remains sorted
 * until all cards are on the sorted pile. 
*/
void insertion_sort(void *res, size_t len, size_t stride, compare_fn_t comp_fn)
{
  for(size_t i = 1; i<len; ++i) {
    for(size_t j=i; j>=1; --j) {
      if(comp_fn(generic_at(res, j), generic_at(res, j-1)) < 0)
        generic_xchg(generic_at(res, j), generic_at(res, j-1));
      else
        break;
    }
  }
}


/*
 * Recursive, Divide and Conquer O(n lg n) sorting algorithm that works out of place.
*/
void merge_sort(void *res, size_t len, size_t stride, compare_fn_t comp_fn)
{
  if(len<2)
    return;

  size_t lower_len = len/2;
  size_t upper_len = len-lower_len;
  void *lower = malloc(stride*len);
  void *upper = lower+stride*lower_len;
  memcpy(lower, res, stride*len);

  merge_sort(lower, lower_len, stride, comp_fn);
  merge_sort(upper, upper_len, stride, comp_fn);

  size_t i = 0, j = 0;
  while(i<lower_len && j<upper_len) {
    if(comp_fn(generic_at(lower, i), generic_at(upper, j)) < 0) {
      generic_assign(generic_at(res, i+j), generic_at(lower, i));
      i++;
    } else {
      generic_assign(generic_at(res, i+j), generic_at(upper, j));
      j++;
    }
  }
  while(i<lower_len) {
    generic_assign(generic_at(res, i+j), generic_at(lower, i));
    ++i;
  }
  while(j<upper_len) {
    generic_assign(generic_at(res, i+j), generic_at(upper, j));
    ++j;
  }

  free(lower);
}


/* Sort using max_heap, O(n lg n) */
void heap_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  struct heap h = {
    .data = a,
    .stride = stride,
    .len = len,
    .size = len
  };

  make_heap(&h, comp_fn);
  while(h.len > 1) {
    heap_extract_max(&h, comp_fn);
  }
}


void quick_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  if(len <= 1)
    return;
  size_t pivot = partition(a, len, stride, comp_fn);
  quick_sort(a, pivot, stride, comp_fn);
  quick_sort(generic_at(a, pivot+1), len-pivot-1, stride, comp_fn);
}


void rand_quick_sort(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  if(len <= 1)
    return;
  size_t pivot = rand_partition(a, len, stride, comp_fn);
  rand_quick_sort(a, pivot, stride, comp_fn);
  rand_quick_sort(generic_at(a, pivot+1), len-pivot-1, stride, comp_fn);
}


/* Linear time sorting algorithms. */


void counting_sort(void *a, size_t len, size_t stride, to_idx_fn_t to_idx)
{
  size_t *cnts = malloc(sizeof(*cnts) * len);
  size_t *b = malloc(sizeof(*b) * len);
  size_t *tmp = malloc(stride * len);
  memcpy(tmp, a, len*stride);

  for(size_t i = 0; i<len; ++i)
    cnts[i] = 0;

  for(size_t i = 0; i<len; ++i) {
    b[i] = to_idx(generic_at(a, i));
    cnts[b[i]] += 1;
  }

  for(size_t i = 1; i<len; ++i)
    cnts[i] += cnts[i-1];
  
  for(size_t i = 0; i<len; ++i) {
    --cnts[b[i]];
    generic_assign(generic_at(a, cnts[b[i]]), &tmp[i]);
  }

  free(cnts);
  free(b);
  free(tmp);
}


/* This is a version of bucket sort modified by me, that does not use 
 * linked lists (as in the book) and might be faster therefore.
 * Obviously there is heavy inspiration from counting sort. */
void bucket_sort_mine(void *a, size_t len, size_t stride, to_uni_dist_fn_t to_uni_dist, compare_fn_t comp_fn)
{
  size_t *offs = malloc(sizeof(*offs) * len); 
  void *tmp = malloc(stride * len);

  memcpy(tmp, a, len*stride);

  for(size_t i = 0; i<len; ++i)
    offs[i] = 0;
  
  for(size_t i = 0; i<len; ++i) {
    double value = to_uni_dist(generic_at(a, i));
    offs[(size_t) (len*value)] += 1;
  }
  
  for(size_t i = 1; i<len; ++i) {
    offs[i] += offs[i-1];
  }

  for(size_t i = 0; i<len; ++i) {
    void *elem = generic_at(tmp, i);
    size_t idx = (size_t)(len*to_uni_dist(elem));
    --offs[idx];
    generic_assign(generic_at(a, offs[idx]), elem);
  }

  for(size_t i = 0; i<len-1; ++i)
    insertion_sort(generic_at(a, offs[i]), offs[i+1]-offs[i], stride, comp_fn);
  insertion_sort(generic_at(a, offs[len-1]), len-offs[len-1], stride, comp_fn);
  
  free(offs);
  free(tmp);
}
