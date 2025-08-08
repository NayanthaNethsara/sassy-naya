#include "snake.h"

void initSnake(Snake &snake, int startX, int startY, int gridSize)
{
    snake.body.clear();
    snake.body.push_back({startX, startY, gridSize, gridSize}); // head
    snake.dx = 0;
    snake.dy = 0;
    snake.gridSize = gridSize;
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
                snake.dy = -snake.gridSize;
            }
            break;
        case SDLK_DOWN:
            if (snake.dy == 0)
            {
                snake.dx = 0;
                snake.dy = snake.gridSize;
            }
            break;
        case SDLK_LEFT:
            if (snake.dx == 0)
            {
                snake.dx = -snake.gridSize;
                snake.dy = 0;
            }
            break;
        case SDLK_RIGHT:
            if (snake.dx == 0)
            {
                snake.dx = snake.gridSize;
                snake.dy = 0;
            }
            break;
        }
    }
}

void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight)
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > moveDelay)
    {
        lastMoveTime = currentTime;

        // Move body segments from tail to head
        for (int i = (int)snake.body.size() - 1; i > 0; --i)
        {
            snake.body[i] = snake.body[i - 1];
        }

        // Move head
        snake.body[0].x += snake.dx;
        snake.body[0].y += snake.dy;

        // Keep head inside boundaries
        if (snake.body[0].x < 0)
            snake.body[0].x = 0;
        if (snake.body[0].y < 0)
            snake.body[0].y = 0;
        if (snake.body[0].x > windowWidth - snake.gridSize)
            snake.body[0].x = windowWidth - snake.gridSize;
        if (snake.body[0].y > windowHeight - snake.gridSize)
            snake.body[0].y = windowHeight - snake.gridSize;
    }
}

void renderSnake(SDL_Renderer *renderer, const Snake &snake)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (const SDL_Rect &segment : snake.body)
    {
        SDL_RenderFillRect(renderer, &segment);
    }
}

void growSnake(Snake &snake)
{
    // Add a new segment at the tail’s position (duplicates last segment)
    SDL_Rect tail = snake.body.back();
    snake.body.push_back(tail);
}
