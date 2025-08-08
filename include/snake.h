#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <vector>

struct Snake
{
    std::vector<SDL_Rect> body;
    int dx;
    int dy;
    int gridSize;
};

void initSnake(Snake &snake, int startX, int startY, int gridSize);
void handleInput(SDL_Event &event, Snake &snake);
void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight);
void renderSnake(SDL_Renderer *renderer, const Snake &snake);
void growSnake(Snake &snake);

#endif // SNAKE_H
