/*
 * 5.19.c
 */
#include <stdio.h>
#include <assert.h>

void psum1a(float a[], float p[], long n) {
  long i;
  float last_val, val;
  last_val = p[0] = a[0];
  for (i = 1; i < n; i++) {
    val = last_val + a[i];
    p[i] = val;
    last_val = val;
  }
}

/* version 4*1a */
void psum_4_1a(float a[], float p[], long n) {
  long i;
  float val, last_val;
  float tmp, tmp1, tmp2, tmp3;
  last_val = p[0] = a[0];

  for (i = 1; i < n - 4; i++) {
    tmp = last_val + a[i];
    tmp1 = tmp + a[i+1];
    tmp2 = tmp1 + a[i+2];
    tmp3 = tmp2 + a[i+3];

    p[i] = tmp;
    p[i+1] = tmp1;
    p[i+2] = tmp2;
    p[i+3] = tmp3;

    /* key point */
    last_val = last_val + (a[i] + a[i+1] + a[i+2] + a[i+3]);
  }

  for (; i < n; i++) {
    last_val += a[i];
    p[i] = last_val;
  }
}

#define LOOP 1000
#define LEN  1000

int main(int argc, char* argv[]) {
  float a[5] = { 1, 2, 3, 4, 5 };
  float p[5];
  psum1a(a, p, 5);
  assert(p[4] == 15);

  float q[5];
  psum_4_1a(a, q, 5);
  assert(q[4] == 15);

  /* for prof */
  for (int i = 0; i < LOOP; i++) {
    float s[LEN];
    float d[LEN];
    psum1a(s, d, LEN);
    psum_4_1a(s, d, LEN);
  }
  return 0;
}


