	.file	"no_avx_no_graph.cpp"
	.intel_syntax noprefix
	.text
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "%d %d\12\0"
LC2:
	.ascii "FPS: %f\12\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB69:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	push	esi
	push	ebx
	and	esp, -16
	sub	esp, 32
	.cfi_offset 6, -12
	.cfi_offset 3, -16
	call	___main
	call	_clock
	mov	esi, eax
	mov	eax, 100
L2:
	sub	eax, 1
	jne	L2
	call	_clock
	mov	ebx, eax
	mov	DWORD PTR [esp+8], eax
	mov	DWORD PTR [esp+4], esi
	mov	DWORD PTR [esp], OFFSET FLAT:LC0
	call	_printf
	mov	DWORD PTR [esp+28], ebx
	fild	DWORD PTR [esp+28]
	fdivr	DWORD PTR LC1
	fstp	QWORD PTR [esp+4]
	mov	DWORD PTR [esp], OFFSET FLAT:LC2
	call	_printf
	mov	eax, 0
	lea	esp, [ebp-8]
	pop	ebx
	.cfi_restore 3
	pop	esi
	.cfi_restore 6
	pop	ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE69:
	.globl	__Z15draw_mondelbrotiif
	.def	__Z15draw_mondelbrotiif;	.scl	2;	.type	32;	.endef
__Z15draw_mondelbrotiif:
LFB70:
	.cfi_startproc
	push	ebx
	.cfi_def_cfa_offset 8
	.cfi_offset 3, -8
	mov	edx, DWORD PTR [esp+8]
	mov	ebx, DWORD PTR [esp+12]
	test	ebx, ebx
	jle	L5
	mov	ecx, 0
	jmp	L9
L7:
	add	ecx, 1
	cmp	ebx, ecx
	je	L5
L9:
	test	edx, edx
	jle	L7
	mov	eax, 0
L8:
	add	eax, 1
	cmp	edx, eax
	jne	L8
	jmp	L7
L5:
	pop	ebx
	.cfi_restore 3
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
LFE70:
	.globl	__Z22mondelbrot_point_colorffii
	.def	__Z22mondelbrot_point_colorffii;	.scl	2;	.type	32;	.endef
__Z22mondelbrot_point_colorffii:
LFB71:
	.cfi_startproc
	fld	DWORD PTR [esp+4]
	fld	DWORD PTR [esp+8]
	fld	st(1)
	fmul	st, st(2)
	fld	st(2)
	fmul	st, st(2)
	fld	st(2)
	fmul	st, st(3)
	fld	st(2)
	fadd	st, st(1)
	fld	DWORD PTR LC4
	fxch	st(1)
	fcomip	st, st(1)
	fstp	st(0)
	ja	L21
	fxch	st(1)
	fadd	st, st(0)
	fadd	st, st(3)
	fxch	st(2)
	fsubrp	st(1), st
	fadd	st, st(3)
	mov	eax, 1
L16:
	fld	st(0)
	fmul	st, st(1)
	fxch	st(1)
	fmul	st, st(2)
	fld	st(2)
	fmulp	st(3), st
	fld	st(1)
	fadd	st, st(3)
	fld	DWORD PTR LC4
	fxch	st(1)
	fcomip	st, st(1)
	fstp	st(0)
	ja	L18
	fadd	st, st(0)
	fadd	st, st(3)
	fxch	st(1)
	fsubrp	st(2), st
	fxch	st(1)
	fadd	st, st(3)
	add	eax, 1
	cmp	eax, 256
	jne	L16
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	mov	eax, 1
	ret
L21:
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	mov	eax, -1
	ret
L18:
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	fstp	st(0)
	mov	eax, -1
	ret
	.cfi_endproc
LFE71:
	.section .rdata,"dr"
	.align 4
LC1:
	.long	1203982336
	.align 4
LC4:
	.long	1120403456
	.ident	"GCC: (i686-win32-dwarf-rev0, Built by MinGW-W64 project) 8.1.0"
	.def	_clock;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
