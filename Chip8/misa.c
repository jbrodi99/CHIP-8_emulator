#include<types.h>
#include<functions.h>

//void clear display();

void ret(t_chip_8 * machine, t_nibbles nibbles){
    machine->pc = machine->stack[machine->sp];
    machine->sp = machine->sp - 1;
}

void jump(t_chip_8 * machine, t_nibbles nibbles){
    machine->pc = nibbles.nnn;
}

void call(t_chip_8 * machine, t_nibbles nibbles){
    machine->sp++;
    machine->stack[machine->sp] = machine->pc;
    machine->pc = nibbles.nnn;
}

void se(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] == nibbles.kk) 
        machine->pc += 0x2;
}

void sne(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] != nibbles.kk)
        machine->pc += 0x2;
}

void se_x_y(t_chip_8 *machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] == machine->V[nibbles.y])
        machine->pc += 2;
}

void load_x_byte(t_chip_8 *machine, t_nibbles nibbles){
    machine->V[nibbles.x] = nibbles.kk;
}

void add_x_byte(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] += nibbles.kk;
}

//WARNING INTRUCTIONS DOBLE DECODE 

void load_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] = machine->V[nibbles.y];
}

void or_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] |= machine->V[nibbles.y];
}

void and_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] &= machine->V[nibbles.y];
}

void xor_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] ^= machine->V[nibbles.y];
}

void add_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    if(((machine->V[nibbles.x] + machine->V[nibbles.y]) & 0xFF) < machine->V[nibbles.x]) 
        machine->V[0xF] = 0x1;
        machine->V[nibbles.x] =(machine->V[nibbles.x] + machine->V[nibbles.y] ) & 0xFF;
}

void sub_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] > machine->V[nibbles.y])
        machine->V[0xF] = 0x1;
        machine->V[nibbles.x] = (machine->V[nibbles.x] - machine->V[nibbles.y]) & 0xFF;
}
void shr_Vx(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] % 0x1 == 0x1)
        machine->V[0xF] = 0x1;
        machine->V[nibbles.x] = machine->V[nibbles.x] >> 1;
}

void sub_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.y] > machine->V[nibbles.x])
        machine->V[0xF] = 0x1;
        machine->V[nibbles.x] = machine->V[nibbles.y] - machine->V[nibbles.x];
}

void shl_Vx(t_chip_8 *machine, t_nibbles nibbles){
    if ((machine->V[nibbles.x] & 0x8000) == 0x8000)
        machine->V[0xF] = 0x1;
        machine->V[nibbles.x] = machine->V[nibbles.x] << 1;
}

//intrution from 9

void sne_Vx_Vy(t_chip_8 * machine, t_nibbles nibbles){
    if (machine->V[nibbles.x] != machine->V[nibbles.y])
        machine->pc += 0x2;
}

void load_I_nnn(t_chip_8 * machine, t_nibbles nibbles){
    machine->I = nibbles.nnn;
}

void jump_V0_nnn(t_chip_8 *machine, t_nibbles nibbles){
    machine->pc = (nibbles.nnn + machine->V[0]);
}

void rnd_Vx_byte(t_chip_8 *machine, t_nibbles nibbles){
    uint8_t r;
    r = rand()% 256;
    machine->V[nibbles.x] = nibbles.kk & r;
}

//DRAW();
//it 14
//p = 15
void  load_Vx_DT(t_chip_8 * machine, t_nibbles nibbles){
    machine->V[nibbles.x] = machine->dt;
}

void load_Vx_key(t_chip_8 * machine, t_nibbles nibbles){
    //aijji
}

void load_DT_Vx(t_chip_8 * machine, t_nibbles nibbles){
    machine->dt = machine->V[nibbles.x];
}

void load_ST_Vx(t_chip_8 * machine, t_nibbles nibbles){
    machine->st = machine->V[nibbles.x];
}

void add_I_Vx(t_chip_8 * machine, t_nibbles nibbles){
    machine->I = machine->I + machine->V[nibbles.x];
}

void load_F_Vx(t_chip_8 * machine, t_nibbles nibbles){
    machine->I = 0x50 + (machine->V[nibbles.x] * 5);
}

void load_bcd_number(t_chip_8 * machine, t_nibbles nibbles){
    machine->ram[machine->I + 2] = machine->V[nibbles.x] % 10;
    machine->ram[machine->I + 1] = (machine->V[nibbles.x]/10) % 10;
    machine->ram[machine->I] = (machine->V[nibbles.x]/100) % 10;
}

void load_I_V(t_chip_8 * machine, t_nibbles nibbles){
    for (int i = 0; i < REG; i++)
        machine->ram[machine->I + i] = machine->V[i];
}

void load_V_I(t_chip_8 * machine, t_nibbles nibbles){
    for (int i = 0; i < REG; i++)
        machine->V[i] = machine->ram[machine->I + i];
}

