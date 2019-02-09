#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "background.h"

using namespace std;

int main( int argc, char* argv[] )
{

  //initialize video
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    logSDLError( std::cout, "SDL_Init" );
    return 1;
  }


  //create window
  int window_width = 800;
  int window_height = 500;
  SDL_Window *win = SDL_CreateWindow("Labyrinth sketch 1",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_width, window_height,
                                     SDL_WINDOW_SHOWN);
  if (win == nullptr)
  {
    logSDLError( std::cout, "CreateWindow" );
    SDL_Quit();
    return 1;
  }

  //create renderer
  SDL_Renderer *ren =
    SDL_CreateRenderer(win, -1,
                       SDL_RENDERER_ACCELERATED
                       | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr)
  {
    cleanup( win );
    logSDLError( std::cout, "CreateRenderer" );
    SDL_Quit();
    return 1;
  }

  //get the background
  Background background = Background();
  Sprite backdrop_sprite = Sprite( "background1.png", ren, 0, 0 );
  SpriteLayer backdrop_layer = SpriteLayer( backdrop_sprite, 0 );

  uint fatty_x = 400;
  uint fatty_y = 270;
  Sprite fatty = Sprite( "fattysheet.png", ren, fatty_x, fatty_y );

  uint fatty2_x = 1600;
  uint fatty2_y = 230;
  Sprite fatty_2 = Sprite( "fattysheet.png", ren, fatty2_x, fatty2_y );

  
  int sign_x = 400;
  int sign_y = 150;
  Sprite sign = Sprite( "fattysign.png", ren, sign_x, sign_y );

  Sprite sign2 = Sprite( "fattysign.png", ren, 330, 130 );

  SpriteLayer l_sign = SpriteLayer( sign, 1 );
  SpriteLayer next_sign = SpriteLayer( sign2, 2 );
  SpriteLayer third_layer = SpriteLayer( sign2, 4 );

  background.add_layer( backdrop_layer );
  background.add_layer( third_layer );
  background.add_layer( next_sign );
  background.add_layer( l_sign );

  int sign_offset = 0;

  //clip sheet for fatty walking
  uint fatty_clip_width = 100;
  uint fatty_clip_height = 200;
  
  uint num_sprites = 2;
  vector< SDL_Rect > fatty_walks;
  for( uint i = 0; i < num_sprites; i++ )
  {
    SDL_Rect fatty_clip;
    fatty_walks.push_back( fatty_clip );
    fatty_walks.at( i ).x = i * ( fatty_clip_width );
    fatty_walks.at( i ).y = 0;
    fatty_walks.at( i ).h = fatty_clip_height;
    fatty_walks.at( i ).w = fatty_clip_width;
  }

  uint fatty_stands = 0;
  fatty_2.set_source( &fatty_walks.at( 1 ) );
  uint speed = 20;

  //render until click the x
  uint x_pos = 0;
  uint y_pos = 0;
  
  SDL_Event e;
  bool quit = false;
  bool left = true;
  uint steps = 0;
  while( !quit )
  {
    if( sign_offset > window_width || sign_offset < ( window_width * -1 ) )
    {
      sign_offset = 0;
    }
    
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
    }
    if( e.type == SDL_KEYDOWN )
    {
      if( e.key.keysym.sym == SDLK_RIGHT )
      {
        fatty_stands = ( fatty_stands + 1 ) % 2;
        
        SDL_RenderClear( ren );

        background.left( speed );
        background.draw();
        
        fatty.set_source( &fatty_walks.at( fatty_stands ) );
        fatty.draw();

        fatty2_x -= speed;
        fatty_2.set_position( fatty2_x, fatty2_y );
        fatty_2.draw();
        
        SDL_RenderPresent( ren );
        SDL_Delay( 250 );
        left = false;
      }
      else if( e.key.keysym.sym == SDLK_LEFT )
      {
        fatty_stands = ( fatty_stands + 1 ) % 2;
        
        SDL_RenderClear( ren );

        background.right( speed );
        background.draw();

        fatty2_x += speed;
        fatty_2.set_position( fatty2_x, fatty2_y );
        fatty_2.draw();

        fatty.set_source( &fatty_walks.at( fatty_stands ) );
        fatty.flip_draw();
        
        SDL_RenderPresent( ren );
        SDL_Delay( 250 );
        left = true;
      }
    }
    else
    {
      fatty_stands = 1;
      SDL_RenderClear( ren );
      background.draw();
      
      fatty.set_source( &fatty_walks.at( fatty_stands ) );

      if( left )
      {
        fatty.flip_draw();
      }
      else
      {
        fatty.draw();
      }

      fatty_2.draw();
      SDL_RenderPresent( ren );
    }
    steps++;
  }
  cleanup( ren, win );
  return 1;
  
}
