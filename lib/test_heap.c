#include <stdio.h>

#include "basics.h"
#include "heap.h"


static int _test_comp(const void *a, const void *b) {
  return *(long*) a - *(long*)b;
}
int main(void)
{
	long arr[10] = {0};
	long arrlen = sizeof(arr)/sizeof(*arr);
  	struct heap h = {
		.data = arr,
		.stride = sizeof(*arr),
		.len = sizeof(arr)/sizeof(*arr),
		.size = sizeof(arr)/sizeof(*arr)
	}; 
	int failed = 0;

 	printf("---------------------------- Heap algorithm tests ---------------------------\n");

	for(long i = 0; i<arrlen; ++i)
		arr[i] = i;
	make_heap(&h, _test_comp);
	for(long i = sizeof(arr)/sizeof(*arr)-1; i>=0; --i)
		if(i != *(long*)heap_extract_max(&h, _test_comp)) {
			failed = 1;
			break;
		}
	if(heap_extract_max(&h, _test_comp) != NULL)
		failed = 1;
	printf("make_heap & heap_extract_max test\t\t\t\t%s\n", failed?RED_TEXT"FAILED"RESET_TEXT:GREEN_TEXT"PASSED"RESET_TEXT);
	if(failed)
		return 0;

	for(long i = 0; i<arrlen; ++i)
		heap_insert_value(&h, _test_comp, &i);
	for(long i = sizeof(arr)/sizeof(*arr)-1; i>=0; --i)
		if(i != *(long*)heap_extract_max(&h, _test_comp)) {
			failed = 1;
			break;
		}
	if(heap_extract_max(&h, _test_comp) != NULL)
		failed = 1;

	printf("heap_insert_value test\t\t\t\t%s\n", failed?RED_TEXT"FAILED"RESET_TEXT:GREEN_TEXT"PASSED"RESET_TEXT);
	if(failed)
		return 0;

	for(long i = 0; i<arrlen; ++i)
		arr[i] = i;
	h.len = sizeof(arr)/sizeof(*arr);
	make_heap(&h, _test_comp);
	
	long new_value = 50;
	heap_change_value(&h, _test_comp, h.len-1, &new_value);
	if(*(long*)h.data != 50)
		failed = 1;
	printf("heap_change_value larger test\t\t\t\t%s\n", failed?RED_TEXT"FAILED"RESET_TEXT:GREEN_TEXT"PASSED"RESET_TEXT);
	if(failed)
		return 0;
	
	new_value = -50;
	heap_change_value(&h, _test_comp, 0, &new_value);
	while(heap_extract_max(&h, _test_comp) != NULL);
	
	if(*(long*)h.data != -50)
		failed = 1;	
	printf("heap_change_value smaller test\t\t\t\t%s\n", failed?RED_TEXT"FAILED"RESET_TEXT:GREEN_TEXT"PASSED"RESET_TEXT);
	if(failed)
		return 0;

  	return 0;
}
