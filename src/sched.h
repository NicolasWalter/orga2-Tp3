/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"
#include "gdt.h"

typedef struct tarea
{
	unsigned char tipo; //Si es 0, sana. Si es 1, A. Si es 2, B.
	unsigned int x;
	unsigned int y;
	unsigned int* cr3;
	unsigned char vivo:1; //0 muerto, 1 vivo.
	unsigned int indice_gdt;


} __attribute__((__packed__)) tarea;


typedef struct scheduler
{
	tarea arreglo_h[15];
	tarea arreglo_a[5];
	tarea arreglo_b[5];
	tarea* actual;
	
} __attribute__((__packed__)) scheduler;


unsigned short sched_proximo_indice();

void sched_inicializar();

#endif	/* !__SCHED_H__ */

