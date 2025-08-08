#include "snake.h"

void initSnake(Snake &snake, int startX, int startY, int gridSize)
{
    snake.head = {startX, startY, gridSize, gridSize};
    snake.dx = 0;
    snake.dy = 0;
}

void handleInput(SDL_Event &event, Snake &snake)
{
    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            if (snake.dy == 0)
            {
                snake.dx = 0;
                snake.dy = -snake.head.h;
            }
            break;
        case SDLK_DOWN:
            if (snake.dy == 0)
            {
                snake.dx = 0;
                snake.dy = snake.head.h;
            }
            break;
        case SDLK_LEFT:
            if (snake.dx == 0)
            {
                snake.dx = -snake.head.w;
                snake.dy = 0;
            }
            break;
        case SDLK_RIGHT:
            if (snake.dx == 0)
            {
                snake.dx = snake.head.w;
                snake.dy = 0;
            }
            break;
        }
    }
}

void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight, int gridSize)
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > moveDelay)
    {
        lastMoveTime = currentTime;

        snake.head.x += snake.dx;
        snake.head.y += snake.dy;

        if (snake.head.x < 0)
            snake.head.x = 0;
        if (snake.head.y < 0)
            snake.head.y = 0;
        if (snake.head.x > windowWidth - gridSize)
            snake.head.x = windowWidth - gridSize;
        if (snake.head.y > windowHeight - gridSize)
            snake.head.y = windowHeight - gridSize;
    }
}

void renderSnake(SDL_Renderer *renderer, const Snake &snake)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &snake.head);
}
