#include "snake.h"
#include <iostream>

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

        SDL_Rect newHead = snake.body.front();
        newHead.x += snake.dx;
        newHead.y += snake.dy;

        // Keep inside window bounds (or wrap)
        if (newHead.x < 0)
            newHead.x = 0;
        if (newHead.y < 0)
            newHead.y = 0;
        if (newHead.x > windowWidth - snake.gridSize)
            newHead.x = windowWidth - snake.gridSize;
        if (newHead.y > windowHeight - snake.gridSize)
            newHead.y = windowHeight - snake.gridSize;

        // Insert new head at front
        snake.body.insert(snake.body.begin(), newHead);

        if (snake.pending_growth > 0)
        {
            // Don’t remove tail — snake grows
            snake.pending_growth--;
        }
        else
        {
            // Remove tail to keep length constant
            snake.body.pop_back();
        }
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
    snake.pending_growth++;
}

// Returns true if snake head collides with its body
bool checkSelfCollision(const Snake &snake)
{
    const SDL_Rect &head = snake.body[0];

    std::cout << "Checking self-collision for snake head at ("
              << head.x << ", " << head.y << ")\n";

    // console logging for debugging
    std::cout << "Snake body size: " << snake.body.size() << "\n";
    std::cout << "Snake body segments:\n";
    for (size_t i = 0; i < snake.body.size(); ++i)
    {
        std::cout << "Segment " << i << ": ("
                  << snake.body[i].x << ", " << snake.body[i].y << ")\n";
    }

    for (size_t i = 1; i < snake.body.size(); ++i)
    {
        if (head.x == snake.body[i].x && head.y == snake.body[i].y)
        {
            return true;
        }
    }
    return false;
}
