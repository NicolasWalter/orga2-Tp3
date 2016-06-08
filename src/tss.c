/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"


tss tss_inicial;
tss tss_idle;

void tss_inicializar() {
	// tarea inicial
	gdt[TAREA_INICIAL].base_0_15 = (unsigned int )&tss_inicial & 0x0000FFFF;
	gdt[TAREA_INICIAL].base_23_16 = ((unsigned int )&tss_inicial & 0x00FF0000) >> 16;
	gdt[TAREA_INICIAL].base_31_24 = ((unsigned int )&tss_inicial & 0xFF000000) >> 24;
	// idle
	gdt[IDLE].base_0_15 = (unsigned int )&tss_idle & 0x0000FFFF;
	gdt[IDLE].base_23_16 = ((unsigned int )&tss_idle & 0x00FF0000) >> 16;
	gdt[IDLE].base_31_24 = ((unsigned int )&tss_idle & 0xFF000000) >> 24;
	
	tss_idle.esp = 0x27000;
	tss_idle.ebp = 0x27000;
	tss_idle.cr3 = 0x27000;
	tss_idle.eip = 	0x00010000;
	tss_idle.esp0 = 0x27000;
	tss_idle.ds = 0x30;
	tss_idle.ss0 = 0x30;
	tss_idle.ss = 0x30;
	tss_idle.fs = 0x40;
	tss_idle.gs = 0x30;
	tss_idle.es = 0x30;
	tss_idle.cs = 0x20;
	tss_idle.eflags = 0x00000202;
	
	int i;
	for (i = 11; i < 100; ++i){
		gdt[i].p = 0;
	}
}

unsigned int gdt_indiceProximoSegmentoLibre(){
	int i;
	for(i=11; i<100; ++i){
		if(gdt[i].p == 0){
			return i;
		}
	}
}


void tss_completar(unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo){//BATATA hace falta todo esto?

	unsigned int slotLibreGdt = gdt_indiceProximoSegmentoLibre();
	unsigned int proxPagLibre= mmu_proxima_pagina_fisica_libre();
	tss* tss_aCompletar = (tss*) proxPagLibre; 
	unsigned int pilaNivel3 = (unsigned int) tss_aCompletar + PAGE_SIZE;
	unsigned int pilaNivel0 = mmu_proxima_pagina_fisica_libre() + PAGE_SIZE;
	unsigned int cr3Nuevo = inicializar_directorio_paginas_tarea(x, y, privilege, readOrWrite, tipo);

	//LA GRAN BATATA, VER COMO RELLENARLLa 
	
	tss_aCompletar->esp = pilaNivel3;
	tss_aCompletar->ebp = pilaNivel3;
	tss_aCompletar->cr3 = cr3Nuevo;
	tss_aCompletar->eip = 0x8000000;
	tss_aCompletar->esp0 = pilaNivel0;
	tss_aCompletar->ss0 = 0x30;//horacio tiene razon batata (selector de segmento, solo offset) 
	tss_aCompletar->ds = 0x38;//datos usuario horacio tiene razon de nuevo 
	tss_aCompletar->ss = 0x38; //datos usuario
	tss_aCompletar->fs = 0x38;//algun descriptor de segmento
	tss_aCompletar->gs = 0x38;//algun descriptor de segmento
	tss_aCompletar->es = 0x38;//algun descriptor de segmento
	tss_aCompletar->cs = 0x28;//codigo usuario
	tss_aCompletar->eflags = 0x202;//0x202


	[slotLibreGdt] = (gdt_entry) { //BATATA ATOMICA, VER CON QUE RELLENAR TODO ESTO
        (unsigned short)    sizeof(tss)-1, //batata       /* limit[0:15]  */
        (unsigned short)    0x0000, //BATATA       /* base[0:15]   */
        (unsigned char)     0x01,   //BATATA       /* base[23:16]  */
        (unsigned char)     0x09,   /* type         */
        (unsigned char)     0x01,   /* s            */
        (unsigned char)     0x00, 	//batata          /* dpl          */
        (unsigned char)     0x01,   /* p            */
        (unsigned char)     0x00,   //batata        /* limit[16:19] */
        (unsigned char)     0x00,   /* avl          */
        (unsigned char)     0x00,   /* l            */
        (unsigned char)     0x01,   /* db           */
        (unsigned char)     0x01,   /* g            */
        (unsigned char)     0x00,   /* base[31:24]  */
    },

    gdt[slotLibreGdt].base_0_15 = (unsigned int)&tss_aCompletar & 0x0000FFFF;
	gdt[slotLibreGdt].base_23_16 = ((unsigned int)&tss_aCompletar & 0x00FF0000) >> 16;
	gdt[slotLibreGdt].base_31_24 = ((unsigned int)&tss_aCompletar) >> 24;
}