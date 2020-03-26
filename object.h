#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include "gobject.h"



/*
* Representation of fork used by philosophers
*/
class Fork{
    int id;                 //id of fork
    GFork *g;               //pointer to GFork, visual model of Fork


    public:
    std::mutex mutex;       //mutex used to lock Fork


    Fork();
    Fork(int id, int y_pos, int x_pos, char ori);
    ~Fork();
    int get_id();
    void set_owner(std::string name);
    
};

/*
* Representation philosopher.
*/
class Philosopher{
    std::string name;                   //name of philosopher
    Fork *left;                         //pointer to left fork
    Fork *right;                        //pointer to right fork
    std::mt19937 range{ std::random_device{}() };       //instance of numbers generator
    Fork *bigger;                       //pointer to fork with bigger index
    Fork *smaller;                      //pointer to fork with smaller index
    GPhilosopher *gp;                   //pointer to GPhilosopher, visual model of Philosopher

    bool execute;                       //boolean value used to shut down process



    public:

    Philosopher();
    Philosopher(std::string name, Fork * l, Fork * r, int y_pos, int x_pos, string shape_char);
    ~Philosopher();
    void wait_with_graphics(string state, int ms);
    void state_with_graphics(string state);
    void exist();
    void eat();
    void think();
    void stop();

};