.section .text
.global sum_col
# long sum_col(long n, long A[NR(n)][NC(n)], long j)
# n in %rdi, A in %rsi, j in %rdx
sum_col:
  leaq 1(,%rdi,4), %r8        # t1 = n*4 + 1
  leaq (%rdi,%rdi,2), %rax    # t2 = n*3
  movq %rax, %rdi             # t3 = n*3
  testq %rax, %rax            # test n*3
  jle .L4                     # n*3 <= 0, jump .L4
  salq $3, %r8                # t1 = t1*8 = 8*(n*4 + 1)
  leaq (%rsi,%rdx,8), %rcx    # t4 = j*8 + A
  movl $0, %eax               # t2 = 0
  movl $0, %edx               # t5 = 0
.L3:
  addq (%rcx), %rax           # t2 = *(t4) = *(A + j*8)
  addq $1, %rdx               # t5 = t5+1
  addq %r8, %rcx              # t4 = t1+t4 = A + j*8 + 8*(n*4 + 1)
  cmpq %rdi, %rdx             # cmp t5 & t3
  jne .L3                     # if t5 != n*3, loop
  rep
  ret
.L4:
  movl $0, %eax               # return 0
  ret
