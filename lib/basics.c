#include "basics.h"

#define RED_TEXT "\033[91m"
#define GREEN_TEXT "\033[92m"
#define RESET_TEXT "\033[0m"
#define SECT_WIDTH 64
#define PASSED "PASSED"
#define FAILED "FAILED"
#define PASSED_COL GREEN_TEXT PASSED RESET_TEXT
#define FAILED_COL RED_TEXT FAILED RESET_TEXT

void pr_sect(const char *secname)
{
  ssize_t dashes = (SECT_WIDTH - (ssize_t)strlen(secname) - 2);
  int uneven = dashes % 2;
  dashes /= 2;

  if(dashes < 0) {
    printf("%s\n", secname);
    return;
  }
  
  for(ssize_t i = 0; i<dashes; ++i) putchar('-');
  printf(" %s ", secname);
  for(ssize_t i = 0; i<dashes+uneven; ++i) putchar('-');
  putchar('\n');
}


void pr_test(const char *testname, int passed)
{
  ssize_t space_ibtw = SECT_WIDTH - (ssize_t)strlen(testname);
  if(passed)
    space_ibtw -= (ssize_t)strlen(PASSED);
  else
    space_ibtw -= (ssize_t)strlen(FAILED);

  if(space_ibtw<=0) {
    printf("%s %s\n", testname, passed?PASSED_COL:FAILED_COL);
    return;
  }

  printf("%s", testname);
  for(ssize_t i = 0; i<space_ibtw; ++i) putchar(' ');
  printf("%s\n", passed?PASSED_COL:FAILED_COL);
}


size_t partition(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  if(len<=1)
    return 0;

  void *pivot = generic_at(a, len-1);
  --len;
  size_t j = 0;
  for(size_t i = 0; i<len; ++i)
    if(comp_fn(generic_at(a, i), pivot) < 0) {
      if(i!=j)
        generic_xchg(generic_at(a, i), generic_at(a, j));
      j++;
    }
  generic_xchg(generic_at(a, j), generic_at(a, len));
  return j;
}


size_t rand_partition(void *a, size_t len, size_t stride, compare_fn_t comp_fn)
{
  size_t pivot = rand() % len;
  generic_xchg(generic_at(a, len-1), generic_at(a, pivot));
  return partition(a, len, stride, comp_fn);
}

void random_permutation(void *a, size_t len, size_t stride)
{
  for(size_t i = 0; i<len; ++i) {
    size_t xchg_i = i + (rand() % (len-i));
    generic_xchg(generic_at(a, xchg_i), generic_at(a, i));
  }
}
