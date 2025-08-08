#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake Head Move",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Snake head position and size
    SDL_Rect snakeHead = {400, 300, 20, 20}; // x, y, w, h
    int speed = 5;                           // pixels per frame

    bool running = true;
    SDL_Event event;

    // Movement direction
    int dx = 0, dy = 0;

    while (running)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
            else if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    dx = 0;
                    dy = -speed;
                    break;
                case SDLK_DOWN:
                    dx = 0;
                    dy = speed;
                    break;
                case SDLK_LEFT:
                    dx = -speed;
                    dy = 0;
                    break;
                case SDLK_RIGHT:
                    dx = speed;
                    dy = 0;
                    break;
                }
            }
        }

        // Update snake head position
        snakeHead.x += dx;
        snakeHead.y += dy;

        // Keep snake inside window boundaries
        if (snakeHead.x < 0)
            snakeHead.x = 0;
        if (snakeHead.y < 0)
            snakeHead.y = 0;
        if (snakeHead.x > 800 - snakeHead.w)
            snakeHead.x = 800 - snakeHead.w;
        if (snakeHead.y > 600 - snakeHead.h)
            snakeHead.y = 600 - snakeHead.h;

        // Clear screen with black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw snake head in green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &snakeHead);

        // Show what we drew
        SDL_RenderPresent(renderer);

        // Simple frame delay (~60 FPS)
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
