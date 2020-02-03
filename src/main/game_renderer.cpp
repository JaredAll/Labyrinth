#include "game_renderer.h"

GameRenderer::GameRenderer( SDL_Window* win )
{
  //create renderer
  SDL_Renderer *ren =
    SDL_CreateRenderer(win, -1,
                       SDL_RENDERER_ACCELERATED
                       | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr)
  {
    cleanup( win );
    logSDLError( std::cout, "CreateRenderer" );
    SDL_Quit();
  }
  renderer = ren;
}

void GameRenderer::render( std::vector<GameComponent*> gameComponents )
{
  for( uint i = 0; i < gameComponents.size(); i++ )
  {
    gameComponents.at( i ) -> draw( renderer );
  }
}

SDL_Texture* GameRenderer::load_texture( std::string image_path )
{
  return load_texture( image_path, renderer );
}
