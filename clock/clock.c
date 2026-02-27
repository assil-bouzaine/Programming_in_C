#include<time.h>
#include<math.h>
#include<stdio.h>
#include<raylib.h>


// Global Variables
const int g_width = 600;
const int g_height = 600;
const float circleRadius = g_height * 0.4f;
const float xCenter = g_width/2;
const float yCenter = g_height/2;
Vector2 center = {xCenter,yCenter};
const float secondHandLen = circleRadius * 0.8;
const float minHandLen = circleRadius * 0.7;
const float hourHandLen = circleRadius * 0.5;

void DrawHand(float length,  float thickness, int time, float fraction, int format, Color color)
{
  float angle = (float)(time % format)* fraction;
  float x_end = xCenter + sinf(angle * DEG2RAD) * length;

  float y_end = yCenter - cosf(angle * DEG2RAD)* length;
  Vector2 end = {x_end, y_end};
  DrawLineEx(center, end, thickness, color );
}


void DrawMinuteMarker() 
{
  float alpha = 0;
  for (size_t i=0; i<60; i++)
  {
    float x_inner = center.x +  circleRadius*(0.98 - (i % 5 == 0 ? 0.12 : 0.08))* sinf(alpha*DEG2RAD);
    float y_inner =  center.y + circleRadius*(0.98 - (i % 5 == 0 ? 0.12 : 0.08))* cosf(alpha*DEG2RAD);
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
  struct tm *tm_local= localtime(&now);
  printf("%d hour now \n", tm_local->tm_hour);
  printf("%d min now \n", tm_local->tm_min);
  printf("%d sec now \n", tm_local->tm_sec);


  //init windows
  InitWindow(g_width, g_height, "Clock");
    while (!WindowShouldClose())
    {
        now = time(NULL);
        tm_local = localtime(&now);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawCircleV(center,circleRadius,WHITE); 
            DrawMinuteMarker();
            DrawCircle(xCenter, yCenter, 5, BLACK);
            DrawHand(hourHandLen,  10, tm_local->tm_hour, 30, 12, BLACK);
            DrawHand(minHandLen,  8, tm_local->tm_min, 6, 60, BLACK);
            DrawHand(secondHandLen,  3, tm_local->tm_sec, 6, 60, RED);
        EndDrawing();
    }

    CloseWindow();
  return 0;

}
