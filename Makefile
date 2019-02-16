CXX = g++
CPPFLAGS=$(shell pkg-config --cflags sdl2) -D_THREAD_SAFE -lSDL2_image -lSDL2 -lpthread -std=c++11

all: strawberryhunter

strawberryhunter: main.cpp game_engine.o object.o gun.o projectile.o strawberry.o tools.o
	$(CXX) -o $@ $^ $(CPPFLAGS)

clean:
	rm *.o strawberryhunter

object.o: object.cpp game_engine.o 
	$(CXX) -c -w $(CPPFLAGS) -o $@ $< 
game_engine.o: game_engine.cpp
	$(CXX) -c -w $(CPPFLAGS) -o $@ $<	
gun.o: gun.cpp
	$(CXX) -c -w $(CPPFLAGS) -o $@ $<
projectile.o: projectile.cpp
	$(CXX) -c -w $(CPPFLAGS) -o $@ $<
strawberry.o: strawberry.cpp
	$(CXX) -c -w $(CPPFLAGS) -o $@ $<
tools.o: tools.cpp
	$(CXX) -c -w $(CPPFLAGS) -o $@ $<
