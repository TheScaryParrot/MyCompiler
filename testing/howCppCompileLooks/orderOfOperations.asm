	.file	"orderOfOperations.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$3, -4(%rbp)
	movl	$2, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	-8(%rbp), %eax
	leal	5(%rax), %edx
	movl	-4(%rbp), %eax
	subl	$3, %eax
	imull	%edx, %eax
	movl	-4(%rbp), %edx
	leal	-3(%rdx), %ecx
	movl	-12(%rbp), %edx
	addl	$5, %edx
	imull	%edx, %ecx
	movl	-8(%rbp), %edx
	addl	%ecx, %edx
	imull	%edx, %eax
	movl	%eax, -16(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
