#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "raylib.h"
#include "Button.h"
#include "Menu.h"
#include "InputBox.h"
#include "Slider.h"

using namespace std;



struct notedata{
    string task;
    bool completed;
    Rectangle noterect{0,0,0,0};
    Vector2 notepos;
    float rotation;
    Color notetint;

};
//=============================================
//  ⁡⁣⁢⁣​‌‌



//=============================================

class Sticky{
    protected:
        static RenderTexture2D stickRnder;
        Texture2D stickypic;
        Font marker;
        Font titles;
        Button menuonff;
        Button savenote;
        Menu Changes;
        InputBox msgbox;
        Slider scaler;

        vector<notedata> StickyList;
        vector<RenderTexture2D> notepics;

        int activenotes=0;
        int dyingnote=0;    //note to dispose of
        double doubleclicktime=0.3;
        double fallingtimer=0;
        double lastclick=0;
        bool menuflag=false;
        bool submenuflag=false;
        bool rectflag=false;



        enum class states{intro,displaying,create,dispose};
        states currstate;

        vector<string> statesetring={"intro","displaying","create","dispose"};


    public:


        Sticky();
        ~Sticky();

        void intro_draw();
        void intro_update();

        void create_draw();
        void create_update();

        void displaying_update();
        void displaying_draw();

        void dispose_update();
        void dispose_draw();

        void draw();
        void update();

        void save2Vectors();
        void FiletoDisk();
        void LoadStickiesfromFile();










};