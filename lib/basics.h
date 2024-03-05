#ifndef __BASICS_H__
#define __BASICS_H__

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

#define RED_TEXT "\033[91m"
#define GREEN_TEXT "\033[92m"
#define RESET_TEXT "\033[0m"

#define MAX_KEYSIZE 50

#define generic_at(arr, i) ((arr)+stride*(i))
#define generic_assign(to, from) memcpy(to, from, stride)
#define generic_xchg(a, b) do{\
  uint8_t tmp[MAX_KEYSIZE];\
  assert(MAX_KEYSIZE>=stride && "Type to be sorted is to big.");\
  generic_assign(tmp, a); generic_assign(a, b); generic_assign(b, tmp);\
}while(0)

typedef int compare_fn_t(const void *a, const void *b);
typedef void sort_fn_t(void *a, size_t len, size_t stride, compare_fn_t comp_fn);

#endif
