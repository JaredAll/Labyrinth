#include "text_box.h"

Text_box::Text_box( uint param_x, uint param_y, uint param_h,
                    uint param_w )
  : x_pos( param_x ), y_pos( param_y ), box_height( param_h ),
    box_width( param_w )
{
  message_rect.x = x_pos;
  message_rect.y = y_pos;
  message_rect.w = box_width;
  message_rect.h = box_height;
}

void Text_box::display( string message, SDL_Renderer *renderer,
                        TTF_Font *font, uint letters )
{
  string to_be_rendered = message.substr( 0, letters );

  message_rect.w = to_be_rendered.length() * 25;

  // for( uint i = 0; i < ( message.length() - to_be_rendered.length());
  //      i++ )
  // {
  //   to_be_rendered = to_be_rendered + ".";
  // }
  
  char message_array[ 100 ];
  strcpy( message_array, to_be_rendered.c_str() );
    
  SDL_Color color = {0, 0, 0};
  SDL_Surface *message_surface =
    TTF_RenderText_Solid( font, message_array, color );
  SDL_Texture *message_texture =
    SDL_CreateTextureFromSurface( renderer,
                                  message_surface );

  SDL_RenderCopy( renderer, message_texture, NULL, &message_rect );
}
