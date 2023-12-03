#include"types.h"
#include"functions.h"


void init_emu(t_chip_8 * machine){

    machine->pc = machine->I = machine->dt = machine->sp = machine->sp = 0x00;
    //memset from string.h used for initialize arrays in 0x00 
    memset(machine->ram, 0x00,MAX_SIZE_RAM);
    memset(machine->stack, 0x00, REG);
    memset(machine->V, 0x00, REG);

}

void load_ROM(t_chip_8 * machine){
    
    //declarate  length variable, i used for load the legth of the ROMs
    int length;
    //declarate fp variable type FILE* and open the ROM file in mode read
    FILE * fp = fopen("ROMs/Particle Demo [zeroZshadow, 2008].ch8", "rb");
    
    if (fp == NULL){ //the file don't exists
        fprintf(stderr, "Cannot open ROM file.\n"); //printf error
        exit(1);    //exit program
    }
    
    //used fseek/ftell/fseek to retrive file size
    fseek(fp,0,SEEK_END);
    length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //read ROM and load in memory RAM from position 0x200 
    fread(machine->ram + 0x200, length,1,fp);
    fclose(fp);
}

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
    
    uint8_t r;
    uint16_t nnn = opcode & 0xFFF;
    uint8_t kk = opcode & 0xFF;
    uint8_t x = (opcode >> 8) & 0xF;
    uint8_t y = (opcode >> 4) & 0xF;
    uint8_t n = opcode & 0xF;
    uint8_t p = (opcode >> 12);

    switch (p)
    {
    case 0:
        //clear display
        if (kk == 0xE0)
        {
            printf("CLS\n");
        }else if (kk == 0xEE)//RET subrutine
        {
            printf("RET\n");
        }
        break;
    case 1:
        //JUMP nnn
        machine->pc = nnn;
        break;
    case 2:
        //CALL subrutine
        //inc SP
        machine->sp++;
        //push(pc)
        machine->stack[machine->sp] = machine->pc;
        //MOV PC, nnn(jmp nnn)
        machine->pc = nnn;
        break;
    case 3:
        //SE Vx, byte(skip equal)
        if (machine->V[x] == kk)
        {
            machine->pc += 0x2;
        }
        break;
    case 4:
        //SNE Vx, byte(Skip not equal)
        if (machine->V[x] != kk)
        {
            machine->pc += 0x2;
        }
        break;
    case 5:
        //SE Vx, Vy (skip equal)
        if (machine->V[x] == machine->V[y])
        {
            machine->pc += 2;
        }
        break;
    case 6:
        //LD Vx, byte (MOV Vx, kk)
        machine->V[x] = kk;
        break;
    case 7:
        //ADD Vx, kk 
        machine->V[x] += kk;
        break;
    case 8:
        switch (n)
        {
        case 0:
            //LD Vx, Vy
            machine->V[x] = machine->V[y];
            break;
        case 1:
            //OR Vx,Vy
            machine->V[x] |= machine->V[y];
            break;
        case 2: 
            //AND Vx, Vy
            machine->V[x] &= machine->V[y];
            break;
        case 3:
            //XOR Vx, Vy
            machine->V[x] ^= machine->V[y];
            break;
        case 4:
            //ADD Vx, Vy
            if(((machine->V[x] + machine->V[y]) & 0xFF) < machine->V[x]) 
                machine->V[0xF] = 0x1;
            machine->V[x] =(machine->V[x] + machine->V[y] ) & 0xFF;
            break;
        case 5:
            //SUB Vx, Vy
            if (machine->V[x] > machine->V[y])
                machine->V[0xF] = 0x1;
            machine->V[x] = (machine->V[x] - machine->V[y]) & 0xFF;
            break;
        case 6:
            //SHR Vx
            if (machine->V[x] % 0x1 == 0x1)
                machine->V[0xF] = 0x1;
            machine->V[x] = machine->V[x] >> 1;
            break;
        case 7:
            //SUBN Vx, Vy
            if (machine->V[y] > machine->V[x])
                machine->V[0xF] = 0x1;
            machine->V[x] = machine->V[y] - machine->V[x];
            break;
        case 14:
            //SHL Vx
            if ((machine->V[x] & 0x8000) == 0x8000)
                machine->V[0xF] = 0x1;
            machine->V[x] = machine->V[x] << 1;
            break;
        default:
            break;
        }
        break;
    case 9:
        //SNE Vx, Vy
        if (machine->V[x] != machine->V[y])
            machine->pc += 0x2;
        break;
    case 10:
        // LD I, nnn
        machine->I = nnn;
        break;
    case 11:
        //JMP VO + nnn
        machine->pc = (nnn + machine->V[0]);
        break;
    case 12:
        //RND Vx, byte
        r = rand()% 256;
        machine->V[x] = kk & r;
        break;
    
    default:
        break;
    }
}