# Labyrinth
A rudimentary video game. All sprites and backgrounds courtesy of Hugh Keene.

# Purpose
This is mainly an educational project, one where I can make the design and implementation decisions while learning
more about C++ and game physics in general. It serves as my first serious pass into game engine design and game design. The lessons and technology learned here will factor into the next version. This project uses [SDL2](https://www.libsdl.org/download-2.0.php).

Over the past few weeks, I have read Design Patterns by the Gang of Four and Game Programming Patterns by Robert Nystrom. I plan to refactor my existing code to make use of design patterns and improve the overall design.

# Build Instructions
Requires clang++, gnumake, and some SDL2 libraries. Current compiler switches are `-Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++11`. 
The library and includes are `-L/usr/local/lib -lSDL2 -lSDL2_image -lSDL2_ttf`
and `-I/usr/include/SDL2`, respectively. Please see the makefile for build 
dependencies. 

I am open to using CMake, however as of yet I am not well versed in it. Since this is an educational project, understanding makefiles at a lower level is given priority over proper build structure and easy build implementation.
