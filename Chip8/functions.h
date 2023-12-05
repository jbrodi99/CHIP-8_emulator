#ifndef FUNCTIONS
#include"types.h"
#include<stdio.h> 
#include<stdlib.h>  
#include<string.h> 
#include<stdbool.h> 
#include<errno.h>
#include<time.h>
#include<SDL2/SDL.h>

/**
 * This function initialize all registers and memory in zero
 * 
 * @param machine - pointer to a variable type t_chip_8
 * @return void - dont't return values
*/
void init_emu(t_chip_8 * machine);

/**
 * This function charge the ROM of the game in the memory RAM from [0x200] address
 * 
 * @param machine - pointer to a variable type t_chip_8
 * @return void - don't return values
*/
void load_ROM(t_chip_8 * machine);

/**
 * This function charge the sprites in the memory RAM from [0x50] address
 * 
 * @param machine - pointer to a variable type t_chip_8
*/
void load_sprites(t_chip_8 * machine);

/**
 * This function run the fetch cycle.
 * load in V[x] <- ram[pc]
 * increment pc by two.
 * 
 * @param machine - pointer to a variable of type t_chip_8
 * @return opcode - opcode (instruction) 
*/
uint16_t fetch(t_chip_8 * machine);

/**
 * This function decoding opcode and execute an instruction 
 * First decode 4 most significant bits, then if necessary decode 4 least significant bits 
 * Then execute the correspondig instruction.
 *  
 * @param machine - pointer a struct tope chip8
 * @param opcode - instantiated a coded instruction 
 * @return void - don´t return values  
*/
void decode_exe(t_chip_8* machine, uint16_t opcode);



#endif      //ENDS FUNCTIONS