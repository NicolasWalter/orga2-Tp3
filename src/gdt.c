/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    [GDT_IDX_NULL_DESC] = (gdt_entry) {
        (unsigned short)    0x0000,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x00,           /* type         */
        (unsigned char)     0x00,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x00,           /* p            */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x00,           /* db           */
        (unsigned char)     0x00,        //batata   /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [CODIGO_KERNEL_0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01, //BATATA          /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [CODIGO_USER_3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01, //BATATA          /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    
    [DATOS_KERNEL_0] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01, //BATATA          /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [DATOS_USER_3] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01, //BATATA          /* p            */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [VIDEO] = (gdt_entry) {
        (unsigned short)    0x9F3F,  //batata       /* limit[0:15]  */
        (unsigned short)    0x8000,  //BATATA       /* base[0:15]   */
        (unsigned char)     0x0B,    //BATATA       /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01, //BATATA          /* p            */
        (unsigned char)     0x0B,   //batata        /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    [IDLE] = (gdt_entry) {
        (unsigned short)    0x0FFF,  //batata       /* limit[0:15]  */
        (unsigned short)    0x0000,  //BATATA       /* base[0:15]   */
        (unsigned char)     0x01,    //BATATA       /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00, //batata          /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x01,   //batata        /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },
    
    [TAREA_INICIAL] = (gdt_entry) { //ES USUARIO O KERNEL?
        (unsigned short)    0x0FFF,  //batata       /* limit[0:15]  */
        (unsigned short)    0x0000,  //BATATA       /* base[0:15]   */
        (unsigned char)     0x01,    //BATATA       /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00, //batata          /* dpl          */
        (unsigned char)     0x01,           /* p            */
        (unsigned char)     0x01,   //batata        /* limit[16:19] */
        (unsigned char)     0x00,          /* avl          */
        (unsigned char)     0x00,           /* l            */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    
    
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};



