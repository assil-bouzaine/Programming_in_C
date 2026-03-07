#include<stdio.h>
#include<math.h>
#include<SDL2/SDL.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60

typedef struct {
  float x;
  float y;
  float z;
}Point;

void transform(Point* p)
{
  p->x = ((p->x + 1 )/2 ) * SCREEN_WIDTH -10;
  p->y = (1- ((p->y + 1 )/2) ) * SCREEN_HEIGHT -10;
}

void project(Point *p)
{
  p->x = p->x / p->z;
  p->y = p->y / p->z;
}

void rotateY(Point* p, float angle)
{
  float newX = p->x*cosf(angle) + p->z*sinf(angle);
  float newZ = -(p->x*sinf(angle)) + p->z*cosf(angle);
  p->x = newX;
  p->z = newZ;
}

void cameraOffset(Point* p, float distance)
{
  p->z = p->z + distance;
}


void drawPoint(SDL_Renderer* renderer,Point* p)
{
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_FRect rect = {p->x,p->y,10,10};
  SDL_RenderFillRectF(renderer,&rect);
}

int main(void) 
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D-Cube", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Point points[] = {
    //front
    {0.25,0.25,0.25},
    {0.25,-0.25,0.25},
    {-0.25,0.25,0.25},
    {-0.25,-0.25,0.25},
    //back
    {0.25,0.25,-0.25},
    {0.25,-0.25,-0.25},
    {-0.25,0.25,-0.25},
    {-0.25,-0.25,-0.25},
  };
  SDL_Event event;
  int num_points = sizeof(points)/sizeof(points[0]);
  int running = 1;
  float distance = 1.0f;
  float angle = 0.0f;

  while(running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT) running = 0;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for(int i=0; i < num_points; i++)
    {
      Point p = points[i];
      rotateY(&p,angle);
      cameraOffset(&p, distance);
      project(&p);
      transform(&p);
      drawPoint(renderer , &p);
    }
    // angle should change after each loop
    angle += 0.02f; 


    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FPS);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
