	.file	"pi_monte_carlo_opencl.c"
	.text
	.section	.rodata
.LC0:
	.string	"r"
.LC1:
	.string	"kernel_boost.cl"
.LC2:
	.string	"Failed to load kernel.\n"
.LC3:
	.string	"boost"
.LC6:
	.string	"PI = %Lf\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB509:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$208, %rsp
	movl	$0, %edi
	call	time
	movl	%eax, %edi
	call	srand
	movq	$0, -16(%rbp)
	movl	$80000000, %edi
	call	malloc
	movq	%rax, -24(%rbp)
	movl	$80000000, %edi
	call	malloc
	movq	%rax, -32(%rbp)
	movl	$80000000, %edi
	call	malloc
	movq	%rax, -40(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	-4(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-24(%rbp), %rax
	addq	%rdx, %rax
	movl	$10000, (%rax)
	call	rand
	movl	-4(%rbp), %edx
	leaq	0(,%rdx,4), %rcx
	movq	-32(%rbp), %rdx
	addq	%rcx, %rdx
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
.L2:
	cmpl	$19999999, -4(%rbp)
	jbe	.L3
	movl	$.LC0, %esi
	movl	$.LC1, %edi
	call	fopen
	movq	%rax, -48(%rbp)
	cmpq	$0, -48(%rbp)
	jne	.L4
	movq	stderr(%rip), %rax
	movq	%rax, %rcx
	movl	$23, %edx
	movl	$1, %esi
	movl	$.LC2, %edi
	call	fwrite
	movl	$1, %edi
	call	exit
.L4:
	movl	$1048576, %edi
	call	malloc
	movq	%rax, -120(%rbp)
	movq	-120(%rbp), %rax
	movq	-48(%rbp), %rdx
	movq	%rdx, %rcx
	movl	$1048576, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	fread
	movq	%rax, -128(%rbp)
	movq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	fclose
	movq	$0, -136(%rbp)
	movq	$0, -144(%rbp)
	leaq	-152(%rbp), %rdx
	leaq	-136(%rbp), %rax
	movq	%rax, %rsi
	movl	$1, %edi
	call	clGetPlatformIDs
	movl	%eax, -156(%rbp)
	movq	-136(%rbp), %rax
	leaq	-148(%rbp), %rcx
	leaq	-144(%rbp), %rdx
	movq	%rcx, %r8
	movq	%rdx, %rcx
	movl	$1, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	clGetDeviceIDs
	movl	%eax, -156(%rbp)
	leaq	-156(%rbp), %rdx
	leaq	-144(%rbp), %rax
	movq	%rdx, %r9
	movl	$0, %r8d
	movl	$0, %ecx
	movq	%rax, %rdx
	movl	$1, %esi
	movl	$0, %edi
	call	clCreateContext
	movq	%rax, -56(%rbp)
	movq	-144(%rbp), %rsi
	leaq	-156(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %rcx
	movl	$0, %edx
	movq	%rax, %rdi
	call	clCreateCommandQueue
	movq	%rax, -64(%rbp)
	leaq	-156(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$80000000, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	clCreateBuffer
	movq	%rax, -168(%rbp)
	leaq	-156(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$80000000, %edx
	movl	$4, %esi
	movq	%rax, %rdi
	call	clCreateBuffer
	movq	%rax, -176(%rbp)
	leaq	-156(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$80000000, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	clCreateBuffer
	movq	%rax, -184(%rbp)
	movq	-168(%rbp), %rsi
	movq	-24(%rbp), %rdx
	movq	-64(%rbp), %rax
	subq	$8, %rsp
	pushq	$0
	pushq	$0
	pushq	$0
	movq	%rdx, %r9
	movl	$80000000, %r8d
	movl	$0, %ecx
	movl	$1, %edx
	movq	%rax, %rdi
	call	clEnqueueWriteBuffer
	addq	$32, %rsp
	movl	%eax, -156(%rbp)
	movq	-176(%rbp), %rsi
	movq	-32(%rbp), %rdx
	movq	-64(%rbp), %rax
	subq	$8, %rsp
	pushq	$0
	pushq	$0
	pushq	$0
	movq	%rdx, %r9
	movl	$80000000, %r8d
	movl	$0, %ecx
	movl	$1, %edx
	movq	%rax, %rdi
	call	clEnqueueWriteBuffer
	addq	$32, %rsp
	movl	%eax, -156(%rbp)
	leaq	-156(%rbp), %rsi
	leaq	-128(%rbp), %rcx
	leaq	-120(%rbp), %rdx
	movq	-56(%rbp), %rax
	movq	%rsi, %r8
	movl	$1, %esi
	movq	%rax, %rdi
	call	clCreateProgramWithSource
	movq	%rax, -72(%rbp)
	leaq	-144(%rbp), %rdx
	movq	-72(%rbp), %rax
	movl	$0, %r9d
	movl	$0, %r8d
	movl	$0, %ecx
	movl	$1, %esi
	movq	%rax, %rdi
	call	clBuildProgram
	movl	%eax, -156(%rbp)
	leaq	-156(%rbp), %rdx
	movq	-72(%rbp), %rax
	movl	$.LC3, %esi
	movq	%rax, %rdi
	call	clCreateKernel
	movq	%rax, -80(%rbp)
	leaq	-168(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$0, %esi
	movq	%rax, %rdi
	call	clSetKernelArg
	movl	%eax, -156(%rbp)
	leaq	-176(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$1, %esi
	movq	%rax, %rdi
	call	clSetKernelArg
	movl	%eax, -156(%rbp)
	leaq	-184(%rbp), %rdx
	movq	-80(%rbp), %rax
	movq	%rdx, %rcx
	movl	$8, %edx
	movl	$2, %esi
	movq	%rax, %rdi
	call	clSetKernelArg
	movl	%eax, -156(%rbp)
	movq	$20000000, -192(%rbp)
	movq	$64, -200(%rbp)
	leaq	-200(%rbp), %rcx
	leaq	-192(%rbp), %rdx
	movq	-80(%rbp), %rsi
	movq	-64(%rbp), %rax
	subq	$8, %rsp
	pushq	$0
	pushq	$0
	pushq	$0
	movq	%rcx, %r9
	movq	%rdx, %r8
	movl	$0, %ecx
	movl	$1, %edx
	movq	%rax, %rdi
	call	clEnqueueNDRangeKernel
	addq	$32, %rsp
	movl	%eax, -156(%rbp)
	movq	-184(%rbp), %rsi
	movq	-40(%rbp), %rdx
	movq	-64(%rbp), %rax
	subq	$8, %rsp
	pushq	$0
	pushq	$0
	pushq	$0
	movq	%rdx, %r9
	movl	$80000000, %r8d
	movl	$0, %ecx
	movl	$1, %edx
	movq	%rax, %rdi
	call	clEnqueueReadBuffer
	addq	$32, %rsp
	movl	%eax, -156(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L5
.L6:
	movl	-4(%rbp), %eax
	leaq	0(,%rax,4), %rdx
	movq	-40(%rbp), %rax
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, %eax
	addq	%rax, -16(%rbp)
	addl	$1, -4(%rbp)
.L5:
	cmpl	$19999999, -4(%rbp)
	jbe	.L6
	movabsq	$200000000000, %rax
	movq	%rax, -88(%rbp)
	fildq	-16(%rbp)
	cmpq	$0, -16(%rbp)
	jns	.L7
	fldt	.LC4(%rip)
	faddp	%st, %st(1)
.L7:
	fldt	.LC5(%rip)
	fmulp	%st, %st(1)
	fildq	-88(%rbp)
	cmpq	$0, -88(%rbp)
	jns	.L8
	fldt	.LC4(%rip)
	faddp	%st, %st(1)
.L8:
	fdivrp	%st, %st(1)
	fstpt	-112(%rbp)
	pushq	-104(%rbp)
	pushq	-112(%rbp)
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	addq	$16, %rsp
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	clFlush
	movl	%eax, -156(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	clFinish
	movl	%eax, -156(%rbp)
	movq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseKernel
	movl	%eax, -156(%rbp)
	movq	-72(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseProgram
	movl	%eax, -156(%rbp)
	movq	-168(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseMemObject
	movl	%eax, -156(%rbp)
	movq	-184(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseMemObject
	movl	%eax, -156(%rbp)
	movq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseCommandQueue
	movl	%eax, -156(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rdi
	call	clReleaseContext
	movl	%eax, -156(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE509:
	.size	main, .-main
	.section	.rodata
	.align 16
.LC4:
	.long	0
	.long	-2147483648
	.long	16447
	.long	0
	.align 16
.LC5:
	.long	0
	.long	-2147483648
	.long	16385
	.long	0
	.ident	"GCC: (GNU) 12.1.1 20220507 (Red Hat 12.1.1-1)"
	.section	.note.GNU-stack,"",@progbits
