#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include "visual.h"
#include "utils.h"
#include "sorting.h"

int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 400;

static void drawText(SDL_Renderer *r, TTF_Font *font, const char *txt, int x, int y) {
    SDL_Color c = {230,230,230,255};
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, txt, c);
    if (!surf) return;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, surf);
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_FreeSurface(surf);
    SDL_RenderCopy(r, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
}

void drawMenuOverlay(SDL_Renderer *r, TTF_Font *font, MenuPosition pos, int delay) {
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    const int PAD = 10;
    SDL_Rect panel;

    if (pos == MENU_LEFT || pos == MENU_RIGHT) {
        panel.w = 215; panel.h = SCREEN_HEIGHT;
        panel.x = (pos == MENU_LEFT) ? 0 : (SCREEN_WIDTH - panel.w);
        panel.y = 0;
    }

    SDL_SetRenderDrawColor(r, 20, 20, 26, 180);
    SDL_RenderFillRect(r, &panel);
    SDL_SetRenderDrawColor(r, 200, 200, 220, 220);
    SDL_RenderDrawRect(r, &panel);
    char buf[64];
    sprintf(buf, "[+/-] Vitesse: %d ms", delay);

    int x = panel.x + PAD, y = panel.y + PAD;
    drawText(r, font, "Choisissez un tri :", x, y); y += 28;
    drawText(r, font, "[B] Bubble", x, y); y += 24;
    drawText(r, font, "[I] Insertion", x, y); y += 24;
    drawText(r, font, "[S] Selection", x, y); y += 24;
    drawText(r, font, "[Q] Quick", x, y); y += 28;
    drawText(r, font, "Position du menu :", x , y); y += 28;
    drawText(r, font, "[F1] Gauche", x, y); y += 24; 
    drawText(r, font, "[F2] Droite", x, y); y += 28; 
    drawText(r, font, "Modes de mélange :", x, y); y += 28;
    drawText(r, font, "[T]: TinyShuffle", x, y); y += 24;
    drawText(r, font, "[F]: FullShuffle", x, y); y += 24;
    drawText(r, font, "[N]: NoShuffle", x, y); y += 28;
    drawText(r, font, "Autres :", x , y); y += 28;
    drawText(r, font, buf, x, y); y+= 24;
    drawText(r, font, "[ESC]: Quit / Stop", x, y);



}

int handleOverlayEvents(MenuPosition *pos, int *abort_sort) {
    SDL_Event e;
    int changed = 0;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) { *abort_sort = 1; return 1; }
        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE: *abort_sort = 1; break;
                case SDLK_F1: *pos = MENU_LEFT;   changed = 1; break;
                case SDLK_F2: *pos = MENU_RIGHT;  changed = 1; break;
                default: break;
            }
        }
    }
    return changed;
}

void drawArray(SDL_Renderer *renderer, int *tab, int size, MenuPosition pos, int hiA, int hiB, int pivot) {   
    const int menuWidth = 215;
    int startX = (pos == MENU_LEFT) ? menuWidth : 0;
    int endWidth = SCREEN_WIDTH - menuWidth;

    if (endWidth < 1) endWidth = 1;
    if (size < 1) return;

    int base = endWidth / size;
    int rem  = endWidth - base * size;

    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);

    int x = startX;
    for (int i = 0; i < size; i++) {
        int w = base + (i < rem ? 1 : 0);
        int barw = (w > 1 ? w - 1 : 1);

        SDL_Rect rect;
        rect.x = x;
        rect.w = barw;
        rect.h = (tab[i] * SCREEN_HEIGHT) / size;
        rect.y = SCREEN_HEIGHT - rect.h;

        float hue = (360.0f * tab[i]) / size;
        int r, g, b;
        HSVtoRGB(hue, 1.0f, 1.0f, &r, &g, &b);

        if (i == pivot) { 
            r = 255; 
            g = 255;   
            b = 255; 
        }
        if (i == hiA || i == hiB) { 
            r = 255; 
            g = 0; 
            b = 0; 
        } 

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderFillRect(renderer, &rect);

        x += w;
    }
}



void renderFrame(SDL_Renderer *r, TTF_Font *font, MenuPosition pos, int *tab, int size, int hiA, int hiB, int pivot, int delay)
{
    drawArray(r, tab, size, pos, hiA, hiB, pivot);
    drawMenuOverlay(r, font, pos, delay);
    SDL_RenderPresent(r);
}

void runAlgorithm(SDL_Renderer *r, TTF_Font *font, MenuPosition *pos, Algo algo, int *tab, int N, int delay) 
{
    switch (algo) {
        case ALGO_BUBBLE:    
            bubbleSorting(tab, N, r, font, pos, delay);            
            break;
        case ALGO_INSERTION: 
            insertionSorting(tab, N, r, font, pos, delay);         
            break;
        case ALGO_SELECTION: 
            selectionSorting(tab, N, r, font, pos, delay);         
            break;
        case ALGO_QUICK:     
            quickSorting(tab, 0, N-1, N, r, font, pos, delay);     
            break;
        default: break;
    }

    renderFrame(r, font, *pos, tab, N, -1, -1, -1, delay);    
    SDL_Delay(600);
}

