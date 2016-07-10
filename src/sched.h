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
#include "game.h"


typedef struct tarea_t {
	unsigned char tipo:2;	 //Si es 0, sana. Si es 1, A. Si es 2, B.
	unsigned int* cr3;
	unsigned char viva:1;	 //0 muerto, 1 vivo.
	unsigned int indice_gdt;
	unsigned int x;
	unsigned int y;
	unsigned int bebe_x;
	unsigned int bebe_y;
	unsigned char dejo_crias; //bool
	unsigned char reloj;
} __attribute__((__packed__)) tarea;

typedef struct player{
	unsigned int id;
	tarea* tareasJugador;
	unsigned int puntaje;
	unsigned int x;
	unsigned int y;
	unsigned int cantTareasDisponibles;
	unsigned int cantInfectados;
} __attribute__((__packed__)) player;

void inicializarTarea(tarea* t, char tipo, unsigned int* cr3, unsigned char viva, unsigned int indice_gdt, unsigned int pX, unsigned int pY);

player p;

typedef struct scheduler{
	tarea arreglo_h[15];
	tarea arreglo_a[5];
	tarea arreglo_b[5];
	tarea* actual;	
	unsigned char indiceA;
	unsigned char indiceB;
	unsigned char indiceH;
	unsigned int cantidadVivas;
	player jugadorA;
	player jugadorB;
} __attribute__((__packed__)) scheduler;

scheduler sched;

unsigned short sched_proximo_indice();

void sched_inicializar();

unsigned short sched_matar_actual();

#endif	/* !__SCHED_H__ */