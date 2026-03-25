#ifndef OLIVE_H
#define OLIVE_H


#define return_defer(value) do {result = value ; goto defer;} while(0)
typedef int Errno;

void olivec_fill(uint32_t *pixels, size_t width, size_t height , uint32_t color)
{
  for(size_t i = 0; i < width * height; i++)
  {
    pixels[i] = color;
  }
}


Errno olivec_save_to_ppm(uint32_t *pixels,size_t width,size_t height,const char* path)
{
  int result = 0;
  FILE* f = NULL;

  {
    f = fopen(path, "wb");
    if(f == NULL) return_defer(errno);

    fprintf(f, "P6\n%zu %zu\n255\n", width, height);
    if(ferror(f)) return_defer(errno);


    for(size_t i = 0; i < width * height; i++)
    {
      uint32_t pixel = pixels[i];
      uint8_t bytes[3] = {
        (pixel >> 16) & 0xFF,  // R
        (pixel >> 8)  & 0xFF,  // G
        (pixel >> 0)  & 0xFF,  // B
      };
      fwrite(bytes, sizeof(bytes), 1, f);
      if(ferror(f)) return_defer(errno);
    }
  } 

defer:
  if(f) fclose(f);
  return result;

}


void olivec_fill_rect(uint32_t *pixels, size_t width, size_t height,
                      int pos_x , int pos_y , size_t w, size_t h, uint32_t color)
{
  for(int dy = 0; dy < (int)h; dy++)
  {
    int y = pos_y + (int)dy;
    if(y >= 0 && y < (int)height)
    {
      for(int dx = 0; dx < (int)w; dx++)
      {
        int x = pos_x + (int)dx;
        if(x >= 0 && x < (int)width)
          pixels[y * width + x] = color;
      }  
    }  
  }
}


void olivec_fill_circle(uint32_t *pixels, size_t width, size_t height, int pos_x, int pos_y,
                    int r, uint32_t color)
{
int x1 = pos_x - r;
int y1 = pos_y - r;

int x2 = pos_x + r;
int y2 = pos_y + r;

for(int y = y1; y <= y2; y++)
{
if(y >= 0 && y < (int)height)
{
  for(int x = x1; x <= x2; x++)
  {
    if(x >= 0 && x <(int) width)
    {
      int dx = x - pos_x;
      int dy = y - pos_y;
      if(dx*dx + dy*dy <= r*r)
        pixels[y * width + x] = color;
    }
  }
}
}
}

#endif // OLIVE_H
