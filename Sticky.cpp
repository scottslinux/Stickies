#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include "raylib.h"
#include "Sticky.h"

using namespace std;

RenderTexture2D Sticky::stickRnder{};  //completing the definition of static rendertexture

//=========================================

Sticky::Sticky():menuonff({1500,10},0.1),Changes(),msgbox(15,8,70,{200,1800}),
    savenote({700,2000},0.1)
{
    stickypic=LoadTexture("./resources/stickypic.png");
    marker=LoadFontEx("./resources/marker.ttf",100,0,0);
    titles=LoadFontEx("./resources/Inter.ttf",80,0,0);

    stickRnder=LoadRenderTexture(500,500);  //initialize  the rendertexture


    currstate=states::displaying;   // set the initial state- eventually will be intro

    //notepics.push_back(LoadRenderTexture(500,500));  //create a sample rndrtex in vector
    //same width and height as stickRnder
    

    
    






}
//=========================================
Sticky::~Sticky()
{
    UnloadFont(marker);
    UnloadFont(titles);
    UnloadTexture(stickypic);
    UnloadRenderTexture(stickRnder);


    marker={};
    stickypic={};





}
//=========================================
void Sticky::update()
{
    //      ⁡⁣⁢⁣​‌‍‌SWITCHBOARD​⁡
    switch (currstate)
    {
            case states::intro :intro_update();
                                break;
            case states::create :create_update();
                                break;
            case states::displaying :displaying_update();
                                break;
            case states::dispose :dispose_update();
                                break;
            default:
                break;
    }

    if (menuonff.update())      //respond to button on
        currstate=states::create;
    if (!menuonff.update() && currstate!=states::dispose)     //when off return to display state
        currstate=states::displaying;

   // cout<<"Current state is: "<<statesetring[static_cast<size_t>(currstate)]<<endl;

}




//=========================================
void Sticky::draw()
{
    switch (currstate)
    {
            case states::intro :intro_draw();
                                break;
            case states::create :create_draw();
                                break;
            case states::displaying :displaying_draw();
                                break;
            case states::dispose :dispose_draw();
                                break;
            default:
                break;
    }


    float scale=0.6;    //Image scale factor


    menuonff.draw();
    

    return;
}

//==========================================

void Sticky::create_update()
{
    
    msgbox.Update();    //update the text box over the note
    if(savenote.update())  //update the save note button 
        {   //save note button pressed
            menuonff.value=false;   //set both buttons to off
            savenote.value=false;
            save2Vectors();         //save the image to the vector

            currstate=states::displaying; //change state

            

        }
    
   

    
}
//==========================================

void Sticky::create_draw()
{
    DrawTextEx(titles,"Create Your New Sticky Note",{0,2200},80,0,GREEN);
    savenote.draw();
    DrawTextEx(marker,"SAVE",{800,2000},50,0,GREEN);
    msgbox.Draw();

    displaying_draw();

    
        

    
}

//==========================================

void Sticky::intro_update()
{


}
//==========================================
void Sticky::intro_draw()
{


}
//==========================================
void Sticky::displaying_update()
{
    //checking for movement and rotation
    int index=0;
    bool mousebuttondown=(IsMouseButtonDown(MOUSE_BUTTON_LEFT));

    Vector2 mousepos=GetMousePosition();

    
                
    for(auto& note:StickyList)
    {
        //  Mouse Dragging the Note into position
        if(CheckCollisionPointRec(mousepos,note.noterect)&&mousebuttondown)
        {
            DrawRectangleLinesEx(note.noterect,4,GREEN);
            note.notepos={GetMousePosition().x-150,GetMousePosition().y-150};
            note.noterect={note.notepos.x,note.notepos.y,notepics[index].texture.width*0.6,
                        notepics[index].texture.height*0.6};

            DrawRectanglePro({0,0,GetScreenWidth(),GetScreenHeight()},{0,0},0,Color{0,150,150,100});
        }


        // Mouse Wheel Rotation of the note
        if(CheckCollisionPointRec(mousepos,note.noterect)&&GetMouseWheelMove())
        {
            note.rotation+=GetMouseWheelMove()*2;
        }

        
        //check for double click-->destroy
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mousepos,note.noterect)) 
        {
            double now=GetTime();
            if(now-lastclick<= doubleclicktime)
            {
                cout<<"DOUBLE CLICK on note "<<index<<endl;
                dyingnote=index;    //index of note to dispose of
                currstate=states::dispose;
            }
                else   
                {
                    lastclick=now;
                    
                }
        }






        index++;
    }
}
//==========================================
void Sticky::displaying_draw()
{
    int i=0; //index
   
    if (notepics.size()!=0) //if not empty iterate the vectors and draw notes
    
    {
        for (auto picimg:notepics )
        {
            Rectangle source={0,0,picimg.texture.width,picimg.texture.height*-1};
            Rectangle destin={StickyList[i].notepos.x,StickyList[i].notepos.y,
                            picimg.texture.width, picimg.texture.height};
            float rotation=StickyList[i].rotation;
            Vector2 orig={picimg.texture.width,stickypic.height};

            DrawTexturePro(picimg.texture,source,destin,{0,0},rotation,WHITE);
            
        

            i++;  //forgot to increment the index--->idiot!
        }
    
    }
}

//==========================================
void Sticky::dispose_update()
{
    fallingtimer+=GetFrameTime();
    if(fallingtimer>0.02)
    {
        //drop at pixels/sec * frame time
        StickyList[dyingnote].notepos.y+=1500*GetFrameTime();
        StickyList[dyingnote].notepos.x+=(StickyList[dyingnote].notepos.y/60)*sin(StickyList[dyingnote].notepos.y/200);
        fallingtimer=0;
        StickyList[dyingnote].rotation+=sin(StickyList[dyingnote].notepos.y/300);


        if (StickyList[dyingnote].notepos.y>GetScreenHeight())
        {
            //erase the element at beginning + index  for both vectors
            StickyList.erase(StickyList.begin()+dyingnote);
            notepics.erase(notepics.begin()+dyingnote);

            


            currstate=states::displaying;



        }
    }

}
//==========================================
void Sticky::dispose_draw()
{
    
    displaying_draw();      //continue to display all notes while conducting animation
}
//==========================================
// the note is finished add the image and info to vectors
void Sticky::save2Vectors()
{
    // create a new entry in the pics vector
    notepics.push_back(LoadRenderTexture(500,500)); 

    //create entry in the note ledger
    notedata newentry;
        newentry.completed=true;
        newentry.notepos={rand()%600,rand()%1200};  //PICK RANDOM SPOT ON SCREEN
        newentry.noterect={newentry.notepos.x,newentry.notepos.y,500*.6,500*.6};
        newentry.rotation=static_cast<float>(rand()%25);
        newentry.task=msgbox.GetString();
        newentry.notetint=msgbox.getColor();

    cout<<"Rotation: "<<newentry.rotation<<endl;

    StickyList.emplace_back(newentry);


    BeginTextureMode(notepics.back());

        DrawTextureEx(stickypic,{0,0},0,0.6,msgbox.getColor());
        DrawTextEx(marker,msgbox.GetString().c_str(),{50,0},70,0,BLACK);
        

    EndTextureMode();

    msgbox.resetBox();  //reset for the next note

    cout<<"number of elements in notepics: "<<notepics.size()<<endl;
    cout<<"number of elements in Stickylist: "<<StickyList.size()<<endl;

    
    






}
