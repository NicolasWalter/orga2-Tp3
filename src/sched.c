/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

void inicializarTarea(tarea* t, char tipo, unsigned int* cr3, unsigned char viva, unsigned int indice_gdt, unsigned int posX, unsigned int posY){
	t->tipo = tipo;
	t->cr3 = cr3;
	t->viva = viva;
	t->indice_gdt = indice_gdt;
	t->x=posX;
	t->y=posY;
	t->bebe_x=0;
	t->bebe_y=0;
	t->dejo_crias=0; //bool
	t->tipoInicial=tipo;
	t->clock='|';
}

unsigned short sched_proximo_indice(){
	actualizarPantalla();
	//print_int(sched.arreglo_h[sched.indiceH].indice_gdt,35,16+sched.indiceH,C_FG_BROWN);
	unsigned int queArreglo = 0;
	unsigned int i;
	unsigned char tipoTarea = sched.actual->tipoInicial;
    //print_int(10,20,0,C_FG_GREEN);
    
	if(sched.cantidadVivas > 1){
		while(queArreglo < 3){	
			if(tipoTarea == 0){
    			i = 1;
				while(i < 6 && (sched.arreglo_a[(sched.indiceA + i) % 5].viva == 0)){
					i++;
				}
				if(i == 6){
					tipoTarea = 1;
					queArreglo++;
				} else {
					//UNA A VIVA
					sched.indiceA = (sched.indiceA+i) % 5;

					sched.actual = &sched.arreglo_a[sched.indiceA]; //batata
				
					print_int(sched.arreglo_a[sched.indiceA].indice_gdt,20,0,C_FG_RED);
					print_int(sched.actual->indice_gdt,40,0,C_FG_GREEN);
					print_int(sched.arreglo_h[sched.indiceA].indice_gdt,34,24,C_FG_RED);

					sched.arreglo_a[sched.indiceA].clock = avanzar_clock(sched.arreglo_a[sched.indiceA].clock);
					return sched.arreglo_a[sched.indiceA].indice_gdt;

				}
			} else if (tipoTarea == 1){//veo las B
    			//VEO AZULES

				i=1;
				while(i<6 && (sched.arreglo_b[(sched.indiceB + i)%5].viva == 0)){
					i++;
				}
				if(i == 6){
					tipoTarea = 2;
					queArreglo++;
					    			// print_int(10,20,0,C_FG_BLUE);

				} else {
					sched.indiceB = (sched.indiceB+i) % 5;
					sched.actual = &sched.arreglo_b[sched.indiceB];
					print_int(sched.arreglo_h[sched.indiceB].indice_gdt,34,24,C_FG_BLUE);
					sched.arreglo_b[sched.indiceB].clock = avanzar_clock(sched.arreglo_b[sched.indiceB].clock);
					return sched.arreglo_b[sched.indiceB].indice_gdt;
				}
			} else if (tipoTarea == 2){

				//tipo es 2, veo las sanas
				i=1;
				while(i<16 && (sched.arreglo_h[(sched.indiceH + i)%15].viva == 0)){
					i++;
				}
				if(i == 16){
					//print_int(10,20,0,C_FG_GREEN);
					tipoTarea = 0;
					queArreglo++;
				} else {

					sched.indiceH = (sched.indiceH+i) % 15;
					sched.actual = &sched.arreglo_h[sched.indiceH];
					print_int(sched.arreglo_h[sched.indiceH].indice_gdt,34,24,C_FG_GREEN);
				//	breakpoint();
					sched.arreglo_h[sched.indiceH].clock = avanzar_clock(sched.arreglo_h[sched.indiceH].clock);
					return sched.arreglo_h[sched.indiceH].indice_gdt	;

				}
			}
		}
	}
	return 0;//batata
}

void sched_inicializar(){	
	//tengo que meter las 15 H
	//void tss_completar(unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo)
	unsigned int i;
	for (i = 0; i < 15; ++i){
		tarea sana;
		unsigned int cr3tarea;
		unsigned int ind_gdt = tss_completar(cr3tarea, 10+i, 10+i, 1, 1, 0);
		if(i == 1){
			//print_int(ind_gdt,60,20,C_FG_RED);
		}
		inicializarTarea(&sana, 0, &cr3tarea, 1, ind_gdt, 10+i, 10+i);
		sched.arreglo_h[i] = sana;
		//tss_completar(1+i,1+i,1,1,0x300); //Batata ver que onda r/w
	}	
	for (i = 0; i < 5; ++i){
		tarea tipoA;
		tipoA.tipo=1;
		tipoA.viva=0;
		tipoA.bebe_x=0;
		tipoA.bebe_y=0;
		tipoA.dejo_crias=0;
		sched.arreglo_a[i] = tipoA;
	}

	for (i = 0; i < 5; ++i){
		tarea tipoB;
		tipoB.tipo=2;
		tipoB.viva=0;
		tipoB.bebe_x=0;
		tipoB.bebe_y=0;
		tipoB.dejo_crias=0;
		sched.arreglo_b[i] = tipoB;
	}

	sched.actual = &sched.arreglo_h[0];
	sched.indiceA = 0;
	sched.indiceB = 0;
	sched.indiceH = 0;
	sched.cantidadVivas = 15;

	player jugA;
	jugA.id = 1;
	jugA.tareasJugador = sched.arreglo_a;
	jugA.x=30;
	jugA.y=22;
	jugA.cantTareasDisponibles=20;
	jugA.cantInfectados=0;
	sched.jugadorA = jugA;

	player jugB;
	jugB.id=2;
	jugB.tareasJugador = sched.arreglo_b;
	jugB.x=50;
	jugB.y=22;
	jugB.cantTareasDisponibles=20;
	jugB.cantInfectados=0;
	sched.jugadorB = jugB;
	pintar_tareas();

	pintar_jugadores();

}

unsigned short sched_matar_actual(){
	if(sched.actual->tipo == 1){
		sched.jugadorA.cantInfectados--;
	} else if (sched.actual->tipo == 2){
		sched.jugadorB.cantInfectados--;
	}
	sched.actual->viva=0;
	sched.cantidadVivas--;
	actualizarPantalla();
	return sched_proximo_indice();
}

unsigned char avanzar_clock(unsigned char clock){
	if(clock == '-'){
		return '\\';
	}
	else if(clock == '\\'){
		return '|';
	}
	else if(clock == '|'){
		return '/';
	}
	else{
		return '-';
	}
}