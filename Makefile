filo: Main.o object.o gobject.o
	g++ Main.o object.o gobject.o -o filo -pthread -lncurses

Main.o: Main.cpp
	g++ -c Main.cpp -pthread -lncurses


object.o: object.cpp
	g++ -c object.cpp -pthread -lncurses

gobject.o: gobject.cpp
	g++ -c gobject.cpp -lncurses

clean:
	rm *.o filo
