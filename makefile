CXX = clang++-3.8
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image
SDL_INCLUDE = -I/usr/include/SDL2
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++11 $(SDL_INCLUDE)
LINKER_FLAGS = $(SDL_LIB)

all: sketch_1 sketch_2

sketch_1: sketch_1.o
	$(CXX) $(LINKER_FLAGS) -o sketch_1 sketch_1.o

sketch_1.o: sketch_1.cpp sprite.h sprite_layer.h background.h character.h scene.h game.h
	$(CXX) $(CXX_FLAGS) -c sketch_1.cpp

sketch_2: sketch_2.o
	$(CXX) $(LINKER_FLAGS) -o sketch_2 sketch_2.o

sketch_2.o: sketch_2.cpp
	$(CXX) $(CXX_FLAGS) -c sketch_2.cpp

clean:
	rm *.o && rm sketch_1 && rm sketch_2
