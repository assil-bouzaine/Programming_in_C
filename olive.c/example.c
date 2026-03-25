#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "olive.c"

#define WIDTH 800
#define HEIGHT 600

#define COLS 16
#define ROWS 12
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFFF0F0F0

static uint32_t pixels[WIDTH*HEIGHT];

float lerpf(float a, float b, float t)
{
  return a + (b-a)*t;
}

bool checker_example(void)
{
  const char* file_path = "checker.ppm";
  olivec_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
  
  for(int y = 0; y < ROWS; y++)
  {
    for(int x = 0; x < COLS; x++)
    {
      uint32_t color = BACKGROUND_COLOR;
      if((x+y) % 2 == 0)
        color = 0xFFFFFFFF;

      olivec_fill_rect(pixels,WIDTH,HEIGHT,x*CELL_WIDTH,y*CELL_HEIGHT,CELL_WIDTH,CELL_HEIGHT,color);
    }
  }


  Errno err = olivec_save_to_ppm(pixels,WIDTH,HEIGHT,file_path);
  if(err)
  {
    fprintf(stderr, "could not save the file %s : %s \n", file_path, strerror(errno));
    return false;
  }
  return true;
}

bool circle_example(void)
{
  const char* file_path = "circle.ppm";
  olivec_fill(pixels,WIDTH,HEIGHT,BACKGROUND_COLOR);
  for(int y = 0; y < ROWS; y++)
  {
    for(int x = 0; x < COLS; x++)
    {
      float u = (float) x/COLS;
      float v = (float) y/ROWS;
      float t = (u + v)/2;
      size_t radius = CELL_WIDTH;
      if(CELL_HEIGHT < radius) radius = CELL_HEIGHT;
      olivec_fill_circle(pixels, WIDTH, HEIGHT, x*CELL_WIDTH + CELL_WIDTH/2,
          y*CELL_HEIGHT + CELL_HEIGHT/2, lerpf(radius/8, radius/2, t),
          FOREGROUND_COLOR);
    }
  }


  Errno err = olivec_save_to_ppm(pixels,WIDTH,HEIGHT,file_path);
  if(err)
  {
    fprintf(stderr, "could not save the file %s : %s \n", file_path, strerror(errno));
    return false;
  }

  return true;
}

//main function
int main(void)
{
  if(!checker_example()) return -1;
  if(!circle_example()) return -1;
  return 0;
}

