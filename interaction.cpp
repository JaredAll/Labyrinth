#include "interaction.h"

Interaction::Interaction( vector< string > param_messages,
                          int param_scene_position,
                          SDL_Renderer* param_renderer,
                          uint font_size ) :
  messages( param_messages ),
  scene_position( param_scene_position ),
  main_display( 100, 100, 100, 300 ),
  renderer( param_renderer )
{
  TTF_Init();
  font = TTF_OpenFont( "OpenSans-Bold.ttf", font_size );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n",
            TTF_GetError() );
  }
}                         

Interaction::Interaction( vector< string > param_messages,
                          int param_scene_position,
                          SDL_Renderer* param_renderer ) :
  messages( param_messages ),
  scene_position( param_scene_position ),
  main_display( 100, 100, 100, 100 ),
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

void Interaction::interact( Background background )
{
  bool end = false;
  bool quit = false;
  SDL_Event e;
  uint message_position = 0;
  uint message_length = messages.size();
  bool interacting = true;
  
  while( interacting )
  {
    if( message_position < message_length )
    {
      scroll_text( messages.at( message_position ),
                   renderer, font, background );
    }
  
    while( SDL_PollEvent( &e ) && !end )
    {
      if( e.type == SDL_QUIT )
      {
        interacting = false;
      }
      if( e.type == SDL_KEYDOWN )
      {
        end = true;
      }
    }
    SDL_RenderClear( renderer );
    background.draw();
    message_position++;
  }

  if( message_position == message_length )
  {
    interacting = false;
  }
}

void Interaction::scroll_text( string message,
                               SDL_Renderer* renderer,
                               TTF_Font *font,
                               Background background )
{
  for( uint letters = 0; letters <= message.size(); letters++ )
  {
    uint milliseconds = 250;
    SDL_RenderClear( renderer );
    background.draw();
    main_display.display( message, renderer, font, letters );
    usleep( milliseconds * milliseconds );
    SDL_RenderPresent( renderer );
  }
}

int Interaction::get_scene_position()
{
  return scene_position;
}
