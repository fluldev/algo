#include <stdio.h>

#include "basics.h"
#include "sort.h"


#define INPUT_SIZE 10
#define SORT_TEST(name) test_sort_algo(name, INPUT_SIZE, #name)

int main(void) {
  printf("-------------------------- Sorting algorithm tests --------------------------\n");
  SORT_TEST(insertion_sort);
  SORT_TEST(merge_sort);
  SORT_TEST(heap_sort);
}
