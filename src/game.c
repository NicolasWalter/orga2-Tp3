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
			if(sched.jugadorA.x!=0){
				sched.jugadorA.x = (sched.jugadorA.x -1);
			}
		}else{
			if(sched.jugadorB.x != 0){
				sched.jugadorB.x= (sched.jugadorB.x -1);
			}
		}
	}else if(dir==DER){
		if(jugador==1){
			if(sched.jugadorA.x!=79){
				sched.jugadorA.x = (sched.jugadorA.x +1);
			}
		}else{
			if(sched.jugadorB.x != 79){
				sched.jugadorB.x= (sched.jugadorB.x +1);
			}
		}
	}else if(dir==ARB){
		if(jugador==1){
			if(sched.jugadorA.y!=1){
				sched.jugadorA.y = (sched.jugadorA.y -1);
			}
		}else{
			if(sched.jugadorB.y != 1){
				sched.jugadorB.y= (sched.jugadorB.y -1);
			}
		}
	}else{
		if(jugador==1){
			if(sched.jugadorA.y!=44){
				sched.jugadorA.y = (sched.jugadorA.y +1);
			}
		}else{
			if(sched.jugadorB.y != 44){
				sched.jugadorB.y= (sched.jugadorB.y +1);
			}
		}
	}
}

void game_lanzar(unsigned int jugador) { 
	unsigned int cr3tarea=0; // lo iguale a 0 porque sino no me compilaba por no estar inicializado.
	if(jugador==1){
		if(sched.jugadorA.cantInfectados!=5 && sched.jugadorA.cantTareasDisponibles >0){
			tarea tipoA;
			unsigned int ind_gdt = tss_completar(cr3tarea,sched.jugadorA.x,sched.jugadorA.y,1,1,1);
			inicializarTarea(&tipoA,1,&cr3tarea,1,ind_gdt,sched.jugadorA.x,sched.jugadorA.y);
			sched.arreglo_a[sched.jugadorA.cantInfectados] = tipoA;
			sched.jugadorA.cantInfectados++;
			sched.jugadorA.cantTareasDisponibles--;
		}
	}else{
		if(sched.jugadorB.cantInfectados!=5 && sched.jugadorB.cantTareasDisponibles >0){
			tarea tipoB;
			unsigned int ind_gdt = tss_completar(cr3tarea,sched.jugadorB.x,sched.jugadorB.y,1,1,2);
			inicializarTarea(&tipoB,2,&cr3tarea,1,ind_gdt,sched.jugadorB.x,sched.jugadorB.y);
			sched.arreglo_b[sched.jugadorB.cantInfectados] = tipoB;
			sched.jugadorB.cantInfectados++;
			sched.jugadorB.cantTareasDisponibles--;

		}
	}
	sched.cantidadVivas++;
	//breakpoint();
}

void game_soy(unsigned int yoSoy) {
	if(yoSoy==0x841){
		sched.actual->tipo=1;
	}else if(yoSoy==AZUL){
		sched.actual->tipo=2;
	}else{
		sched.actual->tipo=0;
	}
}

void game_donde(short* pos) {
	//breakpoint();
	pos[0]=sched.actual->x;
	pos[1]=sched.actual->y;
}


//void mmu_mapear_pagina(unsigned int virtual, unsigned int cr3, unsigned int fisica, unsigned char privilege, unsigned char readOrWrite){
void game_mapear(int x, int y) {
	//breakpoint();
	unsigned int a = (unsigned int)(rcr3());
	a++;
	if(x >= SIZE_W || y >= SIZE_H || y==0){
		return;
	}
	unsigned int fisica = X_Y_A_MEMORIA(x,y);
	mmu_mapear_pagina( 0x8001000, rcr3(), fisica ,1,1);	//(unsigned int)(sched.actual->cr3)
	sched.actual->dejo_crias=1;
	sched.actual->bebe_x=x;
	sched.actual->bebe_y=y;
}

