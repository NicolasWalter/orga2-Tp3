; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
extern GDT_DESC
extern IDT_DESC
extern PAGE_DIRECTORY_BASE
extern inicializar_en_gris
extern idt_inicializar
extern mmu_inicializar

%include "imprimir.mac"

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0

    xchg bx, bx
    ; Habilitar A20      
    call habilitar_A20

    ; Cargar la GDT
    LGDT [GDT_DESC] 

    ; Setear el bit PE del registro CR0
    mov eax, CR0
    or eax, 1
    mov cr0, eax 
    xchg bx, bx
    ; Saltar a modo protegido
    jmp 0x20:modo_protegido
    BITS 32

    modo_protegido: 
    mov eax, 695    
   
     


    ; Establecer selectores de segmentos
    xor eax, eax        
    mov ax, 110000b     
    mov ds, ax
    mov es, ax
    mov gs, ax
	mov ss, ax

    mov ax, 1000000b 
    mov fs, ax
    
    ; Establecer la base de la pila
    mov esp, 0x27000
    mov ebp, 0x27000

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0

    ; Inicializar pantalla
    call inicializar_en_gris  ;BATATA PONIENDO COLORES
	    
    ; Inicializar el manejador de memoria //BATATA Y ESTO QUE DIFERENCIA TIENE CON LA OTRA WEA
    xchg bx, bx
    ; Inicializar el directorio de paginas
    call mmu_inicializar
    ; Cargar directorio de paginas
    xchg bx, bx    
    xor eax, eax
    mov eax, 0x27000 ;BATATA ESTO ES PAGE_DIRECTORY_BASE
    ;xor eax, eax
    ;mov eax, 0x3  ; setea pcd y pwd en 0
    ;and cr3, eax
    mov cr3, eax

    xchg bx, bx    

    ; Habilitar paginacion
    mov eax, cr0
    xchg bx, bx   

    or eax, 0b10000000000000000000000000000000    ;BATATA PAGINACION REVIENTA PERO ESTE VALOR DEBERIA FUNCIONAR (prende el bit 31 de cr0 cuando se hace el mov siguiente)
                                                  ;Hace lo que deberia, revisar paginacion batata lo hace explotar
    xchg bx, bx
    mov cr0, eax 
    ; Inicializar tss
    xchg bx, bx   
    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT


    call idt_inicializar
    xchg bx,bx
    ; Cargar IDT
    lidt [IDT_DESC]
    mov cx, 0
 	div cx
    ; Configurar controlador de interrupciones BATATA

    ; Cargar tarea inicial

    ; Habilitar interrupciones BATATA

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
