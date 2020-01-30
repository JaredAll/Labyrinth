#ifndef RENDER_COMPONENT_H
#define RENDER_COMPONENT_H

#include <SDL.h>

class RenderComponent
{
public:
  virtual void draw( SDL_Renderer* renderer ) = 0;
};

#endif
