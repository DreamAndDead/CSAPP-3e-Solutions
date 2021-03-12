# void store_prod(int128_t* dest, int64_t x, int64_t y)
# dest in %rdi, x in %rsi, y in %rdx
store_prod:
  movq %rdx, %rax     # %rax = y
  cqto                # (int128_t)y, %rdx = (-1)y_63
  movq %rsi, %rcx     # %rcx = x

  # x >> 63, if x == 1, %rcx = -1; if x_63 == 0, %rcx = 0
  # %rcx = (-1)x_63
  sarq $63, %rcx

  # pay attention, imulq behaves differently according to param number(1/2)
  imulq %rax, %rcx    # %rcx = y * -x_63
  imulq %rsi, %rdx    # %rdx = x * -y_63
  addq %rdx, %rcx     # %rcx = x * -y_63 + y * -x_63
  mulq %rsi           # %rdx:%rax <= ux * uy

  # lower 64 bits are same for x * y and ux * uy. ref (2.18) on book
  # %rdx = ux * uy(high 64 bits) - (x_{63}y + y_{63}x)2^{64}
  addq %rcx, %rdx

  movq %rax, (%rdi)   # set lower 64bits
  movq %rdx, 8(%rdi)  # set higher 64bits
  ret
