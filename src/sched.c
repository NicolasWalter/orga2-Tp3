/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned short sched_proximo_indice() {
  return 0;
}

void sched_inicializar(){
	//tengo que meter las 15 H
	//void tss_completar(unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo)
	unsigned int i;
	for (i = 0; i < 15; ++i)
	{
		//tss_completar(30+i,30+i,1,1,0x300); //Batata ver que onda r/w
	}	
}

