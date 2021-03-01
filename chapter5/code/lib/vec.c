/*
 * vec.c
 */
#include <stdlib.h>
#include "./vec.h"

/* Create vector of specific length */
vec_ptr new_vec(long len) {
  /* allocate header structure */
  vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
  if (!result)
    return result;

  result->len = len;
  data_t *data = NULL;
  /* allocate array */
  if (len > 0) {
    data = (data_t*) calloc(len, sizeof(data_t));
    if (!data) {
      free((void*) result);
      return NULL;
    }
  }
  result->data = data;
  return result;
}

/*
 * Retrieve vector element and store at dest
 * return 0 (out of bounds) or 1 (successful)
 */
int get_vec_element(vec_ptr v, long index, data_t *dest) {
  if (index < 0 || index >= v->len) {
    return 0;
  }
  *dest = v->data[index];
  return 1;
}

/* return length of vector */
long vec_length(vec_ptr v) {
  return v->len;
}

/* expose data */
data_t* get_vec_start(vec_ptr v) {
  return v->data;
}

/* set data */
void set_vec_start(vec_ptr v, data_t *data) {
  v->data = data;
}
