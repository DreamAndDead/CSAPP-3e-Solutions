# long cread(long *xp)
# xp in %rdi
cread:
  movq (%rdi), %rax
  testq %rdi, %rdi
  movl $0, %edx
  cmove %rdx, %rax
  ret
