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
	gdt[IDLE].base_0_15 = (uint )&tss_inicial & 0x0000FFFF;
	gdt[IDLE].base_23_16 = ((uint )&tss_inicial & 0x00FF0000) >> 16;
	gdt[IDLE].base_31_24 = ((uint )&tss_inicial & 0xFF000000) >> 24;
	// idle
	gdt[TAREA_INICIAL].base_0_15 = (uint )&tss_idle & 0x0000FFFF;
	gdt[TAREA_INICIAL].base_23_16 = ((uint )&tss_idle & 0x00FF0000) >> 16;
	gdt[TAREA_INICIAL].base_31_24 = ((uint )&tss_idle & 0xFF000000) >> 24;
	
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



} 
