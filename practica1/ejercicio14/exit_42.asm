BITS 32
GLOBAL _start
SECTION .text
_start:
		mov eax, 1   ; set syscall number 1 (EXIT)
		mov ebx, 42  ; argument of EXIT
		int 0x80	 ; do the syscall

