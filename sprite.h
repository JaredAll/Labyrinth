#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "easy_sdl.h"

/**
 * A sprite class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Sprite
{
public:

  /**
   * Constructor
   * @param texture_path the texture file name
   * for the entire texture
   * @param x the x coordinate
   * @param y the y coordinate
   */
  Sprite( std::string image_path, SDL_Renderer *renderer,
          int x, int y );

  /**
   * method to change source rectangle
   * @param source the new source
   */
  void set_source( SDL_Rect *source );

  /**
   * method to change destination rectangle
   * @param destination the new destination
   */
  void set_destination( SDL_Rect destination );

  /**
   * method to draw sprite
   * @param renderer the pointer to renderer
   */
  void draw();

  /**
   * method to draw sprite
   * @param renderer the pointer to renderer
   * @param destination the destination to be drawn to
   */
  void draw( SDL_Rect destination );

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
  void flip_draw( SDL_Rect destination );

  /** 
   * method to change sprite position
   * @param new_x the new x coordinate
   * @param new_y the new y coordinate
   */
  void set_position( int new_x, int new_y );

  /** 
   * method to get sprite position
   */
  vector< int > get_position();

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
  int x;
  int y;

};

Sprite::Sprite( std::string image_path,
                SDL_Renderer *param_renderer,
                int param_x, int param_y )
: renderer( param_renderer ), x( param_x ), y( param_y )
{
  source = NULL;
  sprite_texture = loadTexture( image_path, renderer );
}

int Sprite::get_height()
{
  int sprite_height = 0;
  int sprite_width = 0;
  SDL_QueryTexture( sprite_texture, NULL, NULL, &sprite_width,
                    &sprite_height );
  return sprite_height;
}

int Sprite::get_width()
{
  int sprite_height = 0;
  int sprite_width = 0;
  SDL_QueryTexture( sprite_texture, NULL, NULL, &sprite_width,
                    &sprite_height );
  return sprite_width;
}


void Sprite::set_source( SDL_Rect *param_source )
{
  source = param_source;
}

void Sprite::set_position( int new_x, int new_y )
{
  x = new_x;
  y = new_y;
}

void Sprite::draw( SDL_Rect destination )
{
  renderTexture( sprite_texture, renderer, destination, source );
}

void Sprite::draw()
{
  renderTexture( sprite_texture, renderer, x, y, source );
}

void Sprite::flip_draw()
{
  renderTextureFlip( sprite_texture, renderer, x, y, source );
}

void Sprite::flip_draw( SDL_Rect destination )
{
  renderTextureFlip( sprite_texture, renderer, destination, source );
}

vector< int > Sprite::get_position()
{
  vector< int > coordinates;
  coordinates.push_back( x );
  coordinates.push_back( y );
  return coordinates;
}

#endif
