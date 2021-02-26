# void proc(union ele *up)
# up in %rdi
proc:
  # %rax = *(up+8), don't know it's next or y
  movq 8(%rdi), %rax

  # %rdx = *( *(up+8) ), %rax stands for a pointer
  # so *( *(up+8) ) means *(up->e2.next)
  movq (%rax), %rdx

  # %rdx = *( *(up->e2.next) )
  # %rdx is treated as a pointer
  # so %rdx stores *( *(up->e2.next).e1.p )
  movq (%rdx), %rdx

  # %rax stores *(up+8)
  # %rax is treated as a pointer
  # so %rax = *( up->e2.next ), stands for another union ele's address
  #
  # in subq, %rdx is a long number
  # *( *(up->e2.next)+8 ) must be a long number
  # so 8(%rax) means *(up->e2.next).e1.y
  subq 8(%rax), %rdx

  # %rdi never changes in previous instrctions
  # instrction below is the final assignment
  # so (%rdi) means up->e2.x
  movq %rdx, (%rdi)
  ret
