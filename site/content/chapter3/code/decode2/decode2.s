# long decode2(long x, long y, long z)
# %rdi x, %rsi y, %rdx z
.section .text
.global decode2
decode2:
  subq %rdx, %rsi
  imulq %rsi, %rdi
  movq %rsi, %rax
  salq $63, %rax
  sarq $63, %rax
  xorq %rdi, %rax
  ret

