#ifndef SPRITE_LAYER_H
#define SPRITE_LAYER_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "sprite.h"

/**
 * A sprite layer class
 * @author Jared Allen
 * @version 8 February 2019
 */

class SpriteLayer
{
public:

  /**
   * Constructor
   * @param sprite the sprite 
   * @param distance the distance
   */
  SpriteLayer( Sprite sprite, uint distance );

  /**
   * move layer to the left
   * @param speed
   */
  void left( uint speed );

  /**
   * move layer to the right
   * @param speed
   */
  void right( uint speed );

  /**
   * reset sprite layer
   */
  void reset();

  /**
   * reset sprite layer
   * @param offset the offset
   */
  void reset( int offset );

  /**
   * draw the sprite layer
   * @param renderer the renderer
   */
  void draw();
  
private:

  Sprite layer_sprite;
  int distance;

};

SpriteLayer::SpriteLayer( Sprite param_sprite, uint param_distance )
: layer_sprite( param_sprite ), distance( param_distance )
{

}

void SpriteLayer::left( uint speed )
{
  if( distance > 0 )
  {
    vector< int > sprite_pos = layer_sprite.get_position();
    layer_sprite.set_position(
      sprite_pos.at( 0 ) - ( speed  / distance ),
      sprite_pos.at( 1 ) );
  }
}

void SpriteLayer::right( uint speed )
{
  if( distance > 0 )
  {
    vector< int > sprite_pos = layer_sprite.get_position();  
    layer_sprite.set_position(
      sprite_pos.at( 0 ) + ( speed / distance ),
      sprite_pos.at( 1 ) );
  }
}

void SpriteLayer::draw()
{
  if( distance > 1 )
  {
    vector< int > coordinates = layer_sprite.get_position();
    SDL_Rect destination;
    destination.x = coordinates.at( 0 );
    destination.y = coordinates.at( 1 );
    destination.w = layer_sprite.get_width() / distance;
    destination.h = layer_sprite.get_height() / distance;
    layer_sprite.draw( destination );
  }
  else
  {
    layer_sprite.draw();
  }
}

void SpriteLayer::reset()
{
  layer_sprite.reset_position();
}

void SpriteLayer::reset( int offset )
{
  if( distance > 0 )
  {
    layer_sprite.reset_position( offset / distance ); 
  }
}



#endif
