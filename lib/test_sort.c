#include <stdio.h>

#include "basics.h"
#include "sort.h"


#define INPUT_SIZE 1000
#define SORT_TEST(name) test_sort_algo(name, INPUT_SIZE, #name)

int main(void) {
  pr_sect("Sorting algorithm tests");
  SORT_TEST(insertion_sort);
  SORT_TEST(merge_sort);
  SORT_TEST(heap_sort);
  SORT_TEST(quick_sort);
  SORT_TEST(rand_quick_sort);
}
