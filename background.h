#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "sprite_layer.h"

/**
 * A background class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Background
{
public:

  /**
   * Constructor
   * @param layers the sprites that layer the background
   */
  Background( vector < SpriteLayer > layers );

  /**
   * Constructor
   */
  Background();

  /**
   * add a layer to background
   * @param layer
   */
  void add_layer( SpriteLayer layer );

  /**
   * move background left
   */
  void left( uint speed );

  /**
   * move background right
   */
  void right( uint speed );

  /**
   * reset the background
   */
  void reset();

  /**
   * reset the background with offset
   */
  void reset( int offset );

  /**
   * draw the background
   * @param renderer the renderer
   */
  void draw();


private:

  vector< SpriteLayer > layers;

};

Background::Background( vector< SpriteLayer > param_layers )
: layers( param_layers )
{

}

Background::Background()
{
  vector< SpriteLayer > new_layers;
  layers = new_layers;
}

void Background::add_layer( SpriteLayer layer )
{
  layers.push_back( layer );
}

void Background::left( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).left( speed );
  }
}

void Background::right( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).right( speed );
  }
}

void Background::draw()
{
  for( SpriteLayer layer : layers )
  {
    layer.draw();
  }
}

void Background::reset()
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).reset();
  }
}

void Background::reset( int offset )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).reset( offset );
  }
}

#endif
