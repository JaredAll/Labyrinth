#include "text_box.h"

Text_box::Text_box( uint param_x, uint param_y, uint param_h,
                    uint param_w )
  : x_pos( param_x ), y_pos( param_y ), height( param_h ),
    width( param_w )
{
  display_box = new SDL_Rect();
  display_box -> x = x_pos;
  display_box -> y = y_pos;
  display_box -> h = height;
  display_box -> w = width;
}

void Text_box::display( string message, SDL_Renderer *renderer,
                        TTF_Font *font, uint letters )
{
  string to_be_rendered = message.substr( 0, letters );
  uint line_padding = 5;
  uint lines_per_box = 3;
  uint thin_letter_divisor = 10;
  uint letter_divisor = 6;

  uint next_x = 0;
  uint next_y = y_pos;

  if( message.substr( 0, letters - 1 ).compare( previous_message ) == 0 )
  {
    for( uint i = 0; i < letter_textures.size(); i++ )
    {
      SDL_RenderCopy( renderer, letter_textures.at( i ), NULL,
                      letter_slots.at( i ) );
    }
  }
  else
  {

    for( uint i = 0; i < letter_textures.size(); i++ )
    {
      cleanup( letter_textures.at( i ) );
    }

    letter_textures.clear();
    letter_slots.clear();

    for( uint letter = 0; letter < to_be_rendered.length(); letter++ )
    {
      SDL_Rect *letter_slot = new SDL_Rect();
      uint letter_width;
      if( to_be_rendered.at( letter ) == 'i' ||
          to_be_rendered.at( letter ) == 'l' ||
          to_be_rendered.at( letter ) == 'I' ||
          to_be_rendered.at( letter ) == ' ' )
      {
        letter_width = height / thin_letter_divisor;
      }
      else
      {
        letter_width = height / letter_divisor;
      }

      if( x_pos + next_x > width &&
          to_be_rendered.at( letter - 1 ) == ' ' )
      {
        next_y = next_y + (height / lines_per_box ) + line_padding;
        next_x = 0; 
      }

      letter_slot -> x = x_pos + next_x;
      letter_slot -> y = next_y;
      letter_slot -> h = height / lines_per_box;
      letter_slot -> w = letter_width;
    
      letter_slots.push_back( letter_slot );

      next_x += letter_width;
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
                      letter_slots.at( i ) );
      letter_textures.push_back( letter_texture );
      cleanup( letter_surface );
    }
  }
  previous_message = message;
}
