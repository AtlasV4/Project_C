#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "utils.h"
#include "visual.h"
#include "sorting.h"

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    if (TTF_Init() != 0) {
        fprintf(stderr, "TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Window *win = NULL;
    SDL_Renderer *ren = NULL;
    if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &win, &ren) != 0) {
        fprintf(stderr, "SDL_CreateWindowAndRenderer: %s\n", SDL_GetError());
        TTF_Quit(); SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

    TTF_Font *font = TTF_OpenFont("DejaVuSans.ttf", 20);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
        SDL_DestroyRenderer(ren); SDL_DestroyWindow(win);
        TTF_Quit(); SDL_Quit();
        return EXIT_FAILURE;
    }

    int running = 1;
    int N = 50;
    MenuPosition pos = MENU_LEFT;
    int *tab = generateArray(N, FULLSHUFFLE);

    int delay = 30;
    const int delay_min = 1;
    const int delay_max = 500;

    while (running) {

        drawArray(ren, tab, N, pos, -1, -1, -1);
        drawMenuOverlay(ren, font, pos, delay);
        SDL_RenderPresent(ren);


        Algo chosen = ALGO_NONE;
        Shuffle shuffleChosen = NOSHUFFLE;
        SDL_Event e;

        while (chosen == ALGO_NONE && running) {
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_QUIT) { running = 0; break; }
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_ESCAPE: running = 0; break;
                        case SDLK_b: chosen = ALGO_BUBBLE;    break;
                        case SDLK_i: chosen = ALGO_INSERTION; break;
                        case SDLK_s: chosen = ALGO_SELECTION; break;
                        case SDLK_q: chosen = ALGO_QUICK;     break;
                        case SDLK_F1: pos = MENU_LEFT;   break;
                        case SDLK_F2: pos = MENU_RIGHT;  break;
                        case SDLK_t:
                            shuffleChosen = TINYSHUFFLE;
                            free(tab);
                            tab = generateArray(N, shuffleChosen);
                            break;
                        case SDLK_f:
                            shuffleChosen = FULLSHUFFLE;
                            free(tab);
                            tab = generateArray(N, shuffleChosen);
                            break;
                        case SDLK_n:
                            shuffleChosen = NOSHUFFLE;
                            free(tab);
                            tab = generateArray(N, shuffleChosen);
                            break;
                            case SDLK_KP_PLUS:
                        case SDLK_EQUALS:
                            if (delay > delay_min) delay += 5;
                            break;

                        case SDLK_KP_MINUS:
                        case SDLK_MINUS:
                            if (delay < delay_max) delay -= 5;
                            break;
                        default: break;
                    }
                }
            }

            drawArray(ren, tab, N, pos, -1, -1, -1);            
            drawMenuOverlay(ren, font, pos, delay);
            SDL_RenderPresent(ren);
            SDL_Delay(16);
        }

        if (!running) break;

        runAlgorithm(ren, font, &pos, chosen, tab, N, delay);
    }

    free(tab);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return EXIT_SUCCESS;
}
