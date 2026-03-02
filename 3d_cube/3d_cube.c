#include<stdio.h>
#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



int main(void) 
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D-Cube", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
  SDL_Surface* surface = SDL_GetWindowSurface(window);
//  SDL_Rect rectangle = {100,100,200,400};
 // SDL_FillRect(surface,&rectangle,0xfffff);
  DrawPoint(surface);
  SDL_UpdateWindowSurface(window);
  SDL_Delay(5000);
  return 0;
}

