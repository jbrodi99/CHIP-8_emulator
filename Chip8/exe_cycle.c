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

void decode_exe(t_chip_8* machine, uint16_t opcode){
    
    t_nibbles nibb;
    init_nibbles(&nibb , opcode);

    void (*proc[]) (t_chip_8*, t_nibbles) = {ret, jump, call, se, sne, se_x_y,load_x_byte, add_x_byte,
                                            sne_Vx_Vy, load_I_nnn, jump_V0_nnn, rnd_Vx_byte, 
                                            load_Vx_DT, load_Vx_key, load_DT_Vx, load_ST_Vx,
                                            add_I_Vx, load_F_Vx, load_bcd_number, load_I_V, load_V_I};

}


