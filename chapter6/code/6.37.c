/*
 * 6.37.c
 */

typedef int array_t[N][N];

int sumA(array_t a) {
  int i, j;
  int sum = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      sum += a[i][j];

  return sum;
}

int sumB(array_t a) {
  int i, j;
  int sum = 0;
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      sum += a[j][i];

  return sum;
}

int sumC(array_t a) {
  int i, j;
  int sum = 0;
  for (i = 0; i < N; i+=2)
    for (j = 0; j < N; j+=2)
      sum += (a[j][i] + a[j][i+1] + a[j+1][i] + a[j+1][i+1])
}
