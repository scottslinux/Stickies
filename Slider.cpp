#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>
#include "Slider.h"
#include "GlobalScale.h"

using namespace std;

Texture2D Slider::plate_on{0};
Texture2D Slider::plate_off{0};
Texture2D Slider::knob{0};


//Sound Slider::slide{0};
Font Slider::pencil{0};
bool Slider::resourceguard{false};
int Slider::resourcecounter{0};



//**************************************************** */

Slider::Slider(Vector2 loc, float sliderscale,int detnts,int minim,int maxi)
{
    if(!resourceguard)  //only load resources once for class
    {
        plate_on=LoadTexture("./resources/plate_on.png");
        plate_off=LoadTexture("./resources/plate_off.png");
        knob=LoadTexture("./resources/knob.png");
        
        pencil=LoadFontEx("./resources/Inter.ttf",100,0,0);

        resourceguard=true; //lock it up!

    }
    //initialize all of the instance specific variables
    location=loc;
    scale=sliderscale;
    min=minim;
    max=maxi;
    detents=detnts;

    x1=location.x+73*scale; //this is the start of the slider @100%-->73 pixes from left
    x2=location.x+840*scale; //the slide ends at 840 pixels @ 100% --scaling down
    slidelength=x2-x1;
    slidepoint=x1;

    cout<<"slidept: "<<slidepoint<<" X1: "<<x1<<endl;

    knobrect=Rectangle{location.x,location.y,knob.width*scale,
            knob.height*scale};
    
    resourcecounter++;


}

//**************************************************** */

Slider::~Slider()
{
    
    unloadResources();



}

//**************************************************** */
void Slider::unloadResources()
{
    resourcecounter--;
    cout<<"Trying to unload...resourcecounter: "<<resourcecounter<<endl;

    //check to see if the resource actually exists before the Unload
    if (resourcecounter==0)
    {
        if (plate_off.id != 0) {
            UnloadTexture(plate_off);
            plate_off = Texture2D{};
        }

        if (plate_on.id != 0) {
            UnloadTexture(plate_on);
            plate_on = Texture2D{};
        }

        if (knob.id != 0) {
            UnloadTexture(knob);
            knob = Texture2D{};
        }

        if (pencil.texture.id != 0) {
            UnloadFont(pencil);
            pencil = Font{};
        }
    }
    
    

    return;
}
//**************************************************** */
int Slider::update()
{   //the 0.8 is to shrink the rectangle around the knob image
    //knobrect={location.x,location.y,knob.width*scale*.8,knob.height*scale*.8};

    
    if(CheckCollisionPointCircle(GetMousePosition(),{slidepoint,location.y+plate_off.height*scale/2},
                            60) && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        float normalized=GetMousePosition().x; //some point between x1-20 and x2+20

        //add buffer to both sides
        if((normalized>=x1-20) && normalized<=x2+20)
        {
             

            if (normalized<x1) normalized=x1; //stop on the left
             

            if (normalized>x2) normalized=x2;//stop on the right
            
            
            slidepoint=normalized; //normalized is between x1 and x2 so assign it

            percentage=(slidepoint-x1)/slidelength;

            if (percentage<0.0) percentage=0;  //clamp to end floating point error
            value=(int)max*percentage;

            ismoving=true;


            Globalscale=(float)value*0.1;

            cout<<"Globalscale= "<<Globalscale<<endl;
            return value;
            

        }
    }
    else
        if (CheckCollisionPointRec(GetMousePosition(),{location.x,location.y,plate_on.width*scale,
                            plate_on.height*scale}) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                float normalized=GetMousePosition().x;
                
                if(normalized>=x1 && normalized<=x2)
                    slidepoint=normalized;

                percentage=(slidepoint-x1)/slidelength;
                if (percentage<0.0) percentage=0;  //clamp to end floating point error

                value=(int)max*percentage;

            

                


            }
            
    Globalscale=(float)value*0.1;

    return value;
}
//**************************************************** */
void Slider::draw()
{
    Color light;
    if(!ismoving)
         light={150,234,97,255};
            else
                light={255,50,0,255};

    

    int offset=200;
    DrawTextureEx(plate_on,location,0,scale,WHITE);
    //flashing LED light
    DrawCircle(location.x+plate_off.width*scale*0.925,location.y+plate_off.height*scale*.19,6,light);

    
    DrawTextureEx(knob,{slidepoint-10,(plate_off.height)*scale/5+location.y},0,scale,WHITE);

    
    char buffer[50];
            snprintf(buffer,sizeof(buffer),"value: %d  ",value);

            DrawTextEx(pencil,buffer,{location.x+plate_off.width*scale,
                    location.y+(plate_off.height*scale)/3},50,0,BLACK);

    



    ismoving=false;

    return;
}


//********************************************************** */
//   Generates a delay of given duration (seconds)
//   for timing animations

bool Slider::sltimer()
{

    if(timer<0.4)
    {
            timer+=GetFrameTime();

    }
        else
            {
                timer=0;
                timerflag=false;
            }

return false;


}
//********************************************************** */
