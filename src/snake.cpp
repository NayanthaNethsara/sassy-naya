#include "snake.h"
#include <iostream>

void initSnake(Snake &snake, int startX, int startY, int gridSize)
{
    snake.body.clear();
    snake.body.push_back({startX, startY, gridSize, gridSize}); // head
    snake.gridSize = gridSize;                                  // set first
    snake.dx = snake.gridSize;                                  // now dx gets correct value
    snake.dy = 0;
    snake.pending_growth = 10;
}

const int MAX_QUEUE_SIZE = 2;

void handleInput(SDL_Event &event, Snake &snake)
{
    if (event.type == SDL_KEYDOWN)
    {
        int ndx = snake.dx;
        int ndy = snake.dy;

        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            ndx = 0;
            ndy = -snake.gridSize;
            break;
        case SDLK_DOWN:
            ndx = 0;
            ndy = snake.gridSize;
            break;
        case SDLK_LEFT:
            ndx = -snake.gridSize;
            ndy = 0;
            break;
        case SDLK_RIGHT:
            ndx = snake.gridSize;
            ndy = 0;
            break;
        default:
            return;
        }

        std::pair<int, int> lastDir = {snake.dx, snake.dy};
        if (!snake.directionQueue.empty())
        {
            lastDir = snake.directionQueue.back();
        }

        // Ignore if opposite
        if (ndx == -lastDir.first && ndy == -lastDir.second)
        {
            return;
        }

        if ((int)snake.directionQueue.size() < MAX_QUEUE_SIZE)
        {
            snake.directionQueue.push({ndx, ndy});
        }
        // else ignore input if queue full
    }
}

void updateSnake(Snake &snake, Uint32 &lastMoveTime, Uint32 moveDelay,
                 int windowWidth, int windowHeight)
{
    Uint32 currentTime = SDL_GetTicks();
    if (currentTime - lastMoveTime > moveDelay)
    {
        lastMoveTime = currentTime;

        // Apply next direction from queue if available
        if (!snake.directionQueue.empty())
        {
            auto nextDir = snake.directionQueue.front();
            snake.directionQueue.pop();
            snake.dx = nextDir.first;
            snake.dy = nextDir.second;
        }

        SDL_Rect newHead = snake.body.front();
        newHead.x += snake.dx;
        newHead.y += snake.dy;

        // Keep inside bounds or wrap...

        snake.body.insert(snake.body.begin(), newHead);

        if (snake.pending_growth > 0)
        {
            snake.pending_growth--;
        }
        else
        {
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
