#include "sprite_layer.h"

SpriteLayer::SpriteLayer( std::string image_path,
                          SDL_Renderer *renderer, int x, int y,
                          uint param_distance )
  : distance( param_distance )
{
  sprite = new Sprite( image_path, renderer, x, y );
  destination = new SDL_Rect();
}

SpriteLayer::~SpriteLayer()
{
  if( sprite )
  {
    sprite -> ~Sprite();
    sprite = NULL;
  }
}

void SpriteLayer::left( uint speed )
{
  if( distance > 0 )
  {
    sprite -> set_position(
      sprite -> get_x() - ( speed  / distance ),
      sprite -> get_y() );
  }
}

void SpriteLayer::right( uint speed )
{
  if( distance > 0 )
  { 
    sprite -> set_position(
      sprite -> get_x() + ( speed  / distance ),
      sprite -> get_y() );
  }
}

void SpriteLayer::draw()
{
  if( distance >= 1 )
  {
    destination -> x = sprite -> get_x();
    destination -> y = sprite -> get_y();
    destination -> w = sprite -> get_width() / distance;
    destination -> h = sprite -> get_height() / distance;
    sprite -> draw( destination );
  }
  else
  {
    destination -> x = sprite -> get_x();
    destination -> y = sprite -> get_y();
    destination -> w = sprite -> get_width();
    destination -> h = sprite -> get_height();
    sprite -> draw( destination );
  }
}

void SpriteLayer::reset()
{
  sprite -> reset_position();
}

void SpriteLayer::reset( int offset )
{
  if( distance > 0 )
  {
    sprite -> reset_position( offset / distance ); 
  }
}
