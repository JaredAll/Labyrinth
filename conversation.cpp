#include "conversation.h"
Conversation::Conversation()
{
  
}

SDL_Texture* Conversation::get_dialogue( uint index )
{
  return dialogue.at( index );
}

void Conversation::add_dialogue( char* words, SDL_Renderer* renderer )
{
  TTF_Init();
  TTF_Font *font;
  font = TTF_OpenFont( "OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  
  SDL_Color White = {0, 0, 0};
  SDL_Surface *message_surface =
    TTF_RenderText_Solid( font, words, White );
  SDL_Texture *message =
    SDL_CreateTextureFromSurface( renderer,
                                  message_surface );
  dialogue.push_back( message );
}
