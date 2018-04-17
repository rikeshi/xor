#pragma once
#include <SDL2/SDL.h>

typedef struct Window {
    SDL_Window *win;
    SDL_Renderer *rend;
} Window;

Window *create_window(char *title, int width, int height);
int destroy_window(Window *window);
