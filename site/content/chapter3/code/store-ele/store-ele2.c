/*
 * store-ele2.c
 */
#define R 7
#define S 5
#define T 13

long A2[R][S][T];

long store_ele2(long i, long j, long k, long* dest) {
  *dest = A2[i][j][k];
  return sizeof(A2);
}
