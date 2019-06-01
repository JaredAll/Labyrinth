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

void Text_box::display( char *message, SDL_Renderer *renderer,
  TTF_Font *font )
{
    
  SDL_Color White = {0, 0, 0};
  SDL_Surface *message_surface =
    TTF_RenderText_Solid( font, message, White );
  SDL_Texture *message_texture =
    SDL_CreateTextureFromSurface( renderer,
                                  message_surface );

  SDL_RenderCopy( renderer, message_texture, NULL, &message_rect );
}
