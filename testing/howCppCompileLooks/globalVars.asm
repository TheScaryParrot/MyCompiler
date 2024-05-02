	.file	"globalVars.cpp"
	.text
	.section	.text._ZN8MY_CLASS11PUBLIC_FUNCEv,"axG",@progbits,_ZN8MY_CLASS11PUBLIC_FUNCEv,comdat
	.align 2
	.weak	_ZN8MY_CLASS11PUBLIC_FUNCEv
	.type	_ZN8MY_CLASS11PUBLIC_FUNCEv, @function
_ZN8MY_CLASS11PUBLIC_FUNCEv:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_ZN8MY_CLASS11PUBLIC_FUNCEv, .-_ZN8MY_CLASS11PUBLIC_FUNCEv
	.globl	INT
	.data
	.align 4
	.type	INT, @object
	.size	INT, 4
INT:
	.long	10
	.globl	OBJECT_NONE
	.bss
	.align 8
	.type	OBJECT_NONE, @object
	.size	OBJECT_NONE, 12
OBJECT_NONE:
	.zero	12
	.globl	OBJECT_STACK
	.align 8
	.type	OBJECT_STACK, @object
	.size	OBJECT_STACK, 12
OBJECT_STACK:
	.zero	12
	.globl	OBJECT_HEAP
	.align 8
	.type	OBJECT_HEAP, @object
	.size	OBJECT_HEAP, 8
OBJECT_HEAP:
	.zero	8
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	movl	$20, -4(%rbp)
	movq	OBJECT_NONE(%rip), %rax
	movq	%rax, -28(%rbp)
	movl	8+OBJECT_NONE(%rip), %eax
	movl	%eax, -20(%rbp)
	leaq	-28(%rbp), %rax
	movq	%rax, %rdi
	call	_ZN8MY_CLASS11PUBLIC_FUNCEv
	movl	-28(%rbp), %eax
	movl	%eax, -8(%rbp)
	movq	OBJECT_STACK(%rip), %rax
	movq	%rax, -40(%rbp)
	movl	8+OBJECT_STACK(%rip), %eax
	movl	%eax, -32(%rbp)
	movq	OBJECT_HEAP(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	INT(%rip), %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L7
	cmpl	$65535, -8(%rbp)
	jne	.L7
	movl	$12, %edi
	call	_Znwm@PLT
	movl	$0, (%rax)
	movl	$0, 4(%rax)
	movl	$0, 8(%rax)
	movq	%rax, OBJECT_HEAP(%rip)
.L7:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I_INT, @function
_GLOBAL__sub_I_INT:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	_GLOBAL__sub_I_INT, .-_GLOBAL__sub_I_INT
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_INT
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
