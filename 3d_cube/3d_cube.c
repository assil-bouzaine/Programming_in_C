#include<stdio.h>
#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef struct {
  float x;
  float y;
  float z;
}Point;

Point drawPoint(Point p) 
{
  p.x =(( p.x + 1)/2.0f)*SCREEN_WIDTH;
  p.y =(1- ( p.y + 1)/2.0f)*SCREEN_HEIGHT;
  return p;

}



Point project(Point p)
{
  p.x = p.x/(float)p.z;
  p.y = p.y/(float)p.z;
  return p;
}
int main(void) 
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D-Cube", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
  SDL_Surface* surface = SDL_GetWindowSurface(window);
  Point p = {0,0,2};
  p =  project(p) ;
  p =  drawPoint(p) ;
  SDL_Rect rectangle = {p.x,p.y,20,20};
  SDL_FillRect(surface,&rectangle,0xfffff);
  SDL_UpdateWindowSurface(window);
  SDL_Delay(5000);
  return 0;
}

