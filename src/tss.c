/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

#define USER_SEG 0x3
tss tss_inicial;
tss tss_idle;

void tss_inicializar() {

	// tarea inicial
	gdt[TAREA_INICIAL].base_0_15 = (unsigned int )&tss_inicial;			// & 0x0000FFFF;
	gdt[TAREA_INICIAL].base_23_16 = (unsigned int )&tss_inicial >> 16;	//& 0x00FF0000) >> 16;
	gdt[TAREA_INICIAL].base_31_24 = (unsigned int )&tss_inicial >> 24;	//& 0xFF000000) >> 24;
	
	// idle
	gdt[IDLE].base_0_15 = (unsigned int )&tss_idle;			// & 0x0000FFFF;
	gdt[IDLE].base_23_16 = (unsigned int )&tss_idle>>16;	// & 0x00FF0000) >> 16;
	gdt[IDLE].base_31_24 = (unsigned int )&tss_idle>>24;	// & 0xFF000000) >> 24;

	tss_idle.esp = 0x27000;
	tss_idle.ebp = 0x27000;
	tss_idle.cr3 = 0x27000;
	tss_idle.eip = 	0x10000;
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
	return 0;
}


unsigned int tss_completar(unsigned int* cr3Tem, unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo){//BATATA hace falta todo esto?

	unsigned int slotLibreGdt = gdt_indiceProximoSegmentoLibre();

	unsigned int proxPagLibre= mmu_proxima_pagina_fisica_libre();
	tss* tss_aCompletar = (tss*) proxPagLibre; 
	unsigned int i = 0;
    unsigned char* p = (unsigned char*) tss_aCompletar;
    while(i < sizeof(tss)){
        p[i] = 0;
        i++;
    }
	unsigned int pilaNivel0 = mmu_proxima_pagina_fisica_libre() + PAGE_SIZE;
	unsigned int cr3Nuevo = inicializar_directorio_paginas_tarea(x, y, privilege, readOrWrite, tipo);
	*(cr3Tem)=cr3Nuevo;

	// //LA GRAN BATATA, VER COMO RELLENARLLa 
	
	tss_aCompletar->esp = 0x8001000;
	tss_aCompletar->ebp = 0x8001000;
	tss_aCompletar->cr3 = cr3Nuevo;
	tss_aCompletar->eip = 0x8000000;
	tss_aCompletar->esp0 = pilaNivel0;
	tss_aCompletar->ss0 = 48;			//horacio tiene razon batata (selector de segmento, solo offset) 
	tss_aCompletar->cs = 40 | USER_SEG;	//codig o usuario

	tss_aCompletar->ss = 56 | USER_SEG;	//datos usuario
	tss_aCompletar->ds = 56 | USER_SEG;	//datos usuario horacio tiene razon de nuevo 
	tss_aCompletar->gs = 56 | USER_SEG;	//algun descriptor de segmento
	tss_aCompletar->fs = 56 | USER_SEG;	//algun descriptor de segmento
	tss_aCompletar->es = 56 | USER_SEG;	//algun descriptor de segmento

	tss_aCompletar->eflags = 0x202;		//0x202


	gdt[slotLibreGdt] = (gdt_entry) { 		//BATATA ATOMICA, VER CON QUE RELLENAR TODO ESTO
        (unsigned short)    sizeof(tss)-1,	/* limit[0:15]  */
		(unsigned int)      0,         		/* base[0:15]   */
		(unsigned int)		0,				/* base[23:16]  */
        (unsigned char)     0x09,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x00,           /* g            */
		(unsigned int)    	0,  			/* base[31:24]  */
    };


    gdt[slotLibreGdt].base_0_15 = (unsigned int)tss_aCompletar;
	gdt[slotLibreGdt].base_23_16 = (unsigned int)tss_aCompletar >> 16;
	gdt[slotLibreGdt].base_31_24 = (unsigned int)tss_aCompletar >> 24;


	return (slotLibreGdt<<3); //BATATA
 
}