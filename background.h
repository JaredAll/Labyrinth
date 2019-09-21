#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "sprite_layer.h"

using namespace std;

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
  Background( vector < SpriteLayer* > layers, SDL_Renderer *ren );

  /**
   * Constructor
   */
  Background( SDL_Renderer *ren );

  /**
   * Destructor
   */
  ~Background();

  /**
   * add a layer to background
   * @param layer
   */
  void add_layer( SpriteLayer *layer );

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

  /**
   * draw a blank background 
   */
  void blank();


private:

  vector< SpriteLayer* > layers;
  SpriteLayer *blank_screen;

};

#endif
