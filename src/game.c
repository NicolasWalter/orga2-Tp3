/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"


void game_mover_cursor(int jugador, direccion dir) {
	// if(dir==IZQ){
		
	// }
}

void game_lanzar(unsigned int jugador) {
}

void game_soy(unsigned int yoSoy) {
	if(yoSoy==ROJO){
		sched.actual->tipo=1;
	}else if(yoSoy==AZUL){
		sched.actual->tipo=2;
	}else{
		sched.actual->tipo=0;
	}
}

void game_donde(unsigned int* pos) {
	pos[0]=sched.actual->x;
	pos[1]=sched.actual->y;
}


//void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite){
void game_mapear(int x, int y) {
	unsigned int fisica = X_Y_A_MEMORIA(x,y);
	mmu_mapear_pagina( 0x8001000, rcr3(), fisica ,1,1);
}

