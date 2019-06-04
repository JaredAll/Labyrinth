#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "easy_sdl.h"
#include "game.h"

using namespace std;

int main( int argc, char* argv[] )
{

  /* Setup Window */

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

  /* End Window Setup */

  //get the background
  Background background = Background();
  SpriteLayer backdrop_sprite = SpriteLayer( "sprites/bg1.2.png", ren,
                                             0, 0, 0 );

  /* Set Character Sprites */
  
  uint doug_x = 500;
  uint doug_y = 350;

  uint knut_x = 300;
  uint knut_y = 330;

  uint dirk_x = 500;
  uint dirk_y = 330;

  uint al_x = 700;
  uint al_y = 330;
  
  Sprite doug_s =
    Sprite( "sprites/dougsheet.png", ren, doug_x, doug_y );

  Sprite Lun_Knut = 
        Sprite( "sprites/4knut.png", ren, knut_x, knut_y );

  Sprite Dirk_sprite = Sprite( "sprites/dirkwalk.png", ren, dirk_x,
                               dirk_y );

  Sprite Al_sprite = Sprite( "sprites/walkingAL.png", ren, al_x, al_y );
  
  Sprite knut_faces = Sprite( "sprites/kfaces.png", ren, 400, 0 );
  Sprite doug_faces = Sprite( "sprites/dougFsheet.png", ren, 400,
			      0 );

  /* End Character Sprites */



  
  /* Create Conversations */

  Conversation lunius_convo =
    Conversation( "lunius_conversation.txt", ren );

  Conversation lunius_s1_c2 =
    Conversation( "lunius_s1_c2.txt", ren );
  
  char lunius_angry_response[ 100 ] = "I hate humans.";
  lunius_convo.set_angry_response( lunius_angry_response, ren );

  lunius_s1_c2.set_angry_response( lunius_angry_response, ren);
  
  Conversation doug_convo =
    Conversation( "doug_conversation.txt", ren );
  Conversation doug_c2 =
    Conversation( "doug_c2.txt", ren );

  char doug_angry_response[ 100 ] = "I need some oil.";
  doug_convo.set_angry_response( doug_angry_response, ren );

  doug_c2.set_angry_response( doug_angry_response, ren );

  Conversation doug_s2_c1 =
    Conversation( "doug_scene2.txt", ren );
  doug_s2_c1.set_angry_response( doug_angry_response, ren );

  Conversation lunius_s2 =
    Conversation( "lunius_scene2.txt", ren );
  lunius_s2.set_angry_response( lunius_angry_response, ren );

  Conversation al_s1_c1 =
    Conversation( "al_s1_c1.txt", ren );
  

  /* End Conversations */


  
  /* Create Characters */

  Character doug = Character( "doug",
                              doug_s, doug_faces, 0, 0, 0, 3, 2 );
  
  Character dirk = Character( "dirk",
                              Dirk_sprite, doug_faces, 0, 0, 0,
			      4, 2 );

  Character lunius = Character( "lunius",
                                Lun_Knut, knut_faces, 0, 0, 0,
				4, 2 );

  Character al = Character( "al", Al_sprite, knut_faces, 0, 0, 0, 4, 2 );
  
  dirk.set_screen_position( 500, 330 );

  /* End Create Characters */


  
  /* Initialize Backgrounds */
  
  int sign_x = 400;
  int sign_y = 150;
  SpriteLayer l_sign = SpriteLayer( "sprites/fattysign.png", ren,
                               sign_x, sign_y, 1 );

  SpriteLayer next_sign = SpriteLayer( "sprites/fattysign.png", ren,
                                  330, 130, 2 );
  SpriteLayer third_layer = SpriteLayer( "sprites/fattysign.png", ren,
                                         330, 130, 4 );
  SpriteLayer l_tree_1 = SpriteLayer( "sprites/town1.png", ren,
                                      400, 150, 2 );
  SpriteLayer l_tree_2 = SpriteLayer( "sprites/town1.png", ren,
                                      330, 75, 1 );
  SpriteLayer b_bush_1 = SpriteLayer( "sprites/berrybush.png", ren,
                                      330, 225, 1 );
  SpriteLayer b_bush_2 = SpriteLayer( "sprites/berrybush.png", ren,
                                      330, 225, 2 );
  SpriteLayer b_bush_3 = SpriteLayer( "sprites/berrybush.png", ren,
                                      530, 225, 1 );

  Background trees = Background();
  Background berry_inn = Background();

  berry_inn.add_layer( backdrop_sprite );
  trees.add_layer( backdrop_sprite );

  background.add_layer( backdrop_sprite );
  
  int num_grounds_2 = 4;
  for( int i = num_grounds_2 * ( -1 ); i < num_grounds_2; i++ )
  {
    uint ground_y = 110;
    uint ground_x = 0 + 500 * i;
    SpriteLayer ground_2 = SpriteLayer( "sprites/grass1.png", ren,
                                    ground_x, ground_y, 2 );
    SpriteLayer ground_2_c = SpriteLayer ( "sprites/grass1.png", ren,
                                           ground_x, 160, 2 );
    trees.add_layer( ground_2 );
    trees.add_layer( ground_2_c );
    berry_inn.add_layer( ground_2 );
    berry_inn.add_layer( ground_2_c );
  }

  int num_grounds = 2;
  for( int i = num_grounds * ( -1 ); i < num_grounds; i++ )
  {
    uint ground_y = 0;
    uint ground_x = 0 + 1000 * i;
    SpriteLayer ground = SpriteLayer( "sprites/grass1.png", ren,
                                    ground_x, ground_y, 1 );
    SpriteLayer ground_2 = SpriteLayer( "sprites/grass1.png", ren,
                                    ground_x, ground_y, 2 );
    background.add_layer( ground );
    trees.add_layer( ground );
    berry_inn.add_layer( ground );
  }

  
  trees.add_layer( b_bush_2 );
  trees.add_layer( l_tree_1 );
  trees.add_layer( l_tree_2 );
  
  background.add_layer( third_layer );
  background.add_layer( next_sign );
  background.add_layer( l_sign );
  background.add_layer( b_bush_1 );

  berry_inn.add_layer( l_tree_1 );
  berry_inn.add_layer( b_bush_3 );
  berry_inn.add_layer( b_bush_1 );

  /* End Backgrounds */

  

  /* Initialize Scenes */

  uint speed = 20;

  vector< Character > characters;
  characters.push_back( lunius );
  characters.push_back( doug );
  characters.push_back( al );

  vector< Character* > character_ps;
  character_ps.push_back( &lunius );
  character_ps.push_back( &doug );
  character_ps.push_back( &al );

  vector< Conversation > sketch_1_convos;
  sketch_1_convos.push_back( lunius_convo );

  Script sketch_script = Script( character_ps );
  sketch_script.insert_conversation( &lunius, lunius_convo );
  sketch_script.insert_conversation( &lunius, lunius_s1_c2 );
  sketch_script.insert_conversation( &doug, doug_convo );
  sketch_script.insert_conversation( &doug, doug_c2 );
  sketch_script.insert_conversation( &al, al_s1_c1 );

  Script scene2_script = Script( character_ps );
  scene2_script.insert_conversation( &doug, doug_s2_c1 );
  scene2_script.insert_conversation( &lunius, lunius_s2 );

  uint scene_1_size = 1000;
  uint scene_2_size = 1500;
  uint scene_3_size = 500;

  Scene sketch_1 =
    Scene( ren, background, characters, dirk,
	   sketch_script, speed, scene_1_size );

  characters.clear();
  
  Scene tree_scene =
    Scene( ren, trees, characters, dirk, scene2_script, speed,
      scene_2_size );

  Scene bush_inn =
    Scene( ren, berry_inn, characters, dirk, scene2_script, speed,
      scene_3_size );

  /* End Scenes */

  
  /* Create Game and Play */

  Game fatty_rolls = Game();
  fatty_rolls.add_scene( sketch_1 );
  fatty_rolls.add_joined_scene( bush_inn );
  fatty_rolls.add_scene( tree_scene );
  //fatty_rolls.add_scene( bush_inn );

  fatty_rolls.join_scenes( 0, 0, 300, 0 );

  fatty_rolls.play();

  cleanup( ren, win );
  return 1;

}
