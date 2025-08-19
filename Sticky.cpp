#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "raylib.h"
#include "Sticky.h"
#include "GlobalScale.h"

using namespace std;

RenderTexture2D Sticky::stickRnder{};  //completing the definition of static rendertexture

//=========================================

Sticky::Sticky():menuonff({GetScreenWidth()*0.8,GetScreenHeight()*0.05},0.1),Changes(),msgbox(15,8,70,{GetScreenWidth()*0.7,GetScreenHeight()*0.65}),
    savenote({GetScreenWidth()*0.7,GetScreenHeight()*0.78},0.1),scaler({GetScreenWidth()*0.68,GetScreenHeight()*0.82},0.4,5,5,15)
{
    stickypic=LoadTexture("./resources/stickypic.png");
    marker=LoadFontEx("./resources/marker.ttf",100,0,0);
    titles=LoadFontEx("./resources/Inter.ttf",80,0,0);

    stickRnder=LoadRenderTexture(500,500);  //initialize  the rendertexture


    currstate=states::displaying;   // set the initial state- eventually will be intro

    //check and see if notes already exist....
    
    if (filesystem::exists("./resources/StickyConfig.txt"))
    {
        cout<<"There are existing notes....loading them\n";

        LoadStickiesfromFile();


    }
    
    //Globalscale=7* 0.1; //reasonable initial value for the global scale

    if (Globalscale==1.0)
        Globalscale=7*0.1;  






}
//=========================================
Sticky::~Sticky()
{
    //before shutting down write to disk
    FiletoDisk();

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
    menuonff.update();

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
    scaler.update();    //expose scaling slider


    msgbox.Update();    //update the text box over the note
    if(savenote.update())  //update the save note button 
        {   //save note button pressed
            menuonff.value=false;   //set both buttons to off
            savenote.value=false;
            save2Vectors();         //save the image to the vector

            //save the Stickylist vector to disk

            FiletoDisk();

            currstate=states::displaying; //change state

            

        }
    
   

    
}
//==========================================

void Sticky::create_draw()
{
    DrawTextEx(titles,"    Create\n  Your New\n Sticky Note",{GetScreenWidth()*.70,GetScreenHeight()*0.90},75,0,GREEN);
    savenote.draw();
    DrawTextEx(marker,"SAVE",{GetScreenWidth()*0.72,GetScreenHeight()*0.83},50,0,WHITE);
    msgbox.Draw();

    scaler.draw();
    displaying_draw();

    Rectangle border={GetScreenWidth()*.65,GetScreenHeight()*0.62,GetScreenWidth()*0.25,GetScreenHeight()*0.28};
    DrawRectangleLinesEx(border,10,YELLOW);

    
        

    
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
        //  Mouse Dragging the Note into position
        if(CheckCollisionPointRec(mousepos,note.noterect)&&mousebuttondown)
        {
            DrawRectangleLinesEx(note.noterect,4,GREEN);
            note.notepos={GetMousePosition().x-150,GetMousePosition().y-150};
            note.noterect={note.notepos.x,note.notepos.y,notepics[index].texture.width*0.6,
                        notepics[index].texture.height*0.6};

            DrawRectanglePro({0,0,GetScreenWidth(),GetScreenHeight()},{0,0},0,Color{0,150,150,100});

            break;
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

            //Adjust note size with Globalscale adjusting dest rect
            Rectangle destin={StickyList[i].notepos.x,StickyList[i].notepos.y,
                            picimg.texture.width*Globalscale, picimg.texture.height*Globalscale};



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
//========================================================================
void Sticky::FiletoDisk()
{
    string path="./resources/StickyConfig.txt";

    ofstream outfile(path);   //open or create the file (overwrite)
        if(outfile.is_open())
            cout<<"file opened successfully for write operation.\n";
            else
                cout<<"FAILED TO OPEN FILE FOR WRITE!!!\n";

    outfile<<Globalscale<<"\n";     //first item in the dump is the global scale...will load first

    // Again...a little help from my friend
    for(const auto& stick:StickyList)
    {
        outfile
            << stick.completed << ' '
            << stick.notepos.x << ' ' << stick.notepos.y << ' '
            << stick.noterect.x << ' ' << stick.noterect.y << ' '
            << stick.noterect.width << ' ' << stick.noterect.height << ' '
            << int(stick.notetint.r) << ' ' << int(stick.notetint.g) << ' '
            << int(stick.notetint.b) << ' ' << int(stick.notetint.a) << ' '
            << stick.rotation << ' '
            << std::quoted(stick.task)   // preserves spaces/quotes in the task
            << '\n';


    }

    outfile.close();

    return;

    




}
//========================================================================
void Sticky::LoadStickiesfromFile()
{
    const std::string path = "./resources/StickyConfig.txt";
    std::ifstream infile(path);
    if (!infile) { std::cerr << "FAILED TO OPEN FILE FOR READ!!!\n"; return; }

    StickyList.clear();
    notedata stick;
    int r,g,b,a;

    infile>>Globalscale;

    while (infile
        >> stick.completed
        >> stick.notepos.x >> stick.notepos.y
        >> stick.noterect.x >> stick.noterect.y
        >> stick.noterect.width >> stick.noterect.height
        >> r >> g >> b >> a
        >> stick.rotation
        >> std::quoted(stick.task))
    {
        stick.notetint = { (unsigned char)r, (unsigned char)g, (unsigned char)b, (unsigned char)a };
        StickyList.push_back(stick);
    }


    //create the images from the retrieved data

    notepics.clear();       //clear out the notepics vector

    int i=0;

    for(const auto& s:StickyList)
    {
        notepics.push_back(LoadRenderTexture(500,500));

        BeginTextureMode(notepics.back());

            
            DrawTextureEx(stickypic,{0,0},0,0.6,s.notetint);
            DrawTextEx(marker,s.task.c_str(),{50,0},70,0,BLACK);


        EndTextureMode();

        i++;


    }

}