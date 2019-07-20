#include "interaction.h"

Interaction::Interaction( string param_message,
                          int param_scene_position,
                          SDL_Renderer* param_renderer ) :
  message( param_message ),
  scene_position( param_scene_position ),
  main_display( 200, 200, 200, 400 ),
  renderer( param_renderer )
{
  TTF_Init();
  font = TTF_OpenFont( "OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n",
            TTF_GetError() );
  }
}

void Interaction::interact()
{
  bool end = false;
  bool quit = false;
  SDL_Event e;

  scroll_text( message, renderer, font );
  
  while( !end && !quit )
  {
    SDL_PollEvent( &e );
    if( e.type == SDL_QUIT )
    {
      quit = true;
    }
    if( e.type == SDL_KEYDOWN )
    {
      end = true;
    }
  }
}

void Interaction::scroll_text( string message,
                               SDL_Renderer* renderer,
                               TTF_Font *font )
{
  for( uint letters = 0; letters < message.size(); letters++ )
  {
    uint milliseconds = 250;
    main_display.display( message, renderer, font, letters );
    usleep( milliseconds * milliseconds );
    SDL_RenderPresent( renderer );
  }
}

int Interaction::get_scene_position()
{
  return scene_position;
}
