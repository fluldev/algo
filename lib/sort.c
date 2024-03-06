#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "sort.h"
#include "heap.h"

static int _test_comp(const void *a, const void *b) {
  return *(long*) a - *(long*)b;
}
int test_sort_algo(sort_fn_t algo, size_t input_size, const char *algo_name)
{
  FILE *f;
  int seed;
  assert((f = fopen("/dev/urandom", "r")) != NULL && "Cannot open /dev/urandom.");
  assert((fread(&seed, sizeof(seed), 1, f) == 1) && "Cannot read from /dev/urandom.");
  fclose(f);
  srand(seed);

  long *arr = malloc(input_size * sizeof(*arr));
  long *arr2 = malloc(input_size * sizeof(*arr));
  for(size_t i = 0; i<input_size; ++i) {
    arr[i] = rand();
  }
  memcpy(arr2, arr, sizeof(*arr) * input_size);

  algo(arr, input_size, sizeof(*arr), _test_comp);
  qsort(arr2, input_size, sizeof(*arr2), _test_comp);

  int res;
  if(memcmp(arr, arr2, input_size*sizeof(*arr)) == 0) {
    printf("%s\t\t\t\t"GREEN_TEXT"PASSED"RESET_TEXT".\n", algo_name);
    res = 0;
  } else {
    printf("%s\t\t\t\t"RED_TEXT"FAILED"RESET_TEXT".\n", algo_name);
    res = 1;
  }

  free(arr);
  free(arr2);
  return res;
}

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
