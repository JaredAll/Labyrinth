#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "game.h"

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
  int window_width = 1000;
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
  SpriteLayer backdrop_sprite = SpriteLayer( "bg1.2.png", ren,
                                             0, 0, 0 );


  uint fatty_x = 500;
  uint fatty_y = 290;

  uint doug_x = 500;
  uint doug_y = 350;

  uint knut_x = 300;
  uint knut_y = 290;
  
  Sprite fatty = Sprite( "fattysheet.png", ren, fatty_x, fatty_y );
  Sprite doug_s =
    Sprite( "dougsheet.png", ren, doug_x, doug_y );

  Sprite Lun_Knut = 
        Sprite( "luniusknut_sheet2.png", ren, knut_x, knut_y );
  
  Sprite faces = Sprite( "facesheet.png", ren, 400, 0 );

  Character lunius = Character( Lun_Knut, faces, 0, 0, 0, 3, 2 );

  Character fatso = Character( fatty, faces, 0, 0, 0, 2, 2 );

  uint fatty2_x = 300;
  uint fatty2_y = 275;
  Sprite fatty_2 =
    Sprite( "fattysheet.png", ren, fatty2_x, fatty2_y );

  Character fatso2 = Character( fatty, faces, 0, 0, 0, 2, 2 );

  Character fatso3 = Character( fatty, faces, 0, 0, 0, 2, 2 );

  Character doug = Character( doug_s, faces, 0, 0, 0, 3, 2 );
  Character doug2 = Character( doug_s, faces, 0, 0, 0, 3, 2 );
  doug2.set_screen_position( 600, 330 );
  
  int sign_x = 400;
  int sign_y = 150;
  SpriteLayer l_sign = SpriteLayer( "fattysign.png", ren,
                               sign_x, sign_y, 1 );

  SpriteLayer next_sign = SpriteLayer( "fattysign.png", ren,
                                  330, 130, 2 );
  SpriteLayer third_layer = SpriteLayer( "fattysign.png", ren,
                                         330, 130, 4 );
  SpriteLayer l_tree_1 = SpriteLayer( "inn-01.png", ren,
                                      400, 150, 2 );
  SpriteLayer l_tree_2 = SpriteLayer( "inn-01.png", ren,
                                      330, 75, 1 );

  Background trees = Background();
  trees.add_layer( backdrop_sprite );

  background.add_layer( backdrop_sprite );
  
  int num_grounds = 2;
  for( int i = num_grounds * ( -1 ); i < num_grounds; i++ )
  {
    uint ground_y = 0;
    uint ground_x = 0 + 1000 * i;
    SpriteLayer ground = SpriteLayer( "grass1.png", ren,
                                    ground_x, ground_y, 1 );
    background.add_layer( ground );
    trees.add_layer( ground );
  }

  trees.add_layer( l_tree_1 );
  trees.add_layer( l_tree_2 );
  
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

  vector< Character > characters;
  characters.push_back( fatso );
  characters.push_back( lunius );
  //characters.push_back( doug2 );

  Scene sketch_1 =
    Scene( ren, background, characters, doug, speed );

  characters.clear();
  Scene tree_scene =
    Scene( ren, trees, characters, doug, speed );

  //tree_scene.add_follower( fatso2 );
  //tree_scene.add_follower( fatso3 );

  Game fatty_rolls = Game();
  fatty_rolls.add_scene( sketch_1 );
  fatty_rolls.add_scene( tree_scene );

  fatty_rolls.play();

  cleanup( ren, win );
  return 1;

}
