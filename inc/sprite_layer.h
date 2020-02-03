#ifndef SPRITE_LAYER_H
#define SPRITE_LAYER_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "sprite.h"
#include "render_component.h"

using namespace std;

/**
 * A sprite layer class
 * @author Jared Allen
 * @version 8 February 2019
 */

class SpriteLayer : RenderComponent
{
public:

  /**
   * Constructor
   * @param sprite the sprite 
   * @param distance the distance
   */
  SpriteLayer( Sprite* sprite,
               uint distance );

  /**
   * Destructor
   */
  ~SpriteLayer();

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

  void draw( SDL_Renderer* renderer );
  
private:

  int distance;
  Sprite *sprite;
  SDL_Rect *destination;

};

#endif
