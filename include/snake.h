#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>
#include <vector>
#include <queue>

struct Snake
{
    std::vector<SDL_Rect> body;
    int dx, dy; // current direction
    int gridSize;
    int pending_growth = 0;
    std::queue<std::pair<int, int>> directionQueue;
};

void initSnake(Snake &snake, int startX, int startY, int gridSize);
void handleInput(SDL_Event &event, Snake &snake);
void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight);
void renderSnake(SDL_Renderer *renderer, const Snake &snake);
void growSnake(Snake &snake);
bool checkSelfCollision(const Snake &snake);

#endif // SNAKE_H
