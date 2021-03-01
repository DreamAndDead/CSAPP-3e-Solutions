/*
 * 5.13.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "./lib/vec.h"

/* inner product. accumulate in temporary */
void inner4(vec_ptr u, vec_ptr v, data_t *dest) {
  long i;
  long length = vec_length(u);
  data_t *udata = get_vec_start(u);
  data_t *vdata = get_vec_start(v);
  data_t sum = (data_t) 0;

  for (i = 0; i < length; i++) {
    sum = sum + udata[i] * vdata[i];
  }
  *dest = sum;
}

int main(int argc, char* argv[]) {
  vec_ptr u = new_vec(4);
  vec_ptr v = new_vec(4);

  data_t *arr = (data_t*) malloc(sizeof(data_t) * 4);
  arr[0] = 0;
  arr[1] = 1;
  arr[2] = 2;
  arr[3] = 3;

  set_vec_start(u, arr);
  set_vec_start(v, arr);

  data_t res;
  inner4(u, v, &res);

  assert(res == 1+4+9);
  return 0;
}


