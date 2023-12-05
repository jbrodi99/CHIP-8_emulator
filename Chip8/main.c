/**
*Hi there! It is my first middle proyect in programing, also it's my first time writing the comment in english
*
*This work is a CHIP 8 emulator, the idea is programing the memory structure a CHIP 8 and the UC (unit control) with the fetch, decode and  
*execute cycle. So that you play the games in this emulator. 
*
*Copyright (c) Juan Cruz Rodriguez 
*3/12723
*
*/


#include"types.h"
#include"functions.h"
#include"init.c"
#include"loaders.c"
#include"exe_cycle.c"

int main(){

    t_chip_8 emu;//emulator type chip8 
    uint16_t opcode;//opcode variable                
    srand(time(NULL));

    bool running = true;
    while (running)
    {
        init_emu(&emu);
        load_ROM(&emu);

        opcode = fetch(&emu);

        decode_exe(&emu, opcode);

    }
    

    return 0;
}