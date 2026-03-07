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

void rotateY(Point* p, float* angle)
{
  p->x = p->x*cosf(*angle) + p->z*sinf(*angle);
  p->z = -(p->x*sinf(*angle)) + p->z*cosf(*angle);
}



void frame(Point *p, float *dz, float* angle)
{
  float dt = 1.0f/FPS;
  rotateY(p,angle);
  *dz += 0.1f*dt;
  p->z += *dz;
  project(p);
  transform(p);
}



int main(void) 
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D-Cube", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Point cube_points[] = {
    //front
    {0.5,0.5,0.5},
    {0.5,-0.5,0.5},
    {-0.5,0.5,0.5},
    {-0.5,-0.5,0.5},
    //back
    {0.5,0.5,-0.5},
    {0.5,-0.5,-0.5},
    {-0.5,0.5,-0.5},
    {-0.5,-0.5,-0.5},
  };
  int num_points = sizeof(cube_points)/sizeof(cube_points[0]);
  int running = 1;
  SDL_Event event;
  float dz = 1.0f;
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
      Point p = cube_points[i];
      frame(&p, &dz, &angle);
      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
      SDL_FRect rect = {p.x,p.y,10,10};
      SDL_RenderFillRectF(renderer,&rect);
    }
    angle += 0.02f; 
    SDL_RenderPresent(renderer);
    SDL_Delay(1000/FPS);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
