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




// gcc -o prueba  main.c -L/usr/lib/x86_64-linux-gnu -lSDL2-2.0 (comando para compilar)

int main(){

    SDL_Window * win = NULL;
    SDL_Renderer * renderer = NULL;
    //t_chip_8 emu;//emulator type chip8 
    //uint16_t opcode;//opcode variable                
    //srand(time(NULL));
    //init_emu(&emu);
    //load_ROM(&emu);
    
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL could not initialize SDL_ERROR: %s\n", SDL_GetError());
        return -1;
    }
    else{
        win = SDL_CreateWindow("CHIP_8",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    640, 320, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
        
        if(win = NULL){
            printf("Window could not be created, SDL_Error: %s\n", SDL_GetError());
            return -1;
        }

    }
    
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    bool running = true;
    
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))   
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;
            
            default:
                break;
            }
        }
        
        //opcode = fetch(&emu);

        //decode_exe(&emu, opcode);

    }

    return 0;
}