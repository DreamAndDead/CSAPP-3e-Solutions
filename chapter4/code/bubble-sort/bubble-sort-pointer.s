	.file	"bubble-sort-pointer.c"
	.text
	.globl	bubble_p
	.type	bubble_p, @function
bubble_p:
.LFB0:
	.cfi_startproc
	leaq	-8(%rdi,%rsi,8), %rsi
	jmp	.L2
.L4:
	movq	8(%rax), %rdx
	movq	(%rax), %rcx
	cmpq	%rcx, %rdx
	jge	.L3
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
.L3:
	addq	$8, %rax
	jmp	.L5
.L6:
	movq	%rdi, %rax
.L5:
	cmpq	%rsi, %rax
	jb	.L4
	subq	$8, %rsi
.L2:
	cmpq	%rdi, %rsi
	ja	.L6
	rep ret
	.cfi_endproc
.LFE0:
	.size	bubble_p, .-bubble_p
	.ident	"GCC: (Gentoo 4.9.4 p1.0, pie-0.6.4) 4.9.4"
	.section	.note.GNU-stack,"",@progbits
