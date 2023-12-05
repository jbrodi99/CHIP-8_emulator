#include<types.h>
#include<functions.h>

void init_emu(t_chip_8 * machine){

    machine->pc = machine->I = machine->dt = machine->sp = machine->sp = 0x00;
    //memset from string.h used for initialize arrays in 0x00 
    memset(machine->ram, 0x00,MAX_SIZE_RAM);
    memset(machine->stack, 0x00, REG);
    memset(machine->V, 0x00, REG);

}
void init_nibbles(t_nibbles * nibbles, uint16_t opcode){
    
    nibbles->nnn = opcode & 0xFFF;
    nibbles->kk = opcode & 0xFF;
    nibbles->x = (opcode >> 8) & 0xF;
    nibbles->y = (opcode >> 4) & 0xF;
    nibbles->n = opcode & 0xF;
    nibbles->p = (opcode >> 12);
    
}