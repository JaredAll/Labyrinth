#include "game_renderer.h"

void GameRenderer::render( std::vector<GameComponent*> gameComponents )
{
  for( uint i = 0; i < gameComponents.size(); i++ )
  {
    RenderComponent* renderComponent =
      gameComponents.at( i ) -> getRenderComponent();

    renderComponent -> draw( renderer );
  }
}
