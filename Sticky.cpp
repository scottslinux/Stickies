#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"
#include "Sticky.h"

using namespace std;

RenderTexture2D Sticky::stickRnder{};  //completing the definition of static rendertexture

//=========================================

Sticky::Sticky():menuonff({700,800},0.1)
{
    stickypic=LoadTexture("./resources/stickypic.png");
    marker=LoadFontEx("./resources/marker.ttf",100,0,0);
    stickRnder=LoadRenderTexture(500,500);  //initialize the rendertexture









}
//=========================================
Sticky::~Sticky()
{
    UnloadFont(marker);
    UnloadTexture(stickypic);
    UnloadRenderTexture(stickRnder);

    marker={};
    stickypic={};





}
//=========================================
void Sticky::update()
{
    
    
    if (menuonff.update()&&!menuflag)
        menuflag=true;
    

    
        if (menuflag)
            {
                DrawText("Menu On",400,400,50,WHITE);
                if(menuonff.update())
                    menuflag=false;
            }




}




//=========================================
void Sticky::display()
{
    
    float scale=0.6;

    BeginTextureMode(stickRnder);
        //draw to the rendertexture
        DrawTextureEx(stickypic,{0,0},0,scale,WHITE);
        DrawTextEx(marker,"DEA License\nRenew Sept.",{35,100},60,0,BLACK);

    EndTextureMode();

    Vector2 origin={stickRnder.texture.width*scale/2,stickRnder.texture.height*scale/2};
    Rectangle source={0,0,stickRnder.texture.width,-1*stickRnder.texture.height};
    Rectangle dest={200,200,stickRnder.texture.width,stickRnder.texture.height};
    
    //cout<<"Origin = "<<origin.x<<", "<<origin.y<<endl;

    DrawTexturePro(stickRnder.texture,source,dest,{100,100},15,Color{255,255,255,255});

    menuonff.draw();

    return;
}
//==========================================

void Sticky::createNote()
{
    string newNotetext;
    cin>>newNotetext;

    cout<<newNotetext<<endl;


    
}