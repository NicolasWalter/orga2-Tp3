/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

unsigned int proxima_pagina_libre;

void mmu_inicializar(){
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	return pagina_libre;
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite){
	
	directory_entry* pde = (directory_entry*) cr3;

	if(!pde[PDE_INDEX(virtual)].present){
		unsigned int tableAddress = mmu_proxima_pagina_fisica_libre();
		int i;
		for (i = 0; i < 1024; ++i){
			pde[i].dirBase = 0;
			pde[i].present = 0;
			pde[i].rw = 0;
			pde[i].priv = 0;	
		}
		pde[PDE_INDEX(virtual)].dirBase = tableAddress >> 12;
		pde[PDE_INDEX(virtual)].present = 1;
		pde[PDE_INDEX(virtual)].rw = readOrWrite;
		pde[PDE_INDEX(virtual)].priv = privilege;
	}

	table_entry* pte = (table_entry*) (pde[PDE_INDEX(virtual)].dirBase << 12); //batata

	if(!pte[PTE_INDEX(virtual)].present){
		int j;
		for (j = 0; j < 1024; ++j){
			pte[j].dirBase = 0;
			pte[j].present = 0;
			pte[j].rw = 0;         //BATATA INICIALIZAR CON CERO LOS CEROS CERO CERO
			pte[j].priv = 0;	
		}
		pte[PTE_INDEX(virtual)].dirBase = fisica >> 12;
		pte[PTE_INDEX(virtual)].present = 1;
		pte[PTE_INDEX(virtual)].rw = readOrWrite;
		pte[PTE_INDEX(virtual)].priv = privilege;	
	}
}

void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3){
	directory_entry* pde = (directory_entry*) cr3;

	if(pde[PDE_INDEX(virtual)].present){
		table_entry* pte = (table_entry*) (pde[PDE_INDEX(virtual)].dirBase << 12);
		
		if(pde[PTE_INDEX(virtual)].present){
			pte[PTE_INDEX(virtual)].present = 0;
		}
		pde[PDE_INDEX(virtual)].present = 0;
	}
}

void inicializar_directorio_paginas_tarea(unsigned int virtual, unsigned char privilege, unsigned char readOrWrite) {
	
	unsigned int newDirectoryAddress = mmu_proxima_pagina_fisica_libre();

	directory_entry* pde = (directory_entry*) newDirectoryAddress;

	for (i = 0; i < 1024; ++i){
			pde[i].dirBase = 0;
			pde[i].present = 0;
			pde[i].rw = 0;
			pde[i].priv = 0;	
	}	

	table_entry* pte = (directory_entry*) (pde[PDE_INDEX(virtual)]dirBase)

	pde[PDE_INDEX(virtual)].dirBase = tableAddress >> 12;
	pde[PDE_INDEX(virtual)].present = 1;
	pde[PDE_INDEX(virtual)].rw = readOrWrite;
	pde[PDE_INDEX(virtual)].priv = privilege;	

}

void inicializar_directorio_paginas_kernel() {
	int i;
	unsigned int* pageDirectory = (unsigned int*) 0x27000;
	*(pageDirectory) = 0x28003;
	
	for (i = 1; i < 1024; ++i){
		pageDirectory++;
		*(pageDirectory) = 0;
	}
	
	unsigned int* pageTable = (unsigned int*) 0x28000;
	
	unsigned int page = 0x3;

	for (i = 0; i < 1024; ++i){
		*(pageTable) = page;
		page += 0x1000;	
		pageTable++;
	}
}