#include "window.h"

Window *create_window(char *title, int width, int height) {
    Window *window = malloc(sizeof(Window));
    window->win = SDL_CreateWindow(title, 0, 0, width, height, 0);
    window->rend = SDL_CreateRenderer(window->win, -1, SDL_RENDERER_ACCELERATED);
    return window;
}

int destroy_window(Window *window) {
    if (!window) return 1;
    SDL_DestroyRenderer(window->rend);
    SDL_DestroyWindow(window->win);
    free(window);
    return 0;
}

