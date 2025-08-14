#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <raylib.h>

#include "InputBox.h"

//======================================================================
InputBox::InputBox(int bxwidth, int bxheight,int fntsz, Vector2 xy):boxwidth(bxwidth),boxheight(bxheight),fontsize(fntsz),
                    xypos(xy)

{
    //boxwidth and height refer to the number of characters across and down


    interfnt=LoadFont("./resources/marker.ttf");
    sticky=LoadTexture("./resources/stickypic.png");

    string teststr="WMUDZ"; // string of 5 test chars
 
    // use 5 wide characters and then average out the width. Mult by the number of characters
    //desired in the box. Do the same for height except no averaging
    Vector2 sizetest=MeasureTextEx(interfnt,teststr.c_str(),fontsize,0);
    charwidth=sizetest.x/5;
    charheight=sizetest.y;

    pxlwidth=(sizetest.x/5)*boxwidth;
    pxlheight=sizetest.y * boxheight;

    cursorxy={0,0};




}
//======================================================================
InputBox::~InputBox()
{
    UnloadFont(interfnt);
    UnloadTexture(sticky);
    
}
//======================================================================
string InputBox::Update()
{

    int key = GetKeyPressed();

while (key > 0) 
    {
        char ch = KeyCodeToChar(key);
        if (ch != 0) 
            {
                txtstr += ch;
            }

        key = GetKeyPressed();


    }
    
  if(GetMouseWheelMove())  
  {
    colorindex+=0.1;
    if (colorindex>notecolorchoices.size())
        colorindex=0;
    notecolor=notecolorchoices[colorindex];
  }

    return "";
}
//======================================================================
void InputBox::Draw()
{
   //Rectangle txtbx={xypos.x,xypos.y,pxlwidth,pxlheight};


   DrawTextureEx(sticky,{xypos.x-50,xypos.y},0,.6,notecolor);

   DrawTextEx(interfnt,txtstr.c_str(),{xypos},fontsize,0,BLACK);

   drawcursor();
}
//======================================================================

char InputBox::KeyCodeToChar(int key)
{
    bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);

    if(IsKeyPressed(KEY_BACKSPACE))
        if(txtstr.length()>0)
            txtstr.pop_back();

    // Letters A-Z
    if (key >= KEY_A && key <= KEY_Z) {
        return (shift ? 'A' : 'a') + (key - KEY_A);
    }

    // Numbers 0-9
    if (key >= KEY_ZERO && key <= KEY_NINE) {
        const char normal[]  = "0123456789";
        const char shifted[] = ")!@#$%^&*(";
        return shift ? shifted[key - KEY_ZERO] : normal[key - KEY_ZERO];
    }

    // Space, Tab, Enter
    if (key == KEY_SPACE) return ' ';
    if (key == KEY_TAB)   return '\t'; // black square;
    if (key == KEY_ENTER) return '\n';

    // Punctuation & symbols
    switch (key) {
        case KEY_MINUS:       return shift ? '_' : '-';
        case KEY_EQUAL:       return shift ? '+' : '=';
        case KEY_LEFT_BRACKET:return shift ? '{' : '[';
        case KEY_RIGHT_BRACKET:return shift ? '}' : ']';
        case KEY_BACKSLASH:   return shift ? '|' : '\\';
        case KEY_SEMICOLON:   return shift ? ':' : ';';
        case KEY_APOSTROPHE:  return shift ? '"' : '\'';
        case KEY_COMMA:       return shift ? '<' : ',';
        case KEY_PERIOD:      return shift ? '>' : '.';
        case KEY_SLASH:       return shift ? '?' : '/';
        case KEY_GRAVE:       return shift ? '~' : '`';
    }

    return 0; // not a printable key
}
//===========================================================
void InputBox::drawcursor()
{
    int colpos=0;
    int cols=0;
    int rows=0;
    int rowpos=0;
    

    for (char i:txtstr)
        {   
            if (i=='\n')
            {
                colpos=0;   //reset to next line for a newline char
                rows++;
                rowpos+=charheight;
                
            }
            else
            {
                cols++;
                string test(1,i);
                colpos+=MeasureTextEx(interfnt,test.c_str(),fontsize,0).x;

            }
            
            
            //cout<<"colpos: "<<colpos<<endl;



        }
       

        blinktime();        //start the timer

        if(timer<timeinterval/2)
            DrawRectangle(xypos.x+colpos,xypos.y+rowpos,40,charheight,GREEN);
            


     //cout<<"row: "<<rows<<endl;

     
  
        return;
     

}

//===============================================================
bool InputBox::blinktime()
{
    
    timer+=GetFrameTime();

    if (timer > timeinterval)
    {
        timer=0;
        return true;

    }

    else return false;

}
//=============================================================
string InputBox::GetString()
{
    return txtstr;


}
//=============================================================
void InputBox::resetBox()
{
    txtstr="";

    return;
}
//=============================================================
Color InputBox::getColor()
{
    return notecolor;
}