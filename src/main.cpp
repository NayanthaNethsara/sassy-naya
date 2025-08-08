#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "snake.h"
#include "food.h"

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int GRID_SIZE = 20;
const Uint32 MOVE_DELAY = 200;

bool initSDL(SDL_Window **window, SDL_Renderer **renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return false;
    }

    *window = SDL_CreateWindow("Snake Modular",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return false;
    }

    return true;
}

int main()
{
    srand(time(nullptr));

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!initSDL(&window, &renderer))
    {
        return 1;
    }

    Snake snake;
    initSnake(snake, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GRID_SIZE);

    Food food;
    placeFood(food, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);

    bool running = true;
    SDL_Event event;
    Uint32 lastMoveTime = SDL_GetTicks();

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;

            handleInput(event, snake);
        }

        updateSnake(snake, lastMoveTime, MOVE_DELAY, WINDOW_WIDTH, WINDOW_HEIGHT);

        if (checkFoodEaten(snake.body[0], food))
        {
            placeFood(food, WINDOW_WIDTH, WINDOW_HEIGHT, GRID_SIZE);
            growSnake(snake);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderFood(renderer, food);
        renderSnake(renderer, snake);

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
