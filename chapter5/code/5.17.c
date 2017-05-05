/*
 * 5.17.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SPACE (size_t)125

void* basic_memset(void *s, int c, size_t n) {
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n) {
    *schar++ = (unsigned char) c;
    cnt++;
  }
  return s;
}

/*
 * K = sizeof(unsigned long)
 * cs store K chars for memset
 */
void* effective_memset(void *s, unsigned long cs, size_t n) {
  /* align to K */
  size_t K = sizeof(unsigned long);
  size_t cnt = 0;
  unsigned char *schar = s;
  while (cnt < n) {
    if ((size_t)schar % K == 0) {
      break;
    }
    *schar++ = (unsigned char)cs;
    cnt++;
  }
  /* store K chars one time */
  unsigned long *slong = (unsigned long *)schar;
  /* not cnt < n-K */
  for (; cnt + K < n; cnt += K) {
    *slong++ = cs;
  }
  /* store the rest */
  schar = (unsigned char *)slong;
  for (; cnt < n; cnt++) {
    *schar++ = (unsigned char)cs;
  }
  return s;
}


int main(int argc, char* argv[]) {
  void* basic_space = malloc(SPACE);
  void* effective_space = malloc(SPACE);

  int basic_fill = 0xFF;
  unsigned long effective_fill = ~0;

  basic_memset(basic_space, basic_fill, SPACE);
  effective_memset(effective_space, effective_fill, SPACE);

  assert(memcmp(basic_space, effective_space, SPACE) == 0);
  return 0;
}


