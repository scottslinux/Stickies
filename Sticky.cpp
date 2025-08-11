#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"
#include "Sticky.h"

using namespace std;

RenderTexture2D Sticky::stickRnder{};  //completing the definition of static rendertexture

//=========================================

Sticky::Sticky():menuonff({900,10},0.1),Changes(),msgbox(15,8,70,{200,1800}),
    savenote({550,1800},0.1)
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
    {
        menuflag=true;
        
    }

    
        if (menuflag && !submenuflag)
            {   
                
                DrawText("Menu On",700,800,50,WHITE);
                if(menuonff.update())
                    menuflag=false;
                vector<string> choices={"Add New Note","Edit Existing Note","Exit Notes"};
                
                
                int choice=Changes.displayMenu(choices,{400,2000},60);
                        

                switch (choice)
                {
                case 1:
                    submenuflag=true;  //allows opening note editor
                    menuflag=false;
                    cout<<"choice 1....\n";
                    cout<<"menuflag: "<<menuflag<<endl;
                    break;
                case 2:
                    cout<<"choice 2....\n";
                
                default:
                    break;
                }

                
            }

        
            if(submenuflag)
                {   
                    msgbox.Update();
                    msgbox.Draw();
                    bool save=savenote.update();
                    savenote.draw();
                    DrawTextEx(marker,"Save Note",{620,1800},60,0,WHITE);

                    if (save)  
                        {
                            submenuflag=false;
                            menuflag=false;
                            menuonff.value=false;   //reset both buttons
                            savenote.value=false;
                            cout<<"time to create the actual note.....!!!!\nbut first its bedtime....";
                            //call the routine to capture the note into a rendertexture and 
                            //commit to the vector
                        }
                }


}




//=========================================
void Sticky::display()
{
    
    float scale=0.6;    //Image scale factor

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

    if (menuflag)
        {
            
            
        }

    return;
}
//==========================================

void Sticky::createNote()
{
    string newNotetext;
    cin>>newNotetext;

    cout<<newNotetext<<endl;


    
}