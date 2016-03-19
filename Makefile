CC=g++
C_FLAGS=-c -Wall -std=c++11
LIBS=-lSDL2 -lSDL2_ttf

pong: clean main.o
	$(CC) $(LIBS) build/*.o -o pong 

main.o: src/main.cpp
	$(CC) $(C_FLAGS) $(LIBS) src/main.cpp -o build/main.o

pong.o: src/game/Pong.cpp
	$(CC) $(C_FLAGS) $(LIBS) src/game/Pong.cpp -o build/pong.o

gui.o: src/game/GUI.cpp
	$(CC) $(C_FLAGS) $(LIBS) src/game/GUI.cpp -o build/gui.o

timer.o: src/util/Timer.cpp
	$(CC) $(C_FLAGS) $(LIBS) src/util/Timer.cpp -o build/timer.o

staticitem.o: src/game/StaticItem.cpp
	$(CC) $(C_FLAGS) $(LIBS) src/game/StaticItem.cpp -o build/staticitem.o

clean: 
	\rm -rf build/** pong
