/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "mmu.h"

typedef enum direccion_e { IZQ = 0xAAA, DER = 0x441, ARB = 0xA33, ABA = 0x883 } direccion;

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(short* pos);

void game_mover_cursor(int jugador, direccion dir);

void game_mapear(int x, int y);

void modoDebug(unsigned int cr4, unsigned int cr3, unsigned int cr2, unsigned int cr0,unsigned int gs, unsigned int fs,unsigned int es, unsigned int ds,unsigned int ebp, unsigned int edi, unsigned int esi, unsigned int edx, unsigned int ecx, unsigned int ebx, unsigned int eax, unsigned int errCode, unsigned int eip, unsigned int cs, unsigned int eflags, unsigned int esp, unsigned int ss);

#endif  /* !__GAME_H__ */
