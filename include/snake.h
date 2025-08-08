#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

struct Snake
{
    SDL_Rect head;
    int dx;
    int dy;
};

void initSnake(Snake &snake, int startX, int startY, int gridSize);
void handleInput(SDL_Event &event, Snake &snake);
void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight, int gridSize);
void renderSnake(SDL_Renderer *renderer, const Snake &snake);

#endif // SNAKE_H
