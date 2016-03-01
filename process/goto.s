	.file	"goto.c"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"Inside doJump(): nvar=%d rvar=%d vvar=%d\n"
	.align 8
.LC1:
	.string	"after longjmp(): nvar=%d rvar=%d vvar=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movl	$333, 12(%rsp)
	movl	$env, %edi
	call	_setjmp
	testl	%eax, %eax
	jne	.L4
	movl	$999, 12(%rsp)
	movl	12(%rsp), %ecx
	movl	$888, %edx
	movl	$777, %esi
	movl	$.LC0, %edi
	call	printf
	movl	$1, %esi
	movl	$env, %edi
	call	longjmp
.L4:
	movl	12(%rsp), %ecx
	movl	$222, %edx
	movl	$111, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %edi
	call	exit
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.local	env
	.comm	env,200,32
	.ident	"GCC: (Debian 5.3.1-5) 5.3.1 20160101"
	.section	.note.GNU-stack,"",@progbits
