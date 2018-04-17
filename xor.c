#include "nn.h"
#include "window.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WIN_W 600
#define WIN_H 600
#define BLOCK_SIZE 15

int main(void) {
    srand(time(NULL));
    SDL_Init(SDL_INIT_VIDEO);

    Window *window = create_window("XOR!", WIN_W, WIN_H);
    NeuralNetwork *nn = create_nn(2, 4, 1);

    SDL_Rect block = { 0, 0, BLOCK_SIZE, BLOCK_SIZE };

    int nrows = WIN_H / BLOCK_SIZE;
    int ncols = WIN_W / BLOCK_SIZE;

    int running = 1;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    return running = 0;
            }
        }

        // predict
        for (int i = 0; i < nrows; i++) {
            for(int j = 0; j < ncols; j++) {
                block.x = i * BLOCK_SIZE;
                block.y = j * BLOCK_SIZE;
                float x1 = i / (float)nrows;
                float x2 = j / (float)ncols;
                float input[] = { x1, x2 };
                Matrix *output = nn_predict(nn, input);
                int lum = output->data[0] * 255;
                SDL_SetRenderDrawColor(window->rend,
                        lum, lum, lum, 255);
                SDL_RenderFillRect(window->rend, &block);
            }
        }

        SDL_RenderPresent(window->rend);

        // train on 30 samples per frame
        for(int i = 0; i < 30; i++) {
            int a = rand() & 1;
            int b = rand() & 1;
            int y = a ^ b;
            float ax[] = { a, b };
            float ay[] = { y };
            nn_predict(nn, ax);
            nn_train(nn, ay);
        }

        // wait for 1/30th of a second
        SDL_Delay(1000/30);
    }

    destroy_nn(nn);
    destroy_window(window);
    SDL_Quit();
}
