/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
#include "i386.h"

unsigned int proxima_pagina_libre;

void mmu_inicializar(){
	proxima_pagina_libre = INICIO_PAGINAS_LIBRES;
}

unsigned int mmu_proxima_pagina_fisica_libre() {	
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += PAGE_SIZE;
	unsigned int* aux = (unsigned int*) pagina_libre;
	int i;
	for(i=0; i<1024; i++){  //NO SABEMOS SI VA ESTE FOR
		aux[i]=0;
		aux++;
	}
	return pagina_libre;
}

void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite){
	
	directory_entry* pde = (directory_entry*) cr3;
	table_entry* pte;

	if(!pde[PDE_INDEX(virtual)].present){
		unsigned int tableAddress = mmu_proxima_pagina_fisica_libre(); //Creo
		pde[PDE_INDEX(virtual)].dirBase = tableAddress >> 12;
		pde[PDE_INDEX(virtual)].present = 1;
		pde[PDE_INDEX(virtual)].rw = readOrWrite;
		pde[PDE_INDEX(virtual)].priv = privilege;
		pde[PDE_INDEX(virtual)].ceros=0;

		pte = (table_entry*) (pde[PDE_INDEX(virtual)].dirBase << 12); //si no esta pde tampoco esta pte
		pte[PTE_INDEX(virtual)].dirBase = fisica >> 12;
		pte[PTE_INDEX(virtual)].present = 1;
		pte[PTE_INDEX(virtual)].rw = readOrWrite;
		pte[PTE_INDEX(virtual)].priv = privilege;
		pte[PTE_INDEX(virtual)].ceros = 0;



	}


	pte = (table_entry*) (pde[PDE_INDEX(virtual)].dirBase << 12); //batata
	//breakpoint();
	if(!pte[PTE_INDEX(virtual)].present){
	//	breakpoint();
		// int j;
		// for (j = 0; j < 1024; ++j){
		// 	pte[j].dirBase = 0;
		// 	pte[j].present = 0;	
		// 	pte[j].rw = 0;         //BATATA INICIALIZAR CON CERO LOS CEROS CERO CERO
		// 	pte[j].priv = 0;	
		// }
		pte[PTE_INDEX(virtual)].present = 1;
		pte[PTE_INDEX(virtual)].rw = readOrWrite;
		pte[PTE_INDEX(virtual)].priv = privilege;
		pte[PTE_INDEX(virtual)].ceros = 0;
	
	}
	pte[PTE_INDEX(virtual)].dirBase = fisica >> 12;

	tlbflush();
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

unsigned int inicializar_directorio_paginas_tarea(unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo){
	
	unsigned int cr3 = mmu_proxima_pagina_fisica_libre();
	directory_entry* pde = (directory_entry*) cr3;
	table_entry* pte= (table_entry*) mmu_proxima_pagina_fisica_libre();

	pde[0].dirBase = ALIGN((unsigned int) pte);
	pde[0].present = 1;
	pde[0].rw = readOrWrite;
	pde[0].priv = privilege;
	pde[0].ceros=0;

	unsigned int fisica = X_Y_A_MEMORIA(x,y);
	pte[0].dirBase = ALIGN(fisica);
	pte[0].present = 1;
	pte[0].rw = readOrWrite;
	pte[0].priv = privilege;
	pte[0].ceros=0;

	//breakpoint();

	int i = 0;
	while(i<1024){
		mmu_mapear_pagina(i*PAGE_SIZE,cr3,i*PAGE_SIZE,0,readOrWrite);
		i++;
	}
	mmu_mapear_pagina(0x8000000, cr3, fisica, privilege, readOrWrite);

	mmu_mapear_pagina(fisica, rcr3(), fisica, 0, readOrWrite);
	//void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite){
	//breakpoint();
	unsigned int* codigoTarea;
	if(tipo==1){
		codigoTarea= (unsigned int*) 0x11000;
	}else if(tipo==2){
		codigoTarea=(unsigned int*) 0x12000;
	} else{
		codigoTarea=(unsigned int*) 0x13000;
	}

	unsigned int* punteroAFisica = (unsigned int*) fisica;
	int k;
		//breakpoint();

	for(k=0; k<1024; k++){ //BATATA MODIFICAR EL LIMITE DEL FOR
		punteroAFisica[k]=codigoTarea[k];
	}
	//breakpoint();
	mmu_unmapear_pagina(fisica,rcr3());
	//breakpoint();
	tlbflush(); //batata

return cr3;

}



void inicializar_directorio_paginas_kernel() {    //BATATA DEVOLVER CR3?
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