#include<SDL2/SDL.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {

    SDL_Window* fenetre; // window

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Impossible de se connecter à SDL : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;

    }

    // créer la fenêtre
    fenetre = SDL_CreateWindow("Addition", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 900, SDL_WINDOW_SHOWN);
    if(fenetre == NULL) {
        printf("Impossible de créer la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    
    // le rendu 
    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if(rendu == NULL) {
        printf("Impossible de créer le rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawColor(rendu, 255, 255, 255, 255); // couleur blanche
    SDL_RenderClear(rendu);
    SDL_RenderPresent(rendu);
    SDL_Delay(1000);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return EXIT_SUCCESS;
}