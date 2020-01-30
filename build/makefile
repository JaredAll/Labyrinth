CXX = clang++
SDL_LIB = -L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf
TEST_LIB = -lcppunit
FAKEIT_INCLUDE = -I/home/jared/cpp_dev/FakeIt/single_header/standalone
SDL_INCLUDE = -I/usr/include/SDL2
INC_INCLUDE = -I../inc
CXX_FLAGS = -Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++11 $(SDL_INCLUDE) $(INC_INCLUDE) $(FAKEIT_INCLUDE)
LINKER_FLAGS = $(SDL_LIB) $(TEST_LIB)
OBJ_FILES = sprite.o sprite_layer.o background.o character.o conversation.o scene.o game.o script.o sceneJunction.o text_box.o panel.o interaction.o easy_sdl.o state.o walking_state.o game_renderer.o
TEST_OBJ_FILES = test_background.o
VPATH = ../src/test:../src/main

all: sketch_1 tests

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) -c $<

sketch_1: $(OBJ_FILES) sketch_1.o
	$(CXX) $(LINKER_FLAGS) -o sketch_1 $(OBJ_FILES) sketch_1.o

tests: $(TEST_OBJ_FILES)
	$(CXX) $(LINKER_FLAGS) -o tests $(TEST_OBJ_FILES) $(OBJ_FILES)

clean:
	rm *.o && rm sketch_1 && rm *tests

test:
	./tests

build_linux:
	cp *.o builds/linux/ && cp sketch_1 builds/linux/
