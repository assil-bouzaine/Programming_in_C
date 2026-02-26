#include<time.h>
#include<math.h>
#include<stdio.h>
#include<raylib.h>


// Global Variables
const int g_width = 600;
const int g_height = 600;
float circleRadius = g_height * 0.4f;
const float xCenter = g_width/2;
const float yCenter = g_height/2;
Vector2 center = {xCenter,yCenter};




void DrawMinuteMarker() 
{
  float alpha = 0;
  for (size_t i=0; i<60; i++)
  {
    float x_inner = center.x +  circleRadius*0.9* sinf(alpha*DEG2RAD);
    float y_inner =  center.y + circleRadius*0.9* cosf(alpha*DEG2RAD);
    Vector2 inner = {x_inner, y_inner};
    float x_outer = center.x +  circleRadius*0.98* sinf(alpha*DEG2RAD);
    float y_outer =  center.y + circleRadius*0.98* cosf(alpha*DEG2RAD);
    Vector2 outer = {x_outer, y_outer};
    alpha += 360 / 60;
    DrawLineEx(inner, outer, 3, BLACK);
  }
}




int main(){

  // get the local time
  time_t now = time(NULL);
  char *str_now = ctime(&now);
  printf("%s \n", str_now);


  //init windows
  InitWindow(g_width, g_height, "Clock");
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(center,circleRadius,RAYWHITE); 
            DrawMinuteMarker();
        EndDrawing();
    }

    CloseWindow();
  return 0;

}
