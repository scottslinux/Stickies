#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"

#include "Sticky.h"
#include "GlobalScale.h"



using namespace std;



    

int main()
{

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    
    InitWindow(2000,2500,"Stickies!");
    SetWindowPosition(3500,0);
    InitAudioDevice();

    int mon = GetCurrentMonitor();
    int mw  = GetMonitorWidth(mon);    // raw pixel width of that monitor
    int mh  = GetMonitorHeight(mon);   // raw pixel height of that monitor
    Vector2 dpi = GetWindowScaleDPI(); // e.g. (1.25, 1.25) for 125% scaling

    cout<<"Monitor: "<<mon<<" mw:"<<mw<<" mh:"<<mh<<" DPI:"<<dpi.x<<" "<<dpi.y<<endl;
        

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