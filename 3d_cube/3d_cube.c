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

void rotateZ(Point* p, float angle)
{
  float newX = p->x*cosf(angle) - p->y*sinf(angle);
  float newY = (p->x*sinf(angle)) + p->y*cosf(angle);
  p->x = newX;
  p->y = newY;
}


void rotateX(Point* p, float angle)
{
  float newY = p->y*cosf(angle) - p->z*sinf(angle);
  float newZ = (p->y*sinf(angle)) + p->z*cosf(angle);
  p->y = newY;
  p->z = newZ;
}
void cameraOffsetZ(Point* p, float offsetZ)
{
  p->z = p->z + offsetZ;
}

void cameraOffsetX(Point* p, float offsetX)
{
  p->x = p->x + offsetX;
}

void cameraOffsetY(Point* p, float offsetY)
{
  p->y = p->y + offsetY;
}

void drawPoint(SDL_Renderer* renderer,Point* p)
{
  SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
  SDL_FRect rect = {p->x,p->y,10,10};
  SDL_RenderFillRectF(renderer,&rect);
}


void drawCube(SDL_Renderer* renderer, Point* p,int edges[][2], int num_points,int num_edges, float angle, float offsetX, float offsetY, float offsetZ)
{
    Point transformed_points[num_points];

    for(int i=0; i < num_points; i++)
    {
      Point new_points = p[i];
      rotateY(&new_points,angle);
      rotateX(&new_points,angle);
      rotateZ(&new_points,angle);
      cameraOffsetZ(&new_points, offsetZ);
      cameraOffsetY(&new_points, offsetY);
      cameraOffsetX(&new_points, offsetX);
      project(&new_points);
      transform(&new_points);
     // drawPoint(renderer , &new_points);
      transformed_points[i] = new_points;
    }


    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for(int i=0; i < num_edges; i++)
    {
      Point a = transformed_points[edges[i][0]];
      Point b = transformed_points[edges[i][1]];
      SDL_RenderDrawLineF(renderer,a.x,a.y,b.x,b.y);
    }

}

int main(void) 
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("3D-Cube", SDL_WINDOWPOS_CENTERED ,SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,SCREEN_HEIGHT,0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  Point points[] = {
    //front
    {0.11,0.11,0.11},
    {0.11,-0.11,0.11},
    {-0.11,-0.11,0.11},
    {-0.11,0.11,0.11},
    //back
    {0.11,0.11,-0.11},
    {0.11,-0.11,-0.11},
    {-0.11,-0.11,-0.11},
    {-0.11,0.11,-0.11},
  };

  int edges[][2]= {
    {0,1},
    {1,2},
    {2,3},
    {3,0},
    {4,5},
    {5,6},
    {6,7},
    {7,4},
    {0,4},
    {1,5},
    {2,6},
    {3,7},
  };
  SDL_Event event;
  int num_points = sizeof(points)/sizeof(points[0]);
  int num_edges = sizeof(edges)/sizeof(edges[0]);
  int running = 1;
  float angle = 0.0f;

  while(running)
  {
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT) running = 0;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    for(float i=0.25; i < 1.0f; i+=0.25)
    {
      float sign = 1.0f;
      for(int j=0; j < 2; j++)
      {
        drawCube(renderer,points,edges,num_points,num_edges,angle,i*sign,i*sign,1.0f);
        sign *= -1.0f;
      }
      sign = 1.0f;
      for(int j=0; j < 2; j++)
      {
        drawCube(renderer,points,edges,num_points,num_edges,angle,-i*sign,i*sign,1.0f);
        sign *= -1.0f;
      }
    }
    drawCube(renderer,points,edges,num_points,num_edges,angle,0.0f,0.0f,1.0f);

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
