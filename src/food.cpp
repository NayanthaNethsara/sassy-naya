#include "food.h"
#include <cstdlib>
#include <ctime>

void placeFood(Food &food, int windowWidth, int windowHeight, int gridSize)
{
    int maxX = (windowWidth / gridSize) - 1;
    int maxY = (windowHeight / gridSize) - 1;
    food.rect.x = (rand() % maxX) * gridSize;
    food.rect.y = (rand() % maxY) * gridSize;
    food.rect.w = gridSize;
    food.rect.h = gridSize;
}

void renderFood(SDL_Renderer *renderer, const Food &food)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &food.rect);
}

bool checkFoodEaten(const SDL_Rect &snakeHead, const Food &food)
{
    return SDL_HasIntersection(&snakeHead, &food.rect);
}
