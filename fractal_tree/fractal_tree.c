#include<stdio.h>
#include<math.h>
#include<raylib.h>

const int width = 800;
const int height = 600;


void DrawTree(float x , float y, float angle, float length, float thickness)
{
  Vector2 start = {x , y};
  float x_end = x + sinf(angle * DEG2RAD) * length;
  float y_end = y - cosf(angle * DEG2RAD) * length;
  Vector2 end = {x_end , y_end};
  DrawLineEx(start,end,thickness, BLACK);
  float new_length = length * 0.7; 
  float new_thickness = thickness * 0.7;
  float new_left_angle= angle + 20;
  float new_right_angle= angle - 40;
  if(new_length < 5) return;
  DrawTree(x_end, y_end,new_right_angle,new_length, new_thickness);
  DrawTree(x_end, y_end,new_left_angle,new_length, new_thickness);
}

int main()
{
  InitWindow(width,height, "Mess Around");

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTree(width/2,height-30, 0, 170, 20);
        EndDrawing();
    }

    CloseWindow();
  return 0;
}
