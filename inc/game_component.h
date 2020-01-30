#ifndef GAME_COMPONENT_H
#define GAME_COMPONENT_H

#include "render_component.h"

class GameComponent
{
public:
  RenderComponent* getRenderComponent()
  {
    return renderComponent;
  }

private:
  RenderComponent* renderComponent;
};

#endif
