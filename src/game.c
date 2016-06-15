/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"


void game_mover_cursor(int jugador, direccion dir) {
	// int jugAposX=sched.jugadorA->x;
	// int jugAposY=sched.jugadorA->y;
	// int jugBposX=sched.jugadorB->x;
	// int jugBposY=sched.jugadorB->y;

	if(dir==IZQ){
		if(jugador==1){
			sched.jugadorA.x = (sched.jugadorA.x -1) % 50;
		}else{
			sched.jugadorB.x= (sched.jugadorB.x -1)% 50;
		}
	}else if(dir==DER){
		if(jugador==1){
			sched.jugadorA.x = (sched.jugadorA.x +1)% 50;
		}else{
			sched.jugadorB.x= (sched.jugadorB.x +1)% 50;
		}
	}else if(dir==ARB){
		if(jugador==1){
			sched.jugadorA.y = (sched.jugadorA.y -1);
		}else{
			sched.jugadorB.y= (sched.jugadorB.y -1);
		}
	}else{
		if(jugador==1){
			sched.jugadorA.y = (sched.jugadorA.y +1);
		}else{
			sched.jugadorB.y= (sched.jugadorB.y +1);
		}
	}
	gris_de_nuevo();
	pintar_jugadores();

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

