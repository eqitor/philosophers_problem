#include <iostream>
#include <thread>
#include "object.h"
#include <ncurses.h>




/*
*	Simulation of 5 dining philosophers problem using resource hierarchy solution.
	Control:
	1,2,3,4,5 - start/stop philosopther thread
	q - stops all philosophers and exit
*/


using namespace std;


const int X_OFFSET = 15;			//elements position offset
const int Y_OFFSET = 5;

int main(){


	initscr();
	refresh();
	Fork *fork1 = new Fork(1, 20+Y_OFFSET, 22+X_OFFSET, 'n');				//creating forks
	Fork *fork2 = new Fork(2, 20+Y_OFFSET, 52+X_OFFSET, 'n');
	Fork *fork3 = new Fork(3, 10+Y_OFFSET, 72+X_OFFSET, 'w');
	Fork *fork4 = new Fork(4, 3+Y_OFFSET , 37+X_OFFSET, 's');
	Fork *fork5 = new Fork(5, 10+Y_OFFSET, 0+X_OFFSET, 'e');

	
	std::thread t1, t2, t3, t4, t5;											//creating threads
	
	

	Philosopher *p1, *p2, *p3, *p4, *p5;									//creating pointers to philosophers

	bool s1,s2,s3,s4,s5;													//value representing state of thread, true=off false=on
	s1 = s2 = s3 = s4 = s5 = true;


	char start = 'x';
	while(start != 'q'){													//main loop of program
		start = getch();
		if(start == '1' && s1 == true){										//creating Philosopher and starts thread
			p1 = new Philosopher("Platon" , fork1, fork2, 20+Y_OFFSET, 37+X_OFFSET,"P");
			t1 = std::thread([p1]{p1->exist();});
			s1 = false;
		}
		else if(start == '1' && s1 == false){								//lets thread stop when it's running
			p1->stop();
			t1.join();
			s1 = true;
		}
		else if(start == '2' && s2 == true){
			p2 = new Philosopher("Euklides" , fork2, fork3, 20+Y_OFFSET, 72+X_OFFSET,"E");
			t2 = std::thread([p2]{p2->exist();});
			s2 = false;
		}
		else if(start == '2' && s2 == false){
			p2->stop();
			t2.join();
			s2 = true;
		}
		else if(start == '3' && s3 == true){
			p3 = new Philosopher("Sokrates" , fork3, fork4, 3+Y_OFFSET, 72+X_OFFSET,"S");
			t3 = std::thread([p3]{p3->exist();});
			s3 = false;
		}
		else if(start == '3' && s3 == false){
			p3->stop();
			t3.join();
			s3 = true;
		}
		else if(start == '4' && s4 == true){
			p4 = new Philosopher("Nietzsche" , fork4, fork5, 3+Y_OFFSET, 0+X_OFFSET,"N");
			t4 = std::thread([p4]{p4->exist();});
			s4 = false;
		}
		else if(start == '4' && s4 == false){
			p4->stop();
			t4.join();
			s4 = true;
		}
		else if(start == '5' && s5 == true){
			p5 = new Philosopher("Freud" , fork5, fork1, 20+Y_OFFSET, 0+X_OFFSET,"F");
			t5 = std::thread([p5]{p5->exist();});
			s5 = false;
		}
		else if(start == '5' && s5 == false){
			p5->stop();
			t5.join();
			s5 = true;
		}
		else if(start == 'q'){														//stops all threads and quit

			if(s1 == false){
				p1->stop();
				t1.join();
			}
			if(s2 == false){
				p2->stop();
				t2.join();
			}
			if(s3 == false){
				p3->stop();
				t3.join();
			}
			if(s4 == false){
				p4->stop();
				t4.join();
			}
			if(s5 == false){
				p5->stop();
				t5.join();
			}



		}
	}
	
	refresh();
	endwin();

}