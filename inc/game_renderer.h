#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "game_component.h"
#include <vector>
#include <SDL.h>
#include <stdio.h>
#include <iostream>
#include "easy_sdl.h"
#include "cleanup.h"

class GameRenderer
{
public:
  GameRenderer( SDL_Window* win );

  void render( std::vector<GameComponent*> gameComponents );

private:
  SDL_Renderer* renderer;
};

#endif
