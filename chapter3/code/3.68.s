# void setVal(str1* p, str2* q)
# p in %rdi, q in %rsi
setVal:
  # 8(%rsi) fetch q->t, int t is aligned by 4, so 4 < B <=8
  movslq 8(%rsi), %rax

  # 32(%rsi) fetch q->u, long u is aligned by 8
  # offset q->s is offset q->t + 4, so 24 < 12 + A*2 <= 32
  addq 32(%rsi), %rax

  # 184(%rdi) fetch p->v, long y is aligned by 8, so 176 < A*B*4 <= 184
  movq %rax, 184(%rdi)
  ret
