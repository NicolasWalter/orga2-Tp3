/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "colors.h"
#include "defines.h"
#include "sched.h"
/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void print_char(unsigned char c, unsigned int x, unsigned int y, unsigned short attr);

void inicializar_pantalla();

void gris_de_nuevo();

void pintar_tareas();

void pintar_jugadores();

void imprimirTecla(char);

void imprimirNombreGrupo();

void actualizarPantalla();

void pintar_area(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, unsigned short attr);

void pintar_clocks();

void pintar_puntajes();

void pintar_Debug(unsigned int cr4,unsigned int cr3,unsigned int cr2,unsigned int cr0,unsigned int gs, unsigned int fs,unsigned int es, unsigned int ds,unsigned int ebp, unsigned int edi, unsigned int esi, unsigned int edx, unsigned int ecx, unsigned int ebx, unsigned int eax, unsigned int errCode, unsigned int eip, unsigned int cs, unsigned int eflags, unsigned int esp, unsigned int ss);

#endif  /* !__SCREEN_H__ */
