# Labyrinth
A rudimentary video game. All sprites and backgrounds courtesy of Hugh Keene.

# Purpose
This is mainly an educational project, one where I can make the design and implementation decisions while learning
more about C++ and game physics in general. It serves as my first serious pass into game engine design and game design. The lessons and technology learned here will factor into the next version. This project uses [SDL2](https://www.libsdl.org/download-2.0.php).

I have recently read *Design Patterns* by the Gang of Four and *Game Programming Patterns* by Robert Nystrom. I plan to refactor my existing code to make use of design patterns and improve the overall design.

# Build Instructions
Requires clang++, gnumake, and some SDL2 libraries. Current compiler switches are `-Werror -pedantic-errors -O0 -Wno-c++98-compat-pedantic -Wno-padded -std=c++11`. 
Please see the makefile for build dependencies. 
