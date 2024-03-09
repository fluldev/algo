#include <stdio.h>
#include <stdlib.h>

#include "basics.h"
#include "sort.h"


#define INPUT_SIZE 10000
#define SORT_TEST(name) test_sort_algo(name, INPUT_SIZE, #name)
#define LIN_SORT_TEST(name) test_lin_sort_algo(name, INPUT_SIZE, #name)
#define LIN_SORT_TEST2(name) test_lin_sort_algo2(name, INPUT_SIZE, #name)

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
    res = 1;
  } else {
    res = 0;
  }
  pr_test(algo_name, res);

  free(arr);
  free(arr2);
  return res;
}

static size_t _test_to_idx(void *x)
{
  return *(long*)x;
}

int test_lin_sort_algo(void(*algo)(void*,size_t,size_t,to_idx_fn_t), size_t input_size, const char *algo_name)
{
  FILE *f;
  int seed;
  assert((f = fopen("/dev/urandom", "r")) != NULL && "Cannot open /dev/urandom.");
  assert((fread(&seed, sizeof(seed), 1, f) == 1) && "Cannot read from /dev/urandom.");
  fclose(f);
  srand(seed);

  long *arr = malloc(input_size * sizeof(*arr));
  for(size_t i = 0; i<input_size; ++i) {
    arr[i] = i;
  }
  random_permutation(arr, input_size, sizeof(long));

  algo(arr, input_size, sizeof(*arr), _test_to_idx);

  int res = 1;
  for(size_t i = 0; i<input_size; ++i)
    if(arr[i] != (long)i) {
      res = 0;
      break;
    }
  pr_test(algo_name, res);

  free(arr);
  return res;
}


static double _test_to_uni_dist(void *x) 
{
  return (double)*(long*)x / RAND_MAX;
}

int test_lin_sort_algo2(void(*algo)(void*,size_t,size_t,to_uni_dist_fn_t,compare_fn_t), size_t input_size, const char *algo_name)
{
  FILE *f;
  int seed;
  int res;
  assert((f = fopen("/dev/urandom", "r")) != NULL && "Cannot open /dev/urandom.");
  assert((fread(&seed, sizeof(seed), 1, f) == 1) && "Cannot read from /dev/urandom.");
  fclose(f);
  srand(seed);

  long *arr = malloc(input_size * sizeof(*arr));
  long *arr2 = malloc(input_size * sizeof(*arr));
  for(size_t i = 0; i<input_size; ++i) {
    arr[i] = rand();
    arr2[i] = arr[i];
  }

  algo(arr, input_size, sizeof(*arr), _test_to_uni_dist, _test_comp);
  qsort(arr2, input_size, sizeof(long), _test_comp);

  res = memcmp(arr, arr2, sizeof(long)*input_size) == 0;
  pr_test(algo_name, res);

  free(arr);
  return res;
}


int main(void) {
  pr_sect("Sorting algorithm tests");
  SORT_TEST(insertion_sort);
  SORT_TEST(merge_sort);
  SORT_TEST(heap_sort);
  SORT_TEST(quick_sort);
  SORT_TEST(rand_quick_sort);
  pr_sect("Linear time sorting algorithm tests");
  LIN_SORT_TEST(counting_sort);
  LIN_SORT_TEST2(bucket_sort_mine);
}
