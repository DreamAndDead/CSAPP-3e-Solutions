# void test(long i, b_struct *bp)
# i in %rdi, bp in %rsi
test:
  mov 0x120(%rsi), %ecx         # bp+0x120 fetch bp->last
  add (%rsi), %ecx              # bp->first + bp->last
  lea (%rdi,%rdi,4), %rax       # i*5
  lea (%rsi,%rax,8), %rax       # bp+i*40

  # ap = &bp->a[i] = bp+i*40+8, +8 means skip int first
  # so a_struct is aligned by 8, size is 40
  # check last instrction, %rdx here saves value ap->idx!!!
  # so in a_struct, idx is first element
  mov 0x8(%rax), %rdx

  movslq %ecx, %rcx             # n = bp->first + bp->last, convert to long

  # save n to address 8*(ap->idx) + bp+i*40+0x8 + 0x8  (0x10)
  # bp+i*40+0x8 means ap
  # ap + 0x8 means &(ap->x)
  # ap + 0x8 + 8*(ap->idx) means &(ap-x[ap->idx])
  # second element of a_struct is x, x is an array of long
  # 8*(ap->idx) means idx is also long type
  mov %rcx, 0x10(%rax,%rdx,8)

  # size of a_struct is 40 and aligned by 8
  # so array x has 4 long elements
  # finally, a_struct is
  #   typedef struct {
  #     long idx,
  #     long x[4]
  #   } a_struct
  retq
