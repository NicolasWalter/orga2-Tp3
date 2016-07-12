/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void print_char(unsigned char c, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
        p[y][x].c = (unsigned char) c;
        p[y][x].a = (unsigned char) attr;
}

void gris_de_nuevo(){
    pintar_area(0, 1, 80, 44, C_FG_WHITE + C_BG_LIGHT_GREY);
}


void pintar_tareas(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i=0;
    while(i<15){
        print_int(sched.arreglo_h[i].viva,5+(i*2),40,C_FG_WHITE + C_BG_GREEN);

        if(sched.arreglo_h[i].viva){
            if(sched.arreglo_h[i].tipo == 0){
                p[sched.arreglo_h[i].y][sched.arreglo_h[i].x].c = 0xff;
                p[sched.arreglo_h[i].y][sched.arreglo_h[i].x].a = C_FG_GREEN + C_BG_GREEN;
            }
            if(sched.arreglo_h[i].tipo == 1){
                print("A", sched.arreglo_h[i].x, sched.arreglo_h[i].x, C_FG_WHITE + C_BG_RED);
                if(sched.arreglo_h[i].dejo_crias){
                    print("A", sched.arreglo_h[i].bebe_x, sched.arreglo_h[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }
            } 
            if(sched.arreglo_h[i].tipo == 2){
                print("B", sched.arreglo_h[i].x, sched.arreglo_h[i].x, C_FG_WHITE + C_BG_BLUE);
                if(sched.arreglo_h[i].dejo_crias){
                    print("B", sched.arreglo_h[i].bebe_x, sched.arreglo_h[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }
            }
        }
        i++;
    }
    i=0;
    while(i<5){        
        print_int(sched.arreglo_a[i].viva,33+(i*2),40,C_FG_WHITE + C_BG_RED);

        if(sched.arreglo_a[i].viva){
            p[sched.arreglo_a[i].y][sched.arreglo_a[i].x].c = 0xff;
            p[sched.arreglo_a[i].y][sched.arreglo_a[i].x].a = C_FG_RED + C_BG_RED;
            if(sched.arreglo_a[i].dejo_crias==1){
                if(sched.arreglo_a[i].tipo==1){
                    print("A", sched.arreglo_a[i].bebe_x, sched.arreglo_a[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }else{
                    print("B", sched.arreglo_a[i].bebe_x, sched.arreglo_a[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }
            }
        }
        i++;
    }
     i=0;
     while(i<5){
        print_int(sched.arreglo_b[i].viva,43+(i*2),40,C_FG_WHITE + C_BG_BLUE);

        if(sched.arreglo_b[i].viva){
            p[sched.arreglo_b[i].y][sched.arreglo_b[i].x].c = 0xff;
            p[sched.arreglo_b[i].y][sched.arreglo_b[i].x].a = C_FG_BLUE + C_BG_BLUE;
            if(sched.arreglo_b[i].dejo_crias==1){
                if(sched.arreglo_b[i].tipo==1){
                    print("A", sched.arreglo_b[i].bebe_x, sched.arreglo_b[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }else{
                    print("B", sched.arreglo_b[i].bebe_x, sched.arreglo_b[i].bebe_y, C_FG_WHITE + C_BG_LIGHT_GREY);
                }

            }
        }
        i++;
    }   
}

void pintar_jugadores(){
    //print_int(sched.jugadorA->x,20,0,C_FG_WHITE);
    //print_int(sched.jugadorA->y,15,0,C_FG_WHITE);
    // print_int(9,sched.jugadorA.x,sched.jugadorA.y,C_FG_WHITE);
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    p[sched.jugadorA.y][sched.jugadorA.x].c = 0X11;
    p[sched.jugadorA.y][sched.jugadorA.x].a = C_FG_WHITE + C_BG_RED;
    p[sched.jugadorB.y][sched.jugadorB.x].c = 0X12;
    p[sched.jugadorB.y][sched.jugadorB.x].a = C_FG_WHITE + C_BG_BLUE;
}

void imprimirTecla(char input){
    if(input==0x11){
        print("w",80,1,3);
    }else if(input==0x1e){
        print("a",80,1,3);
    }else if(input==0x1f){
        print("s",80,1,3);
    }else if(input==0x20){
        print("d",80,1,3);
    }else if(input==0x17){
        print("i",80,1,3);
    }else if(input==0x24){
        print("j",80,1,3);
    }else if(input==0x25){
        print("k",80,1,3);
    }else if(input==0x26){
        print("l",80,1,3);
    }else if(input==0x2a){
        print("LShift",80,1,3);
    }else if(input==0x36){
        print("RShift",80,1,3);
    }
}

void imprimirMovimiento(char input){
    if(input==0x11){
        game_mover_cursor(1,ARB);
    }else if(input==0x1e){
        game_mover_cursor(1,IZQ);

    }else if(input==0x1f){
        game_mover_cursor(1,ABA);

    }else if(input==0x20){
        game_mover_cursor(1,DER);
    }else if(input==0x17){

        game_mover_cursor(2,ARB);
    }else if(input==0x24){
        game_mover_cursor(2,IZQ);
    }else if(input==0x25){
        game_mover_cursor(2,ABA);
    }else if(input==0x26){
        game_mover_cursor(2,DER);
    }
}

void pintar_area(unsigned int x, unsigned int y, unsigned int ancho, unsigned int alto, unsigned short attr){
    unsigned int fila;
    unsigned int tope_y;  
    unsigned int tope_x = x + ancho;

    for(tope_y = y + alto; y < tope_y; y++){
        fila = x;
        for (fila = x; fila < tope_x; fila++){
            print(" ", fila, y, attr);
        }
    }
}

void inicializar_pantalla(){
    pintar_area(0, 0, 80, 1, C_FG_WHITE + C_BG_BLACK);
    pintar_area(0, 1, 80, 44, C_FG_WHITE + C_BG_LIGHT_GREY);
    pintar_area(0, 45, 80, 5, C_FG_WHITE + C_BG_BLACK);
    pintar_area(52, 45, 6, 5, C_FG_WHITE + C_BG_RED);
    pintar_area(58, 45, 6, 5, C_FG_WHITE + C_BG_BLUE);
    
    print("Vidas     Puntos     Vidas", 45, 46, C_FG_WHITE + C_BG_BLACK);
    //print("Vidas", 66, 46, C_FG_WHITE + C_BG_BLACK);
    print("A->             B->", 5, 46, C_FG_WHITE + C_BG_BLACK);
}

void pintar_clocks(){
    int i;
    for(i = 0; i < 15; i++){
        if(sched.arreglo_h[i].viva){
            print_char(sched.arreglo_h[i].clock, (2*i)+5, 48, C_FG_WHITE + C_BG_BLACK );
        } else {
            print_char(' ', (2*i)+5, 48, C_FG_WHITE + C_BG_BLACK );
        }
    }
    for(i = 0; i < 5; i++){
        if(sched.arreglo_a[i].viva){        
            print_char(sched.arreglo_a[i].clock, (2*i)+9, 46, C_FG_WHITE + C_BG_BLACK );   
        } else {
            print_char(' ', (2*i)+9, 46, C_FG_WHITE + C_BG_BLACK );
        }
    }
    for(i = 0; i < 5; i++){
        if(sched.arreglo_b[i].viva){
            print_char(sched.arreglo_b[i].clock, (2*i)+25, 46, C_FG_WHITE + C_BG_BLACK );    
        } else {
            print_char(' ', (2*i)+25, 46, C_FG_WHITE + C_BG_BLACK );
        }
    }
}

void pintar_puntajes(){
    int cantA = 0;   
    int cantB = 0;
    int i;
    for(i = 0; i < 15; i++){
        if(sched.arreglo_h[i].viva == 1){
            if(sched.arreglo_h[i].tipo == 1){
                cantA++;
            } else if(sched.arreglo_h[i].tipo == 2){
                cantB++;
            }
        }
    }
    
    for(i = 0; i < 5; i++){
        if(sched.arreglo_a[i].viva == 1){
            if(sched.arreglo_a[i].tipo == 1){
                cantA++;
            } else if(sched.arreglo_a[i].tipo == 2){
                cantB++;
            }
        }
        if(sched.arreglo_b[i].viva == 1){
            if(sched.arreglo_b[i].tipo == 1){
                cantA++;
            } else if(sched.arreglo_b[i].tipo == 2){
                cantB++;
            }
        }
    }

    print_int(sched.jugadorA.cantTareasDisponibles, 48, 48, C_FG_WHITE + C_BG_BLACK);
    print_int(cantA, 55, 48, C_FG_WHITE + C_BG_BLACK);
    print_int(cantB, 61, 48, C_FG_WHITE + C_BG_BLACK);
    print_int(sched.jugadorB.cantTareasDisponibles, 69, 48, C_FG_WHITE + C_BG_BLACK);
}

void imprimirLanzar(char input){
    if(input==0x2a){
        game_lanzar(1);
    }else if(input==0x36){
        game_lanzar(2);
    }
}


void interrupTeclado(char input){
    imprimirMovimiento(input);
    imprimirLanzar(input);
    actualizarPantalla();
}

void actualizarPantalla(){
    gris_de_nuevo();
    pintar_tareas();
    pintar_jugadores();
    pintar_clocks();
    pintar_puntajes();
}

