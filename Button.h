#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>


class Button

{
    protected:

    float buttonscale=1.0;
    float timer=0.0;

    
    bool timerflag=false;
    bool animationflag=false;

    Vector2 location;

    static Texture2D button_off;
    static Texture2D button_on;

                            //instance specific



    static Font pencil;
    static Sound click;

    static bool resourceguard;
    static int resourcecounter;



   


    public:
    bool value=false;   //true and false for on/off
    

    Button(Vector2 location,float scale);
    ~Button();

    virtual bool update();
    virtual void draw();
    bool getbuttonval();
    void unloadResources();
    bool clicktimer();



};
