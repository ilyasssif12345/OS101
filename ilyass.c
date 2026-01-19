#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "outb.h"
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_YELLOW = 14,
	VGA_COLOR_WHITE = 15,
};

uint16_t ara_ra9m(char c,uint8_t lawn_total){
    return (uint16_t) c | (uint16_t) lawn_total << 8;
};
uint8_t lawn(enum vga_color fc,enum vga_color bg){
    return (uint8_t) fc | (uint8_t) bg << 4;
};
size_t strlen(char *c){
    size_t len = 0;
    while (c[len]){
        len++;
        }
    return len;
};
#define VGA_MAGIC 0xB8000
volatile uint16_t *vga_index =(volatile uint16_t *) VGA_MAGIC;

void TERMINAL_CLEAN(enum vga_color bg){
    uint16_t *index = (uint16_t *) VGA_MAGIC;
    uint16_t char_5awi = ara_ra9m(' ',lawn(VGA_COLOR_WHITE,bg));

    while ((uint32_t) index < (uint32_t) 0xB8F9F){
        *index = char_5awi;
         index++;
    
    };
    vga_index =(volatile uint16_t *) VGA_MAGIC;

};

void VGA_PRINTER(char* text,enum vga_color fc,enum vga_color bg){
    uint8_t lawn_tot = lawn(fc,bg);
    size_t str_len = strlen(text);
    if ((uint32_t)vga_index <= (uint32_t) ((uint16_t*)0xB8FA0 - str_len)){ //the pointer automatically substructs 2 bytes for each char because of the casting
    size_t i = 0;
    for (i=0;i< str_len;i++){
        char ch = (char) text[i];
        uint16_t buffer = ara_ra9m(ch,lawn_tot);
        *vga_index = buffer;
        vga_index++;

                };
    };
};
void SET_CURSOR(volatile uint16_t *idx){
     uint16_t idx_ = (uint16_t) (idx - (volatile uint16_t *) VGA_MAGIC);
     uint8_t H_byte = (uint8_t)(idx_ >> 8);
     uint8_t L_byte = (uint8_t)(idx_ & 0xFF);
     outb(0x3D4, 0x0F); //reigter_15
     outb(0x3D5, L_byte);
     outb(0x3D4, 0x0E); //register_14
     outb(0x3D5, H_byte);
};
void inspect_address(void *addr){ 
    const char HEX[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    char text[9] = "";
    int i;
    size_t j=0;
    for (i = 28;i>=0;i-=4){
    uint8_t num = (uint8_t) (((uint32_t)addr >> i) & 0x0F);   
    char char_ = HEX[num];
    text[j] = char_;
    j++;
    };
    text[8] = '\0';
    VGA_PRINTER("0x",VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    VGA_PRINTER(text,VGA_COLOR_WHITE,VGA_COLOR_BLACK);
     

};

void ilyass(void){
    TERMINAL_CLEAN(VGA_COLOR_BLACK);
    VGA_PRINTER("SAMAYKOM",VGA_COLOR_YELLOW,VGA_COLOR_BLUE);
    SET_CURSOR(vga_index);

while(1){

//loop
}

};
