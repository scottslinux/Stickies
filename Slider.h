#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>

class Slider
{
private:

    float scale=1.0;
    float timer=0.0;    //use for animation timing
    Rectangle knobrect;
    int knoboffset=0;
    
    bool timerflag=false;
    bool animationflag=false;
    bool ismoving=false;

    Vector2 location;

    static Texture2D plate_off;
    static Texture2D knob;
    static Texture2D plate_on;

                            //instance specific



    static Font pencil;
    //static Sound slide;

    static bool resourceguard;
    static int resourcecounter;



   


    public:
    int value=0;   //starting value of slider
    int detents=2; //number of detents along slider
    int min=0;
    int max=10;

    //variables to help define the slide start and stop points on the backplate for calculating 
    //the position of the slider

    float x1=0;
    float x2=0;
    float slidelength=0;
    float slidepoint=0;
    float percentage=0;
    

    Slider(Vector2 location,float scale,int detnts, int min,int max);
    ~Slider();

    int update();
    void draw();
    int getSliderValue();
    void unloadResources();
    bool slidetimer();
    bool sltimer();



};










    




