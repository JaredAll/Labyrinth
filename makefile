CXX = clang++
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
SDL_INCLUDE = -I/usr/include/SDL2
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++11 $(SDL_INCLUDE)
LINKER_FLAGS = $(SDL_LIB)


all: sketch_1 sketch_2

sketch_1.o: sketch_1.cpp
	$(CXX) $(CXX_FLAGS) -c sketch_1.cpp

sprite.o: sprite.h sprite.cpp
	$(CXX) $(CXX_FLAGS) -c sprite.cpp

sprite_layer.o: sprite_layer.h sprite_layer.cpp
	$(CXX) $(CXX_FLAGS) -c sprite_layer.cpp

background.o: background.h background.cpp
	$(CXX) $(CXX_FLAGS) -c background.cpp

character.o: character.h character.cpp
	$(CXX) $(CXX_FLAGS) -c character.cpp

conversation.o: conversation.h conversation.cpp
	$(CXX) $(CXX_FLAGS) -c conversation.cpp

scene.o: scene.h scene.cpp
	$(CXX) $(CXX_FLAGS) -c scene.cpp

game.o: game.h game.cpp
	$(CXX) $(CXX_FLAGS) -c game.cpp

sketch_2: sketch_2.o
	$(CXX) $(LINKER_FLAGS) -o sketch_2 sketch_2.o

sketch_2.o: sketch_2.cpp
	$(CXX) $(CXX_FLAGS) -c sketch_2.cpp

script.o: script.h script.cpp
	$(CXX) $(CXX_FLAGS) -c script.cpp

sceneJunction.o: sceneJunction.h sceneJunction.cpp
	$(CXX) $(CXX_FLAGS) -c sceneJunction.cpp

text_box.o: text_box.h text_box.cpp
	$(CXX) $(CXX_FLAGS) -c text_box.cpp

easy_sdl.o: easy_sdl.h easy_sdl.cpp
	$(CXX) $(CXX_FLAGS) -c easy_sdl.cpp

sketch_1: sketch_1.o sprite.o sprite_layer.o background.o character.o conversation.o scene.o game.o script.o sceneJunction.o text_box.o easy_sdl.o
	$(CXX) $(LINKER_FLAGS) -o sketch_1 sketch_1.o background.o sprite_layer.o character.o conversation.o scene.o sprite.o game.o script.o sceneJunction.o text_box.o easy_sdl.o

clean:
	rm *.o && rm sketch_1 && rm sketch_2
build_linux:
	cp *.o builds/linux/ && cp sketch_1 builds/linux/ && cp sketch_2 builds/linux/
