#include "sprite_layer.h"

SpriteLayer::SpriteLayer( std::string image_path,
                          SDL_Renderer *renderer, int x, int y,
                          uint param_distance )
: Sprite::Sprite( image_path, renderer, x, y ),
  distance( param_distance )
{
  
}

void SpriteLayer::left( uint speed )
{
  if( distance > 0 )
  {
    set_position(
      get_x() - ( speed  / distance ),
      get_y() );
  }
}

void SpriteLayer::right( uint speed )
{
  if( distance > 0 )
  { 
    set_position(
      get_x() + ( speed  / distance ),
      get_y() );
  }
}

void SpriteLayer::draw()
{
  if( distance > 1 )
  {
    SDL_Rect destination;
    destination.x = get_x();
    destination.y = get_y();
    destination.w = get_width() / distance;
    destination.h = get_height() / distance;
    Sprite::draw( destination );
  }
  else
  {
    Sprite::draw();
  }
}

void SpriteLayer::reset()
{
  reset_position();
}

void SpriteLayer::reset( int offset )
{
  if( distance > 0 )
  {
    reset_position( offset / distance ); 
  }
}
