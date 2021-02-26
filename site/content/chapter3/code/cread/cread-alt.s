# long cread_alt(long* xp)
# xp in %rdi
cread_alt:
  movl $0, %eax
  testq %rdi, %rdi
  cmovne (%rdi), %rax
