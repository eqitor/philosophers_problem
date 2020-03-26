#include <ncurses.h>
#include <iostream>
#include <ctype.h>
#include "gobject.h"



using namespace std;

GPhilosopher::GPhilosopher(string name, int y_pos, int x_pos, string shape_char):name(name){
    shape = shape_char + shape_char + string("\n") + shape_char + shape_char;       //creating shape using custom letters
    this->shape_w = newwin(2,3,y_pos,x_pos);                                        //creating shape window
    this->text_w = newwin(3,15,y_pos+3,x_pos-6);                                    //creating text window

    refresh();                                                                      
    wrefresh(shape_w);
    wrefresh(text_w);
}

/* Clears text and shape window. */
void GPhilosopher::clear()
    {
        mvwprintw(shape_w, 0,0, "               ");
        mvwprintw(text_w,0,0, "                                            ");
        wrefresh(shape_w);
        wrefresh(text_w);
        
    }


/*Draw philisopher model with name, state, and time to change of state (percent).
* @state - state of Philosopher
* @time - time to change of state (percent)
*/
void GPhilosopher::draw(string state, int time){
    clear();
    mvwprintw(shape_w, 0,0, shape.c_str());
    mvwprintw(text_w,0,0,(name + string("\n") + state + string("\n") + to_string(time) + string("/100")).c_str());
        
    wrefresh(shape_w);
    wrefresh(text_w);
}

GPhilosopher::~GPhilosopher(){
        clear();
        delete shape_w;
        delete text_w;
    }





GFork::GFork(){};

GFork::GFork(int num, int y_pos, int x_pos, char ori) : number(num){
    orient = tolower(ori);
    if(orient == 'n'){
        shape = string("|_|_|\n")+                               //definition of model for 'N' orientation
                string("  |  \n")+
                string("  ") + to_string(number) + string("  ");
        this->shape_w = newwin(3,6,y_pos,x_pos);                 //shape window for 'N' orientation
        this->text_w = newwin(2,15,y_pos+4,x_pos-6);             //text window for 'N' orientation

    }
    else if(orient == 's'){
        shape = string("  ") + to_string(number) + string("  \n")+
                string(" _|_ \n")+
                string("| | |");
        this->shape_w = newwin(3,6,y_pos,x_pos);
        this->text_w = newwin(2,15,y_pos-2,x_pos-6);
        
    }
    else if(orient == 'w'){
        shape = string("__    \n")+
                string("__|__") + to_string(number) + string("\n")+
                string("__|   \n");

        this->shape_w = newwin(3,7,y_pos,x_pos);
        this->text_w = newwin(2,15,y_pos,x_pos+7);
    }
    else if(orient == 'e'){
        shape = string("    __\n")+
                to_string(number) + string("__|__\n")+
                string("   |__");

        this->shape_w = newwin(3,7,y_pos,x_pos);
        this->text_w = newwin(2,15,y_pos,x_pos-15);


    }
    else{
        shape = string("|_|_|\n")+
                string("  |  \n")+
                string("  ") + to_string(number) + string("  ");


        this->shape_w = newwin(3,6,y_pos,x_pos);
        this->text_w = newwin(2,15,y_pos+3,x_pos-6);
    }
    draw("Nobody");                                          //drawing fork with no owner


    

} 

GFork::~GFork(){
    clear();
    delete shape_w;
    delete text_w;
}


/*
* Fits text strings to window (adding blank spaces)
* @s - input string
* @return char* representation of modified text
*/
const char* GFork::convert_str(string s)
{
    int spaces;
    if(orient == 'w') return s.c_str();          //calculate ammount of blank spaces for orientation
    if(orient == 'e') spaces = 15 - s.length();
    else spaces = 8 - s.length()/2;
    
    
    string sample;
    
    for(int i = 0; i < spaces;i++){
        sample+=" ";
    }
    sample+=s;
    return sample.c_str();
}

/*Draw fork model with his owner.
* @owner - Philosopher who uses this Fork.
* 
    */
void GFork::draw(std::string owner)
{
    clear();
    mvwprintw(shape_w, 0,0, shape.c_str());
    mvwprintw(text_w,0,0, convert_str(owner));
    
    wrefresh(shape_w);
    wrefresh(text_w);
    refresh();


}
/* Clears text and shape window. */
void GFork::clear()
{
    mvwprintw(shape_w, 0,0, "               ");
    mvwprintw(text_w,0,0, "               ");
    wrefresh(shape_w);
    wrefresh(text_w);
    
}