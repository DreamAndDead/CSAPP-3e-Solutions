/*
 * bubble-sort-array.c
 */

void bubble_a(long* data, long count) {
  long i, last;
  for (last = count-1; last > 0; last--) {
    for (i = 0; i < last; i++) {
      if (data[i+1] < data[i]) {
        /* swap adjacent elements */
        long t = data[i+1];
        data[i+1] = data[i];
        data[i] = t;
      }
    }
  }
}
