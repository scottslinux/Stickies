#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"
#include "Button.h"

using namespace std;



struct notedata{
    string task;
    bool completed;

    Rectangle noterect{0,0,0,0};

};

class Sticky{
    protected:
        static RenderTexture2D stickRnder;
        Texture2D stickypic;
        Font marker;
        Button menuonff;

        vector<notedata> StickyList;
        int activenotes=0;
        bool menuflag=false;

    public:


        Sticky();
        ~Sticky();

        void createNote();
        void display();
        void update();
        void destroyoldnote();










};