#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "render_component.h"

class GameComponent
{
public:
  virtual void draw( SDL_Renderer* renderer )
  {
    renderComponent -> draw( renderer );
  }

  virtual void update() = 0;

  void setRenderComponent( RenderComponent* component )
  {
    renderComponent = component;
  }

private:
  RenderComponent* renderComponent;
};

#endif
