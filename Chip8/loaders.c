#include<types.h>
#include<functions.h>

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

void load_sprites(t_chip_8 * machine){
    FILE * fp = fopen("Chip8/sprites.bin", "rb");
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot open SPRITES file.\n");
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    fread(machine->ram + 0x50, length, 1, fp);
    fclose(fp);
}
