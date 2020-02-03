#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "render_component.h"

using namespace std;

/**
 * A sprite class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Sprite : public RenderComponent
{
public:

  /**
   * Constructor
   * @param texture_path the texture file name
   * for the entire texture
   * @param x the x coordinate
   * @param y the y coordinate
   */
  Sprite( std::string image_path,
          int x,
          int y,
          SDL_Texture* sprite_texture );

  /**
   * Destructor
   */
  ~Sprite();

  /**
   * method to change source rectangle
   * @param source the new source
   */
  void set_source( SDL_Rect *source );

  /**
   * method to change destination rectangle
   * @param destination the new destination
   */
  void set_destination( SDL_Rect *destination );

  /**
   * method to draw sprite
   * @param renderer the pointer to renderer
   */
  void draw( SDL_Renderer* renderer );

  /**
   * method to draw sprite
   * @param renderer the pointer to renderer
   * @param destination the destination to be drawn to
   */
  void draw( SDL_Rect *destination );

  /**
   * method to draw mirror sprite
   * @param renderer the pointer to the renderer
   */
  void flip_draw();

  /**
   * method to draw mirror sprite
   * @param renderer the pointer to the renderer
   * @param destination the destination for sprite
   */
  void flip_draw( SDL_Rect *destination );
  /** 
   * method to change sprite position
   * @param new_x the new x coordinate
   * @param new_y the new y coordinate
   */
  void set_position( int new_x, int new_y );

  /**
   * method to change sprite position
   * @param new_x the new x coordinate
   */
  void set_position( int new_x );
  
  /** 
   * method to reset sprite position
   */
  void reset_position();

  /**
   * method to reset sprite position with offset
   * @param offset the offset
   */
  void reset_position( int offset );

  /** 
   * method to get sprite x position
   */
  int get_x();

  /** 
   * method to get sprite y position
   */
  int get_y();
  
  /**
   * get the sprite's height
   */
  int get_height();

  /**
   * get the sprite's width
   */
  int get_width();


private:

  SDL_Texture *sprite_texture;
  SDL_Rect *source;
  SDL_Renderer *renderer;
  SDL_Rect *destination;
  int initial_x;
  int initial_y;
  int x;
  int y;

};



#endif
