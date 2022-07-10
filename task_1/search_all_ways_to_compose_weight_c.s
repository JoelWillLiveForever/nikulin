	.file	"search_all_ways_to_compose_weight.c"
	.text
	.globl	saved_hashsums
	.bss
	.align 32
	.type	saved_hashsums, @object
	.size	saved_hashsums, 100
saved_hashsums:
	.zero	100
	.globl	saved_hashsums_curr_index
	.align 4
	.type	saved_hashsums_curr_index, @object
	.size	saved_hashsums_curr_index, 4
saved_hashsums_curr_index:
	.zero	4
	.text
	.globl	search_all_ways_recursive
	.type	search_all_ways_recursive, @function
search_all_ways_recursive:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$136, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -116(%rbp)
	movl	%esi, -120(%rbp)
	movq	%rdx, -128(%rbp)
	movl	%ecx, -132(%rbp)
	movq	%r8, -144(%rbp)
	movl	%r9d, -136(%rbp)
	movl	-120(%rbp), %eax
	subl	%eax, -116(%rbp)
	cmpl	$0, -116(%rbp)
	jne	.L2
	movl	$0, -52(%rbp)
	jmp	.L3
.L6:
	movl	-52(%rbp), %eax
	cltq
	movl	saved_hashsums(,%rax,4), %eax
	cmpl	%eax, -132(%rbp)
	jne	.L4
	movl	$0, %eax
	jmp	.L5
.L4:
	addl	$1, -52(%rbp)
.L3:
	cmpl	$24, -52(%rbp)
	jle	.L6
	movl	saved_hashsums_curr_index(%rip), %eax
	cltq
	movl	-132(%rbp), %edx
	movl	%edx, saved_hashsums(,%rax,4)
	movl	saved_hashsums_curr_index(%rip), %eax
	addl	$1, %eax
	movl	%eax, saved_hashsums_curr_index(%rip)
	movl	$1, %eax
	jmp	.L5
.L2:
	cmpl	$0, -116(%rbp)
	jns	.L7
	movl	$0, %eax
	jmp	.L5
.L7:
	movl	$0, -56(%rbp)
	movl	-136(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -72(%rbp)
	movl	$0, -60(%rbp)
	jmp	.L8
.L13:
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -80(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -88(%rbp)
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -96(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -160(%rbp)
	movq	$0, -152(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -176(%rbp)
	movq	$0, -168(%rbp)
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -104(%rbp)
	movl	$0, -64(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L9
.L12:
	movl	-60(%rbp), %eax
	cmpl	-68(%rbp), %eax
	je	.L14
	movl	-68(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-128(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-88(%rbp), %rax
	movl	-64(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	-68(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-144(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-104(%rbp), %rax
	movl	-64(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -64(%rbp)
	jmp	.L11
.L14:
	nop
.L11:
	addl	$1, -68(%rbp)
.L9:
	movl	-68(%rbp), %eax
	cmpl	-136(%rbp), %eax
	jl	.L12
	movl	-60(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-128(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -108(%rbp)
	movl	-60(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-144(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-132(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -112(%rbp)
	movl	-72(%rbp), %eax
	movq	-104(%rbp), %rdx
	movl	-112(%rbp), %ecx
	movq	-88(%rbp), %rsi
	movl	-108(%rbp), %edi
	movl	-116(%rbp), %r10d
	movl	%eax, %r9d
	movq	%rdx, %r8
	movq	%rsi, %rdx
	movl	%edi, %esi
	movl	%r10d, %edi
	call	search_all_ways_recursive
	addl	%eax, -56(%rbp)
	movq	%rbx, %rsp
	addl	$1, -60(%rbp)
.L8:
	movl	-60(%rbp), %eax
	cmpl	-136(%rbp), %eax
	jl	.L13
	movl	-56(%rbp), %eax
.L5:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	search_all_ways_recursive, .-search_all_ways_recursive
	.section	.rodata
.LC0:
	.string	"Rus"
	.align 8
.LC1:
	.string	"\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\270\321\201\320\272\320\276\320\274\321\213\320\271 \320\262\320\265\321\201 V \320\262 \320\263\321\200\320\260\320\274\320\274\320\260\321\205 \320\270\320\267 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 [100..11200]: "
.LC2:
	.string	"%d"
	.align 8
.LC3:
	.string	"\320\235\320\260\320\271\320\264\320\265\320\275\320\276 \321\201\320\277\320\276\321\201\320\276\320\261\320\276\320\262: 0. \320\243\320\272\320\260\320\267\320\260\320\275\320\275\321\213\320\271 \320\262\320\260\320\274\320\270 \320\270\321\201\320\272\320\276\320\274\321\213\320\271 \320\262\320\265c \320\262: %d \320\263\321\200\320\260\320\274\320\274 \320\262\321\213\321\205\320\276\320\264\320\270\321\202 \320\267\320\260 \321\200\320\260\320\274\320\272\320\270 \320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276\320\263\320\276 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 [100..11200]!\n"
	.align 8
.LC4:
	.string	"\320\235\320\260\320\271\320\264\320\265\320\275\320\276 \321\201\320\277\320\276\321\201\320\276\320\261\320\276\320\262: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$216, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	$.LC0, %esi
	movl	$6, %edi
	call	setlocale
	movl	$100, -160(%rbp)
	movl	$200, -156(%rbp)
	movl	$300, -152(%rbp)
	movl	$500, -148(%rbp)
	movl	$1000, -144(%rbp)
	movl	$1200, -140(%rbp)
	movl	$1400, -136(%rbp)
	movl	$1500, -132(%rbp)
	movl	$2000, -128(%rbp)
	movl	$3000, -124(%rbp)
	movl	$55, -208(%rbp)
	movl	$23, -204(%rbp)
	movl	$421, -200(%rbp)
	movl	$90, -196(%rbp)
	movl	$10, -192(%rbp)
	movl	$4, -188(%rbp)
	movl	$-8, -184(%rbp)
	movl	$92, -180(%rbp)
	movl	$67, -176(%rbp)
	movl	$111, -172(%rbp)
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	leaq	-212(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-212(%rbp), %eax
	cmpl	$99, %eax
	jle	.L16
	movl	-212(%rbp), %eax
	cmpl	$11200, %eax
	jle	.L17
.L16:
	movl	-212(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	jmp	.L25
.L17:
	movl	$0, -52(%rbp)
	movl	$10, -68(%rbp)
	movl	-68(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -72(%rbp)
	movl	$0, -56(%rbp)
	jmp	.L19
.L24:
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -80(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, %r12
	movl	$0, %r13d
	movslq	%eax, %rdx
	movq	%rdx, %r14
	movl	$0, %r15d
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %ecx
	movl	$0, %edx
	divq	%rcx
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -88(%rbp)
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -96(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -240(%rbp)
	movq	$0, -232(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -256(%rbp)
	movq	$0, -248(%rbp)
	cltq
	leaq	0(,%rax,4), %rdx
	movl	$16, %eax
	subq	$1, %rax
	addq	%rdx, %rax
	movl	$16, %esi
	movl	$0, %edx
	divq	%rsi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -104(%rbp)
	movl	$0, -60(%rbp)
	movl	$0, -64(%rbp)
	jmp	.L20
.L23:
	movl	-56(%rbp), %eax
	cmpl	-64(%rbp), %eax
	je	.L26
	movl	-64(%rbp), %eax
	cltq
	movl	-160(%rbp,%rax,4), %ecx
	movq	-88(%rbp), %rax
	movl	-60(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	-64(%rbp), %eax
	cltq
	movl	-208(%rbp,%rax,4), %ecx
	movq	-104(%rbp), %rax
	movl	-60(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -60(%rbp)
	jmp	.L22
.L26:
	nop
.L22:
	addl	$1, -64(%rbp)
.L20:
	movl	-64(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L23
	movl	-56(%rbp), %eax
	cltq
	movl	-160(%rbp,%rax,4), %eax
	movl	%eax, -108(%rbp)
	movl	-56(%rbp), %eax
	cltq
	movl	-208(%rbp,%rax,4), %eax
	movl	%eax, -112(%rbp)
	movl	-212(%rbp), %r10d
	movl	-72(%rbp), %eax
	movq	-104(%rbp), %rdx
	movl	-112(%rbp), %ecx
	movq	-88(%rbp), %rsi
	movl	-108(%rbp), %edi
	movl	%eax, %r9d
	movq	%rdx, %r8
	movq	%rsi, %rdx
	movl	%edi, %esi
	movl	%r10d, %edi
	call	search_all_ways_recursive
	addl	%eax, -52(%rbp)
	movq	%rbx, %rsp
	addl	$1, -56(%rbp)
.L19:
	movl	-56(%rbp), %eax
	cmpl	-68(%rbp), %eax
	jl	.L24
	movl	-52(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
.L25:
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 12.1.1 20220507 (Red Hat 12.1.1-1)"
	.section	.note.GNU-stack,"",@progbits
