#ifndef FOOD_H
#define FOOD_H

#include <SDL2/SDL.h>

struct Food
{
    SDL_Rect rect;
};

void placeFood(Food &food, int windowWidth, int windowHeight, int gridSize);
void renderFood(SDL_Renderer *renderer, const Food &food);
bool checkFoodEaten(const SDL_Rect &snakeHead, const Food &food);

#endif // FOOD_H
