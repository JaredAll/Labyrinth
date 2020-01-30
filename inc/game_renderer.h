#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "game_component.h"
#include <vector>
#include <SDL.h>

class GameRenderer
{
public:
  void render( std::vector<GameComponent*> gameComponents );

private:
  SDL_Renderer* renderer;
};

#endif
