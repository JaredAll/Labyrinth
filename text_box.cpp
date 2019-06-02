#include "text_box.h"
#include <SDL_ttf.h>
#include <unistd.h>

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
  TTF_Font *font )
{
  message_rect.w = 25 * message.length();
  
  char message_array[ 100 ];
  strcpy( message_array, message.c_str() );
    
  SDL_Color color = {0, 0, 0};
  SDL_Surface *message_surface =
    TTF_RenderText_Solid( font, message_array, color );
  SDL_Texture *message_texture =
    SDL_CreateTextureFromSurface( renderer,
                                  message_surface );

  SDL_RenderCopy( renderer, message_texture, NULL, &message_rect );
}

