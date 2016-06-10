/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

void mmu_inicializar();
void inicializar_directorio_paginas();
unsigned int mmu_proxima_pagina_fisica_libre();
void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite);
void mmu_unmapear_pagina(unsigned int virtual, unsigned int cr3);
unsigned int inicializar_directorio_paginas_tarea(unsigned int x, unsigned int y, unsigned char privilege /*batata*/, unsigned char readOrWrite /*batata*/, unsigned int tipo );
void inicializar_directorio_paginas_kernel();


typedef struct str_directory_entry {
    unsigned char   present:1;
    unsigned char   rw:1;
    unsigned char   priv:1;
    unsigned int    ceros:9;
    unsigned int  dirBase:20;
} __attribute__((__packed__)) directory_entry;

typedef struct str_table_entry {
    unsigned char   present:1;
    unsigned char   rw:1;
    unsigned char   priv:1;
    unsigned int    ceros:9;
    unsigned int  dirBase:20;
} __attribute__((__packed__)) table_entry;



#endif	/* !__MMU_H__ */




