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

void inicializar_en_gris(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; i < 50; ++i){
        int j;
        for(j=0; j < 80; ++j){
            if(i < 1 || i > 44){
                p[i][j].c = 0xFF;
                p[i][j].a = C_FG_BLACK + C_BG_BLACK;
            } else {
                p[i][j].c = 0xB2;
                p[i][j].a = C_FG_LIGHT_GREY + C_BG_BLACK;
            }
        }
    }
}

void gris_de_nuevo(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    for (i = 0; i < 50; ++i){
        int j;
        for(j=0; j < 80; ++j){
            if(!(i < 1 || i > 44)){
                p[i][j].c = 0xB2;
                p[i][j].a = C_FG_LIGHT_GREY + C_BG_BLACK;
            }
        }
    }
}

void pintar_tareas(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    int i;
    while(i<15){
        if(sched.arreglo_h[i].viva){
            p[sched.arreglo_h[i].x][sched.arreglo_h[i].y].c = 0xff;
            p[sched.arreglo_h[i].x][sched.arreglo_h[i].y].a = C_FG_GREEN + C_BG_GREEN;
        }
        i++;
    }

}

void pintar_jugadores(){
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    p[sched.jugadorA->x][sched.jugadorA->y].c = 0X11;
    p[sched.jugadorA->x][sched.jugadorA->y].a = C_FG_WHITE + C_BG_RED;
    p[sched.jugadorB->x][sched.jugadorB->y].c = 0X12;
    p[sched.jugadorB->x][sched.jugadorB->y].a = C_FG_WHITE + C_BG_BLUE;
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
    }else if(input==0x2a){
        //print("LShift",80,1,3);
    }else if(input==0x36){
        //print("RShift",80,1,3);
    }
}
