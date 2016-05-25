; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1
_isr%1:
    mov eax, %1
    imprimir_texto_mp msgInt%1, msgIntLen%1, 0x07, 3, 0
    jmp $
%endmacro

msgInt0: db 'Divide error'
msgIntLen0 equ $ - msgInt0

msgInt1: db 'RESERVED'
msgIntLen1 equ $ - msgInt1

msgInt2: db 'Nonmaskable external interrupt'
msgIntLen2 equ $ - msgInt2

msgInt3: db 'Breakpoint'
msgIntLen3 equ $ - msgInt3

msgInt4: db 'Overflow'
msgIntLen4 equ $ - msgInt4

msgInt5: db 'BOUND Range Exceeded'
msgIntLen5 equ $ - msgInt5

msgInt6: db 'Invalid Opcode'
msgIntLen6 equ $ - msgInt6

msgInt7: db 'Device Not Available (No Math Coprocessor)'
msgIntLen7 equ $ - msgInt7

msgInt8: db 'Double Fault'
msgIntLen8 equ $ - msgInt8

msgInt9: db 'Coprocessor Segment Overrun'
msgIntLen9 equ $ - msgInt9

msgInt10: db 'Invalid TSS'
msgIntLen10 equ $ - msgInt10

msgInt11: db 'Segment Not Present'
msgIntLen11 equ $ - msgInt11

msgInt12: db 'Stack-Segment Fault'
msgIntLen12 equ $ - msgInt12

msgInt13: db 'General Protection'
msgIntLen13 equ $ - msgInt13

msgInt14: db 'Page Fault'
msgIntLen14 equ $ - msgInt14

msgInt16: db 'x87 FPU Floating-Point Error'
msgIntLen16 equ $ - msgInt16

msgInt17: db 'Alignment Check'
msgIntLen17 equ $ - msgInt17

msgInt18: db 'Machine Check'
msgIntLen18 equ $ - msgInt18

msgInt19: db 'SIMD Floating-Point Exception'
msgIntLen19 equ $ - msgInt19

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define DONDE  0x124
%define SOY    0xA6A
%define MAPEAR 0xFF3

%define VIRUS_ROJO 0x841
%define VIRUS_AZUL 0x325


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
        
