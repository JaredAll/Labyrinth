#include "text_box.h"

Text_box::Text_box( uint param_x, uint param_y, uint param_h )
  : x_pos( param_x ), y_pos( param_y ), height( param_h )
{
  
}

void Text_box::display( string message, SDL_Renderer *renderer,
                        TTF_Font *font, uint letters )
{  
  string to_be_rendered = message.substr( 0, letters );

  uint letter_width = height / 4;
    
  for( uint letter = 0; letter < to_be_rendered.length(); letter++ )
  {
    SDL_Rect letter_slot;
    letter_slot.x = x_pos + letter * letter_width;
    letter_slot.y = y_pos;
    letter_slot.h = height;
    letter_slot.w = letter_width;
    
    letter_slots.push_back( letter_slot );
  }
  
  char message_array[ 100 ];
  strcpy( message_array, to_be_rendered.c_str() );
  SDL_Color color = {0, 0, 0};
  
  for( uint i = 0; i < to_be_rendered.length(); i++ )
  {
    char letter_singleton[ 2 ] = { message_array[ i ], '\0' };
    SDL_Surface *letter_surface =
      TTF_RenderText_Solid( font, letter_singleton, color );
  
    SDL_Texture *letter_texture =
      SDL_CreateTextureFromSurface( renderer, letter_surface );
    SDL_RenderCopy( renderer, letter_texture, NULL,
                    &letter_slots.at( i ) );
  }

  letter_slots.clear();

}
