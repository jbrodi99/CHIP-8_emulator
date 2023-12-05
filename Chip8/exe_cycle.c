#include"types.h"
#include"functions.h"
#include"misa.c"


uint16_t fetch(t_chip_8 * machine){
    
    uint16_t opcode;
    /*all instrutions are 2 bytes long and stored most-significant bytes first
        opcode = |b15|b14|b13|b12|b11|b10|b9|b8|  |b7|b6|b5|b4|b3|b2|b1|b0|
    first fetch 1 byte most significant
        |0|0|0|0|0|0|0|0|b15|b14|b13|b12|b11|b10|b9|b8|
    then I shift 8 bits to the left with operantn '<<'
        |b15|b14|b13|b12|b11|b10|b9|b8|0|0|0|0|0|0|0|0|
    then I do an OR with the next value
        |b15|b14|b13|b12|b11|b10|b9|b8|0|0|0|0|0|0|0|0|
    OR
        |0|0|0|0|0|0|0|0|b7|b6|b5|b4|b3|b2|b1|b0|
        ---------------------------------------------------------
        |b15|b14|b13|b12|b11|b10|b9|b8|b7|b6|b5|b4|b3|b2|b1|b0|
    */
    opcode = ((machine->ram[machine->pc] << 8) | machine->ram[machine->pc + 1]);
    //increment the value of PC in two and I mask  PC AND with 0xFFF in case the overflow
    machine->pc = (machine->pc + 2) & 0xFFF;

    return opcode;
}

void deco_inst_0(t_chip_8 * machine, t_nibbles nibbles){
    void (*proc0[]) (t_chip_8*, t_nibbles) = {cls, ret};
    if (nibbles.kk == 0xE0)
        proc0[0] (machine, nibbles);
    else if(nibbles.kk == 0xEE)   
        proc0[1] (machine, nibbles);
}

void deco_inst_8(t_chip_8 * machine, t_nibbles nibbles){

    void (*proc8[]) (t_chip_8*, t_nibbles) = {load_Vx_Vy, or_Vx_Vy, and_Vx_Vy,xor_Vx_Vy,add_Vx_Vy,sub_Vx_Vy,shr_Vx,sub_Vy_Vx,NOOP, NOOP, NOOP, NOOP, NOOP, NOOP, shl_Vx};

    proc8[nibbles.n] (machine, nibbles);
}

void deco_inst_14(t_chip_8 *machine, t_nibbles nibble){

    void (*proc14[]) (t_chip_8*, t_nibbles) = {inst_14, inst_14_b};

    if (nibble.kk == 0x9E)
        proc14[0] (machine, nibble);
    else   
        proc14[1] (machine, nibble);
}

void deco_inst_15(t_chip_8 * machine, t_nibbles nibbles){

    uint8_t opcode[] = {0x07,0x0A, 0x15, 0x18,0x1E,0x29,0x33,0x55,0x65};
    int i = 0;
    void (*proc15[]) (t_chip_8*, t_nibbles) = {load_Vx_DT, load_Vx_key, load_DT_Vx, load_ST_Vx, add_I_Vx, load_F_Vx,load_bcd_number,load_I_V, load_V_I};

    while (nibbles.kk != opcode[i] && i < 9)
        i++;
    if (i != 9)
        proc15[i] (machine, nibbles);
}

void decode_exe(t_chip_8* machine, uint16_t opcode){
    
    t_nibbles nibb;
    init_nibbles(&nibb , opcode);

    void (*proc[]) (t_chip_8*, t_nibbles) = {deco_inst_0,jump, call, se, sne, se_x_y,load_x_byte, add_x_byte,
                                            deco_inst_8, sne_Vx_Vy, load_I_nnn, jump_V0_nnn, rnd_Vx_byte, DRAW, deco_inst_14, deco_inst_15};

    proc[nibb.p] (machine, nibb);
}


