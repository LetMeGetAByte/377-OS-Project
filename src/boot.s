.set ALIGN,		1<<0
.set MEMINFO,	1<<1
.set VIDEO,		1<<2
.set FLAGS,		ALIGN | MEMINFO | VIDEO
.set MAGIC,		0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 1024
.long 768
.long 32

.section .bss
.align 16
stack_base_ptr:
.skip 16384
stack_ptr:

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_ptr, %esp
	sub $12, %esp
	push %ebx
	call kernel_main
	cli

1:	hlt
	jmp 1b

.size _start, . - _start