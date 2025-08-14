#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"

#include "Sticky.h"


using namespace std;



    

int main()
{

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
   SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    InitWindow(1000,2500,"Stickies!");
    SetWindowPosition(4400,0);
    InitAudioDevice();
     

    SetTargetFPS(60);
    Sticky notepad;

    while(!WindowShouldClose())
    {

      BeginDrawing();
          ClearBackground(Color{0,0,0,0});   //clear the screen
          notepad.update();
          notepad.draw();


      EndDrawing();




    }
    CloseAudioDevice();
    return 0;
    
}