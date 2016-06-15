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
}
unsigned short sched_proximo_indice() {
	int queArreglo = 0;
	int i;
	unsigned char tipoTarea = sched.actual->tipo;
	if(sched.cantidadVivas>2){
		while(queArreglo < 3){
			if(tipoTarea == 0){//veo las A
				i = 1;
				while(i<6 && (sched.arreglo_a[(sched.indiceA + i)%5].viva == 0)){
					i++;
				}
				if(i == 6){
					tipoTarea = 1;
					queArreglo++;
				} else {
					sched.indiceA = (sched.indiceA+i) % 5;
					sched.actual = &sched.arreglo_a[sched.indiceA]; //batata
					return sched.arreglo_a[sched.indiceA].indice_gdt;
				}
			} else if (tipoTarea == 1){//veo las B
				i=1;
				while(i<6 && (sched.arreglo_b[(sched.indiceB + i)%5].viva == 0)){
					i++;
				}
				if(i == 6){
					tipoTarea = 2;
					queArreglo++;
				} else {
					sched.indiceB = (sched.indiceB+i) % 5;
					sched.actual = &sched.arreglo_b[sched.indiceB];
					return sched.arreglo_b[sched.indiceB].indice_gdt;
				}
			} else if (tipoTarea == 2){
				//tipo es 2, veo las sanas
				i=1;
				while(i<16 && !(sched.arreglo_h[(sched.indiceH + i)%15].viva == 0)){
					i++;
				}
				if(i == 16){
					tipoTarea = 0;
					queArreglo++;
				} else {
					sched.indiceH = (sched.indiceH+i) % 15;
					sched.actual = &sched.arreglo_h[sched.indiceH];
					return sched.arreglo_h[sched.indiceH].indice_gdt;
				}
			}
		}
	}
	return 0;
}

void sched_inicializar(){
	//tengo que meter las 15 H
	//void tss_completar(unsigned int x, unsigned int y, unsigned char privilege, unsigned char readOrWrite, unsigned int tipo)
	unsigned int i;
	for (i = 0; i < 15; ++i){
		tarea sana;
		unsigned int cr3tarea;
		unsigned int ind_gdt = tss_completar(cr3tarea, 10+i, 10+i, 1, 1, 0);
		inicializarTarea(&sana, 0, &cr3tarea, 1, ind_gdt,10+i, 10+i);
		sched.arreglo_h[i] = sana;
		//tss_completar(1+i,1+i,1,1,0x300); //Batata ver que onda r/w
	}	

	for (i = 0; i < 5; ++i){
		tarea tipoA;
		tipoA.tipo=1;
		tipoA.viva=0;
		sched.arreglo_a[i] = tipoA;
	}

	for (i = 0; i < 5; ++i){
		tarea tipoB;
		tipoB.tipo=2;
		tipoB.viva=0;
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
	jugA.puntaje = 0;
	jugA.x=1;
	jugA.y=0;
	jugA.cantTareasDisponibles=20;
	jugA.cantInfectados=0;
	sched.jugadorA = &jugA;

	player jugB;
	jugB.id=2;
	jugB.tareasJugador = sched.arreglo_b;
	jugB.puntaje = 0;
	jugB.x=44;
	jugB.y=79;
	jugB.cantTareasDisponibles=20;
	jugB.cantInfectados=0;
	sched.jugadorB = &jugB;

	pintar_jugadores();

}

unsigned short sched_matar_actual(){
	sched.actual->viva=0;
	sched.cantidadVivas--;
	return sched_proximo_indice();
}