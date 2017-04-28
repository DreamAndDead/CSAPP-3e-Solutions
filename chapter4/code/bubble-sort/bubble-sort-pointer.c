/*
 * bubble-sort-pointer.c
 */

void bubble_p(long* data, long count) {
  long *i, *last;
  for (last = data+count-1; last > data; last--) {
    for (i = data; i < last; i++) {
      if (*(i+1) < *i) {
        /* swap adjacent elements */
        long t = *(i+1);
        *(i+1) = *i;
        *i = t;
      }
    }
  }
}

