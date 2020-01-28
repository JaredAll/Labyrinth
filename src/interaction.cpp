#include "interaction.h"

Interaction::Interaction( vector< string > param_messages,
                          int param_scene_position,
                          SDL_Renderer* param_renderer ) :
  messages( param_messages ),
  scene_position( param_scene_position ),
  main_display( 200, 200, 200, 400 ),
  renderer( param_renderer )
{
  TTF_Init();
  font = TTF_OpenFont( "/home/jared/Games/Labyrinth/resources/OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n",
            TTF_GetError() );
  }
}

uint Interaction::get_interaction_length()
{
  return messages.size();
}

string Interaction::get_message( uint index )
{
  return messages.at( index );
}

int Interaction::get_scene_position()
{
  return scene_position;
}
