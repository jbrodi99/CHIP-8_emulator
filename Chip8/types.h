#ifndef TYPES
#define TYPES
#include<stdint.h>
#define MAX_SIZE_RAM 4096                   //size of memory RAM (4Kb)
#define REG 16                              //numbers of registers 
#define WIDTH 640
#define HEIGHT 320
/**
 * the struct t_chip_8 contain:
 * 
 * -Array RAM[4096] that simulate the memory RAM of the chip 8 arquitecture. Size of elements is the 8 bits.
 * 
 * -PC is a program counter register, this register is used to store the currently executing address, should be 16 bits.
 * 
 * -Stack is an array of 16, 16 bit values, used to store the address the interpreter shoud return to when finished with a subrutine.
 * 
 * -The SP register is used to point to the topmost level of the stack.
 * 
 * -V is an array of 16, 8 bit values, used for simulate the 16 general registers of the chip 8
 * 
 * -I is a variable of 16 bit for simulate the index register
 * 
 * -dt is delay timer (clock) and st is a sound timer register.  
*/
typedef struct t_chip_8 {

    uint8_t ram[MAX_SIZE_RAM];              
    uint16_t pc;

    uint16_t stack[REG];
    uint16_t sp;
    
    uint8_t V[REG];
    uint16_t I;
    uint8_t dt, st;

} t_chip_8;

typedef struct t_nibbles
{

    uint16_t nnn;
    uint8_t kk;
    uint8_t x; 
    uint8_t y; 
    uint8_t n; 
    uint8_t p;
} t_nibbles;

#endif 