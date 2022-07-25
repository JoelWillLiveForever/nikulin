	.file	"weight_combinations_detail.c"
	.text
	.globl	saved_roots
	.bss
	.align 32
	.type	saved_roots, @object
	.size	saved_roots, 40
saved_roots:
	.zero	40
	.globl	counter
	.data
	.align 4
	.type	counter, @object
	.size	counter, 4
counter:
	.long	-1
	.globl	saved
	.bss
	.align 32
	.type	saved, @object
	.size	saved, 4000
saved:
	.zero	4000
	.globl	saved_hashsums
	.align 32
	.type	saved_hashsums, @object
	.size	saved_hashsums, 400
saved_hashsums:
	.zero	400
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
	subq	$152, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	%edi, -132(%rbp)
	movl	%esi, -136(%rbp)
	movq	%rdx, -144(%rbp)
	movl	%ecx, -148(%rbp)
	movq	%r8, -160(%rbp)
	movl	%r9d, -152(%rbp)
	movl	counter(%rip), %eax
	addl	$1, %eax
	movl	%eax, counter(%rip)
	movl	counter(%rip), %eax
	cltq
	movl	-136(%rbp), %edx
	movl	%edx, saved_roots(,%rax,4)
	movl	-136(%rbp), %eax
	subl	%eax, -132(%rbp)
	cmpl	$0, -132(%rbp)
	jne	.L2
	movl	$0, -52(%rbp)
	jmp	.L3
.L6:
	movl	-52(%rbp), %eax
	cltq
	movl	saved_hashsums(,%rax,4), %eax
	cmpl	%eax, -148(%rbp)
	jne	.L4
	movl	counter(%rip), %eax
	cltq
	movl	$0, saved_roots(,%rax,4)
	movl	counter(%rip), %eax
	subl	$1, %eax
	movl	%eax, counter(%rip)
	movl	$0, %eax
	jmp	.L5
.L4:
	addl	$1, -52(%rbp)
.L3:
	cmpl	$99, -52(%rbp)
	jle	.L6
	movl	saved_hashsums_curr_index(%rip), %eax
	cltq
	movl	-148(%rbp), %edx
	movl	%edx, saved_hashsums(,%rax,4)
	movl	saved_hashsums_curr_index(%rip), %eax
	addl	$1, %eax
	movl	%eax, saved_hashsums_curr_index(%rip)
	movl	$0, -56(%rbp)
	jmp	.L7
.L13:
	movl	-56(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	salq	$3, %rax
	addq	$saved, %rax
	movl	(%rax), %eax
	testl	%eax, %eax
	jne	.L22
	movl	$0, -60(%rbp)
	jmp	.L10
.L11:
	movl	-60(%rbp), %eax
	cltq
	movl	saved_roots(,%rax,4), %ecx
	movl	-60(%rbp), %eax
	movslq	%eax, %rsi
	movl	-56(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rsi, %rax
	movl	%ecx, saved(,%rax,4)
	addl	$1, -60(%rbp)
.L10:
	cmpl	$9, -60(%rbp)
	jle	.L11
	jmp	.L12
.L22:
	nop
	addl	$1, -56(%rbp)
.L7:
	cmpl	$99, -56(%rbp)
	jle	.L13
.L12:
	movl	counter(%rip), %eax
	cltq
	movl	$0, saved_roots(,%rax,4)
	movl	counter(%rip), %eax
	subl	$1, %eax
	movl	%eax, counter(%rip)
	movl	$1, %eax
	jmp	.L5
.L2:
	cmpl	$0, -132(%rbp)
	jns	.L14
	movl	counter(%rip), %eax
	cltq
	movl	$0, saved_roots(,%rax,4)
	movl	counter(%rip), %eax
	subl	$1, %eax
	movl	%eax, counter(%rip)
	movl	$0, %eax
	jmp	.L5
.L14:
	movl	$0, -64(%rbp)
	movl	-152(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -80(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L15
.L20:
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -88(%rbp)
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
	movl	$16, %edi
	movl	$0, %edx
	divq	%rdi
	imulq	$16, %rax, %rax
	subq	%rax, %rsp
	movq	%rsp, %rax
	addq	$3, %rax
	shrq	$2, %rax
	salq	$2, %rax
	movq	%rax, -96(%rbp)
	movl	-80(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -104(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -176(%rbp)
	movq	$0, -168(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -192(%rbp)
	movq	$0, -184(%rbp)
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
	movq	%rax, -112(%rbp)
	movl	$0, -72(%rbp)
	movl	$0, -76(%rbp)
	jmp	.L16
.L19:
	movl	-68(%rbp), %eax
	cmpl	-76(%rbp), %eax
	je	.L23
	movl	-76(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-144(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-96(%rbp), %rax
	movl	-72(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	-76(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-160(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-112(%rbp), %rax
	movl	-72(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -72(%rbp)
	jmp	.L18
.L23:
	nop
.L18:
	addl	$1, -76(%rbp)
.L16:
	movl	-76(%rbp), %eax
	cmpl	-152(%rbp), %eax
	jl	.L19
	movl	-68(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-144(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -116(%rbp)
	movl	-68(%rbp), %eax
	cltq
	leaq	0(,%rax,4), %rdx
	movq	-160(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %edx
	movl	-148(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -120(%rbp)
	movl	-80(%rbp), %eax
	movq	-112(%rbp), %rdx
	movl	-120(%rbp), %ecx
	movq	-96(%rbp), %rsi
	movl	-116(%rbp), %edi
	movl	-132(%rbp), %r10d
	movl	%eax, %r9d
	movq	%rdx, %r8
	movq	%rsi, %rdx
	movl	%edi, %esi
	movl	%r10d, %edi
	call	search_all_ways_recursive
	addl	%eax, -64(%rbp)
	movq	%rbx, %rsp
	addl	$1, -68(%rbp)
.L15:
	movl	-68(%rbp), %eax
	cmpl	-152(%rbp), %eax
	jl	.L20
	movl	counter(%rip), %eax
	cltq
	movl	$0, saved_roots(,%rax,4)
	movl	counter(%rip), %eax
	subl	$1, %eax
	movl	%eax, counter(%rip)
	movl	-64(%rbp), %eax
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
	.string	"\n\320\245\321\215\321\210 \320\272\320\276\320\264 \320\262 \321\201\320\276\320\276\321\202\320\262\320\265\321\202\321\201\321\202\320\262\320\270\320\270 \321\201 \320\272\320\260\320\266\320\264\320\276\320\271 \320\263\320\270\321\200\320\265\320\271. \320\223\320\270\321\200\321\217: %4d == \320\245\321\215\321\210: %4d"
	.align 8
.LC2:
	.string	"\n\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\270\321\201\320\272\320\276\320\274\321\213\320\271 \320\262\320\265\321\201 V \320\262 \320\263\321\200\320\260\320\274\320\274\320\260\321\205 \320\270\320\267 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 [100..11200]: "
.LC3:
	.string	"%d"
	.align 8
.LC4:
	.string	"\320\235\320\260\320\271\320\264\320\265\320\275\320\276 \321\201\320\277\320\276\321\201\320\276\320\261\320\276\320\262: 0. \320\243\320\272\320\260\320\267\320\260\320\275\320\275\321\213\320\271 \320\262\320\260\320\274\320\270 \320\270\321\201\320\272\320\276\320\274\321\213\320\271 \320\262\320\265c \320\262: %d \320\263\321\200\320\260\320\274\320\274 \320\262\321\213\321\205\320\276\320\264\320\270\321\202 \320\267\320\260 \321\200\320\260\320\274\320\272\320\270 \320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276\320\263\320\276 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 [100..11200]!\n"
	.align 8
.LC5:
	.string	"\nsaved_hashsums[%d] = %6d\tsaved_roots[%d]: "
.LC6:
	.string	"%6d"
	.align 8
.LC7:
	.string	"\n\n\320\235\320\260\320\271\320\264\320\265\320\275\320\276 \321\201\320\277\320\276\321\201\320\276\320\261\320\276\320\262: %d\n"
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
	subq	$232, %rsp
	.cfi_offset 15, -24
	.cfi_offset 14, -32
	.cfi_offset 13, -40
	.cfi_offset 12, -48
	.cfi_offset 3, -56
	movl	$.LC0, %esi
	movl	$6, %edi
	call	setlocale
	movl	$100, -176(%rbp)
	movl	$200, -172(%rbp)
	movl	$300, -168(%rbp)
	movl	$500, -164(%rbp)
	movl	$1000, -160(%rbp)
	movl	$1200, -156(%rbp)
	movl	$1400, -152(%rbp)
	movl	$1500, -148(%rbp)
	movl	$2000, -144(%rbp)
	movl	$3000, -140(%rbp)
	movl	$55, -224(%rbp)
	movl	$23, -220(%rbp)
	movl	$421, -216(%rbp)
	movl	$90, -212(%rbp)
	movl	$10, -208(%rbp)
	movl	$4, -204(%rbp)
	movl	$-8, -200(%rbp)
	movl	$92, -196(%rbp)
	movl	$67, -192(%rbp)
	movl	$111, -188(%rbp)
	movl	$0, -52(%rbp)
	jmp	.L25
.L26:
	movl	-52(%rbp), %eax
	cltq
	movl	-224(%rbp,%rax,4), %edx
	movl	-52(%rbp), %eax
	cltq
	movl	-176(%rbp,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -52(%rbp)
.L25:
	cmpl	$9, -52(%rbp)
	jle	.L26
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	leaq	-228(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	__isoc99_scanf
	movl	-228(%rbp), %eax
	cmpl	$99, %eax
	jle	.L27
	movl	-228(%rbp), %eax
	cmpl	$11200, %eax
	jle	.L28
.L27:
	movl	-228(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	jmp	.L40
.L28:
	movl	$0, -56(%rbp)
	movl	$10, -80(%rbp)
	movl	-80(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -84(%rbp)
	movl	$10, %edi
	call	putchar
	movl	$0, -60(%rbp)
	jmp	.L30
.L35:
	movq	%rsp, %rax
	movq	%rax, %rbx
	movl	-84(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -96(%rbp)
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
	movq	%rax, -104(%rbp)
	movl	-84(%rbp), %eax
	movslq	%eax, %rdx
	subq	$1, %rdx
	movq	%rdx, -112(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -256(%rbp)
	movq	$0, -248(%rbp)
	movslq	%eax, %rdx
	movq	%rdx, -272(%rbp)
	movq	$0, -264(%rbp)
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
	movq	%rax, -120(%rbp)
	movl	$0, -64(%rbp)
	movl	$0, -68(%rbp)
	jmp	.L31
.L34:
	movl	-60(%rbp), %eax
	cmpl	-68(%rbp), %eax
	je	.L41
	movl	-68(%rbp), %eax
	cltq
	movl	-176(%rbp,%rax,4), %ecx
	movq	-104(%rbp), %rax
	movl	-64(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	movl	-68(%rbp), %eax
	cltq
	movl	-224(%rbp,%rax,4), %ecx
	movq	-120(%rbp), %rax
	movl	-64(%rbp), %edx
	movslq	%edx, %rdx
	movl	%ecx, (%rax,%rdx,4)
	addl	$1, -64(%rbp)
	jmp	.L33
.L41:
	nop
.L33:
	addl	$1, -68(%rbp)
.L31:
	movl	-68(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jl	.L34
	movl	-60(%rbp), %eax
	cltq
	movl	-176(%rbp,%rax,4), %eax
	movl	%eax, -124(%rbp)
	movl	-60(%rbp), %eax
	cltq
	movl	-224(%rbp,%rax,4), %eax
	movl	%eax, -128(%rbp)
	movl	$-1, counter(%rip)
	movl	-228(%rbp), %r10d
	movl	-84(%rbp), %eax
	movq	-120(%rbp), %rdx
	movl	-128(%rbp), %ecx
	movq	-104(%rbp), %rsi
	movl	-124(%rbp), %edi
	movl	%eax, %r9d
	movq	%rdx, %r8
	movq	%rsi, %rdx
	movl	%edi, %esi
	movl	%r10d, %edi
	call	search_all_ways_recursive
	addl	%eax, -56(%rbp)
	movq	%rbx, %rsp
	addl	$1, -60(%rbp)
.L30:
	movl	-60(%rbp), %eax
	cmpl	-80(%rbp), %eax
	jl	.L35
	movl	$0, -72(%rbp)
	jmp	.L36
.L39:
	movl	-72(%rbp), %eax
	cltq
	movl	saved_hashsums(,%rax,4), %edx
	movl	-72(%rbp), %ecx
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, -76(%rbp)
	jmp	.L37
.L38:
	movl	-76(%rbp), %eax
	movslq	%eax, %rcx
	movl	-72(%rbp), %eax
	movslq	%eax, %rdx
	movq	%rdx, %rax
	salq	$2, %rax
	addq	%rdx, %rax
	addq	%rax, %rax
	addq	%rcx, %rax
	movl	saved(,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -76(%rbp)
.L37:
	cmpl	$9, -76(%rbp)
	jle	.L38
	addl	$1, -72(%rbp)
.L36:
	cmpl	$99, -72(%rbp)
	jle	.L39
	movl	-56(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC7, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
.L40:
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
