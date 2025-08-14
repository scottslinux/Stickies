#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <raylib.h>



using namespace std;


class InputBox{

    private:

        Font interfnt;
        Texture2D sticky;

        string txtstr="";

        int words=0;
        int chars=0;
        int lines=0;
        int fontsize=0;
        Vector2 xypos{};
        Vector2 cursorxy{};

        int boxwidth=0;
        int boxheight=0;
        float pxlwidth=0;
        float pxlheight=0;
        float charwidth=0;
        float charheight=0;

        float dtime=0.0;
        float cursorinterval=0.25;  //.25 ms cursor blink interval

        double timer=0;
        double timeinterval=1.0;

        vector<Color> notecolorchoices={
                { 0, 255, 255, 255 },   // cyan
                { 146,255,74, 255 },   // green
                { 255, 255, 0, 255 },    // yellow
                { 255, 170, 255,255}    //pink
        };
        Color notecolor={ 255, 255, 0, 200};
        float colorindex=0;

    public:

        InputBox(int bxwidth, int bxheight,int fntsz, Vector2 xypos);
        ~InputBox();

        string Update();        //returns a string when input complete
        void Draw();            //draw the box
        char KeyCodeToChar(int key);  //from my friend
        void drawcursor();
        bool blinktime();
        string GetString();
        void resetBox();
        Color getColor();













};