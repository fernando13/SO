; Linux OS
; file: exit_42.asm
; compile with:
; nasm -f elf exit_42.asm
; ld -s -nostdlib -o exit_42 exit_42.o -m elf_i386
;
; try it using:
; ./exit_42 ; echo $?

BITS 32
GLOBAL _start
SECTION .text
_start:
		mov eax, 1   ; set syscall number 1 (EXIT)
		mov ebx, 42  ; argument of EXIT
		int 0x80	 ; do the syscall


; MAC OS (BSD)
; file: exit_42.asm
; compile with:
; nasm -f macho exit_42.asm
; ld -macosx_version_min 10.7.0 -o exit_42 exit_42.o
;
; try it using:
; ./exit_42 ; echo $?

; BITS 32
; GLOBAL start
; SECTION .text
; start:
; 		mov eax, 1  ; set syscall number 1 (EXIT)
;		push 42	    ; argument of EXIT on stack
;		sub esp, 4  ; return value space
;		int 0x80    ; do the syscall		