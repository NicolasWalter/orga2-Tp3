/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_H                 15
#define CANT                    5
#define SIZE_W                  80
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 9

#define GDT_IDX_NULL_DESC           0

#define CODIGO_KERNEL_0 4
#define CODIGO_USER_3 5
#define DATOS_KERNEL_0  6
#define DATOS_USER_3 7
#define VIDEO 		8
/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO_SCREEN            0x000B8000 /* direccion fisica del buffer de video */

/*Memory Management Unit */
#define PDE_INDEX(virtual) virtual >> 22
#define PTE_INDEX(virtual) (virtual << 10) >> 22
#define ALIGN(dir) dir >> 12
#define PG_WRITE 0x00000002
#define PG_USER 0x00000004
#define PG_PRESENT 0x00000001
#define INICIO_PAGINAS_LIBRES	0x100000
#define PAGE_SIZE 				0x1000
#define X_Y_A_MEMORIA(x,y) (0x400000+(y*80+x)*0x1000)
#define ROJO 0x841
#define AZUL 0x325
//#define MIN(x,y) ( x < y ? x : y )



#endif  /* !__DEFINES_H__ */