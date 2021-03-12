# long aframe(long n, long idx, long *q)
# n in %rdi, idx in %rsi, q in %rdx
aframe:
  pushq %rbp
  movq %rsp, %rbp
  subq $16, %rsp
  leaq 30(,%rdi,8), %rax
  andq $-16, %rax
  subq %rax, %rsp
  leaq 15(%rsp), %r8
  andq $-16, %r8
