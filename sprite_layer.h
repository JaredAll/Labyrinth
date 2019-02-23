#ifndef SPRITE_LAYER_H
#define SPRITE_LAYER_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "sprite.h"

using namespace std;

/**
 * A sprite layer class
 * @author Jared Allen
 * @version 8 February 2019
 */

class SpriteLayer : public Sprite
{
public:

  /**
   * Constructor
   * @param sprite the sprite 
   * @param distance the distance
   */
  SpriteLayer( std::string image_path,
               SDL_Renderer *renderer, int x, int y,
               uint distance );

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

  int distance;

};

#endif
