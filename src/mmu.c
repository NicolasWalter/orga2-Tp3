/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

void mmu_inicializar() {
	int i;
	unsigned int* pageDirectory = (unsigned int*) 0x27000;
	*(pageDirectory) = 0x28003;  // 101000000000000000_000_000000_011
	
	for (i = 1; i < 1024; ++i){
		pageDirectory++;
		*(pageDirectory) = 0;
	}
	
	unsigned int* pageTable = (unsigned int*) 0x28000;
	
	for (i = 0; i < 1048576; ++i){
		pageTable++;
		*(pageTable) = 0x3; //batata (estan presentes y en r/w)
	}

}