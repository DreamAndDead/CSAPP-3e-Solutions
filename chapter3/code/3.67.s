# strB process(strA s)
# s in %rdi
process:
  movq %rdi, %rax
  movq 24(%rsp), %rdx
  movq (%rdx), %rdx
  movq 16(%rsp), %rcx
  movq %rcx, (%rdi)
  movq 8(%rsp), %rcx
  movq %rcx, 8(%rdi)
  movq %rdx, 16(%rdi)
  ret

# long eval(long x, long y, long z)
# x in %rdi, y in %rsi, z in %rdx
eval:
  subq $104, %rsp
  movq %rdx, 24(%rsp)
  leaq 24(%rsp), %rax
  movq %rdi, (%rsp)
  movq %rsi, 8(%rsp)
  movq %rax, 16(%rsp)
  leaq 64(%rsp), %rdi
  call process
  movq 72(%rsp), %rax
  addq 64(%rsp), %rax
  addq 80(%rsp), %rax
  addq $104, %rsp
  ret
