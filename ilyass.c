#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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

void VGA_PRINTER(char* text,enum vga_color fc,enum vga_color bg){
    uint8_t lawn_tot = lawn(fc,bg);
    size_t str_len = strlen(text);
    if ((uint32_t)vga_index < (uint32_t) ((uint16_t*)0xB8F9F - str_len)){
    size_t i = 0;
    for (i=0;i< str_len;i++){
        char ch = (char) text[i];
        uint16_t buffer = ara_ra9m(ch,lawn_tot);
        *vga_index = buffer;
        vga_index++;

                };
    };
};
void ilyass(void){
VGA_PRINTER("SAMAYKOM",VGA_COLOR_YELLOW,VGA_COLOR_BLACK);

while(1){

//loop
}

};
