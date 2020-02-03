#include "sprite.h"
#include "easy_sdl.h"

Sprite::Sprite( std::string image_path,
                int param_x,
                int param_y,
                SDL_Texture* sprite_texture )
  : x( param_x ), y( param_y )
{
  source = NULL;
  destination = new SDL_Rect();
  this -> sprite_texture = sprite_texture;
  initial_x = x;
  initial_y = y;
}

Sprite::~Sprite()
{
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

void Sprite::set_position( int new_x )
{
  x = new_x;
}

void Sprite::draw( SDL_Rect *destination )
{
  renderTexture( sprite_texture, renderer, destination, source );
}

void Sprite::draw( SDL_Renderer* renderer )
{  
  renderTexture( sprite_texture, renderer, x, y, source, destination );
}

void Sprite::flip_draw()
{
  renderTextureFlip( sprite_texture, renderer, x, y, source );
}

void Sprite::flip_draw( SDL_Rect *destination )
{
  renderTextureFlip( sprite_texture, renderer, destination, source );
}

int Sprite::get_x()
{
  return x;
}

int Sprite::get_y()
{
  return y;
}


void Sprite::reset_position()
{
  x = initial_x;
  y = initial_y;
}

void Sprite::reset_position( int new_x )
{
  x = initial_x + new_x;
  y = initial_y;
}
