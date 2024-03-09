#include "basics.h"
#include "order_stat.h"

#define LIST_LEN 1000

static int _test_comp(const void *a, const void *b) {
  return *(long*) a - *(long*)b;
}


int main(void)
{
  FILE *f;
  int seed;
  assert((f = fopen("/dev/urandom", "r")) != NULL && "Cannot open /dev/urandom.");
  assert((fread(&seed, sizeof(seed), 1, f) == 1) && "Cannot read from /dev/urandom.");
  fclose(f);
  srand(seed);

  long *list = malloc(LIST_LEN * sizeof(*list));
  long *sorted_list = malloc(LIST_LEN * sizeof(*sorted_list));
  long *working_list = malloc(LIST_LEN * sizeof(*working_list));
  for(size_t i = 0; i<LIST_LEN; ++i)
    list[i] = rand();
  memcpy(sorted_list, list, LIST_LEN*sizeof(*working_list));
  qsort(sorted_list, LIST_LEN, sizeof(*sorted_list), _test_comp);

  pr_sect("Order Statistics tests");
  int res;

  memcpy(working_list, list, LIST_LEN*sizeof(*working_list));
  res = sorted_list[0] == *(long*)(minimum(working_list, LIST_LEN, sizeof(*working_list), _test_comp));
  pr_test("minimum", res);
  
  memcpy(working_list, list, LIST_LEN*sizeof(*working_list));
  void *min, *max;
  minimum_maximum(working_list, LIST_LEN, sizeof(*working_list), _test_comp, &min, &max);
  res = sorted_list[0] == *(long*)min && sorted_list[LIST_LEN-1] == *(long*)max;
  pr_test("minimum_maximum", res);
  
  memcpy(working_list, list, LIST_LEN*sizeof(*working_list));
  long *median = randomized_select(LIST_LEN/2, working_list, LIST_LEN, sizeof(*working_list), _test_comp);
  res = sorted_list[LIST_LEN/2] == *median;
  pr_test("randomized_select", res);

  free(list);
  free(sorted_list);
  free(working_list);

  return 0;
}
