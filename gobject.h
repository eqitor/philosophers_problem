#include <ncurses.h>
#include <iostream>
#include <ctype.h>
//#include <bject.h>

using namespace std;

/*
*   Visual representation of Philosopher.
*
*/
class GPhilosopher{
    string name;                //name of philosopher
    string shape;               //string with shape of model
    WINDOW *shape_w, *text_w;   //shape_w - window for shape, text_w - window for text

    public:

    GPhilosopher();
    GPhilosopher(string name, int y_pos, int x_pos, string shape_char);
    void clear();
    void draw(string state, int time);
    ~GPhilosopher();

};

/*
*   Visual representation of Fork.
*
*/
class GFork{
    int number;                     //number assigned to Fork
    string shape;                   //string with shape of model
    char orient;                    //orientation of model (N,S,W,E)
    WINDOW * shape_w, *text_w;      //shape_w - window for shape, text_w - window for text

    public:

    GFork();
    GFork(int num, int y_pos, int x_pos, char ori);
    ~GFork();
    const char* convert_str(std::string s);
    void draw(std::string owner);
    void clear();

};