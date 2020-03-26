#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <chrono>
#include "object.h"



const int CONST_TIME = 2000;                        //constant duration of time for every state


Fork::Fork(){};

Fork::Fork(int id, int y_pos, int x_pos, char ori) {
    this->id = id;
    g = new GFork(id, y_pos, x_pos, ori);
}

Fork::~Fork(){
    delete g;
}


/*
* Returns id.
* @return id
*/
int Fork::get_id()
{
    return id;
}



/*
* Sets owner of Fork.
*/
void Fork::set_owner(std::string name)
{
    g->draw(name);
}




Philosopher::Philosopher(){};

Philosopher::Philosopher(std::string name, Fork * l, Fork * r, int y_pos, int x_pos, string shape_char): name(name), left(l),right(r), execute(true) {
    gp = new GPhilosopher(name, y_pos, x_pos, shape_char);

}

Philosopher::~Philosopher(){
    delete gp;
}

/*
* Waits for time definied in 'ms' and draws ammount of time to change state (percent) with state.
* @state - state of Philosopher
* @ms - time to wait in ms
*/
void Philosopher::wait_with_graphics(string state, int ms)
{
    for(int i = ms; i >= 0; i-=ms/5){
        std::this_thread::sleep_for(std::chrono::milliseconds(ms/5));
        gp->draw(state, ((ms-i)*100)/ms);
    }
}

/*
* Prints state of Philosopher without waiting
* @state - state of Philisopher
*/
void Philosopher::state_with_graphics(string state){
    gp->draw(state, 0);
}

/*
* Representing life of Philisopher
*/
void Philosopher::exist(){
    while(execute){             //if execute == False, function stops
        think();
        eat();
    }

    gp->clear();
}
    /*
* Simulation of eating.
*/
void Philosopher::eat(){
    if (left->get_id() > right->get_id())       //checks which fork has bigger id
    {
        bigger = left;
        smaller = right;
    }
    else{
        bigger = right;
        smaller = left;
    }
    state_with_graphics("Hungry");
    std::lock_guard<std::mutex> guard1(smaller->mutex);             //waits for free forks
    std::lock_guard<std::mutex> guard2(bigger->mutex);
    bigger->set_owner(name);                                        //assign forks to new owner
    smaller->set_owner(name);
    static thread_local std::uniform_int_distribution<> wait(0, 10);        //calculate random offset of time
    wait_with_graphics("Eating", CONST_TIME + wait(range) * 50);
    bigger->set_owner("Nobody");                                    //returns forks
    smaller->set_owner("Nobody");



    
}
    /*
* Simulation of eating.
*/
void Philosopher::think(){
    static thread_local std::uniform_int_distribution<> wait(1, 10); //calculate random offset of time
    wait_with_graphics("Thinking", CONST_TIME + wait(range) * 50);
}


/*
* Stops thread
*/
void Philosopher::stop(){
    execute = false;
}