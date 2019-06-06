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

  /* Set Character Sprites */

  uint character_plane_x = 450;
  
  uint doug_x = 500;
  uint doug_y = character_plane_x;

  uint knut_x = 300;
  uint knut_y = character_plane_x - 50;

  uint dirk_x = 500;
  uint dirk_y = character_plane_x;

  uint al_x = 200;
  uint al_y = character_plane_x - 50;
  
  Sprite doug_s =
    Sprite( "sprites/dougsheet.png", ren, doug_x, doug_y );

  Sprite lunius_s = 
        Sprite( "sprites/4knut.png", ren, knut_x, knut_y );

  Sprite dirk_s = Sprite( "sprites/dirkwalk.png", ren, dirk_x,
                               dirk_y );

  Sprite al_s = Sprite( "sprites/walkingAL.png", ren, al_x, al_y );
  
  Sprite knut_faces = Sprite( "sprites/kfaces.png", ren, 400, 0 );
  Sprite doug_faces = Sprite( "sprites/dougFsheet.png", ren, 400,
			      0 );

  doug_s.set_position(
    doug_x, character_plane_x - doug_s.get_height() );

  lunius_s.set_position(
    knut_x, character_plane_x - lunius_s.get_height() );

  dirk_s.set_position(
    dirk_x, character_plane_x - dirk_s.get_height() );

  al_s.set_position(
    al_x, character_plane_x - al_s.get_height() );

  
  /* End Character Sprites */



  
  /* Create Conversations */

  Conversation lunius_s1_c1 =
    Conversation( "convos/lunius_s1_c1.txt", ren );

  Conversation lunius_s1_c2 =
    Conversation( "convos/lunius_s1_c2.txt", ren );
  
  char lunius_angry_response[ 100 ] = "I hate humans.";
  lunius_s1_c1.set_angry_response( lunius_angry_response, ren );
  lunius_s1_c2.set_angry_response( lunius_angry_response, ren);
  
  Conversation doug_s1_c1 =
    Conversation( "convos/doug_s1_c1.txt", ren );
  
  Conversation doug_s1_c2 =
    Conversation( "convos/doug_s1_c2.txt", ren );

  char doug_angry_response[ 100 ] = "I need some oil.";
  doug_s1_c1.set_angry_response( doug_angry_response, ren );
  doug_s1_c2.set_angry_response( doug_angry_response, ren );

  Conversation doug_s2_c1 =
    Conversation( "convos/doug_s2_c1.txt", ren );
  doug_s2_c1.set_angry_response( doug_angry_response, ren );

  Conversation lunius_s2_c1 =
    Conversation( "convos/lunius_s2_c1.txt", ren );
  lunius_s2_c1.set_angry_response( lunius_angry_response, ren );

  Conversation al_s1_c1 =
    Conversation( "convos/al_s1_c1.txt", ren );
  
  /* End Conversations */


  
  /* Create Characters */

  Character doug = Character( "doug",
                              doug_s, doug_faces, 0, 0, 0, 3, 2 );
  
  Character dirk = Character( "dirk",
                              dirk_s, doug_faces, 0, 0, 0,
			      4, 2 );

  Character lunius = Character( "lunius",
                                lunius_s, knut_faces, 0, 0, 0,
				4, 2 );

  Character al = Character( "al", al_s, knut_faces, 0, 0, 0, 4, 2 );
  
  /* End Create Characters */


  
  /* Initialize Backgrounds */

  SpriteLayer backdrop_sprite = SpriteLayer( "sprites/bg1.2.png",
                                             ren, 0, 0, 0 );
  
  SpriteLayer far_town = SpriteLayer( "sprites/town1.png", ren,
                                      400, 150, 2 );
  SpriteLayer near_town = SpriteLayer( "sprites/town1.png", ren,
                                      330, 35, 1 );
  SpriteLayer b_bush_1 = SpriteLayer( "sprites/berrybush.png", ren,
                                      330, 225, 1 );
  SpriteLayer b_bush_2 = SpriteLayer( "sprites/berrybush.png", ren,
                                      330, 225, 2 );
  SpriteLayer b_bush_3 = SpriteLayer( "sprites/berrybush.png", ren,
                                      530, 225, 1 );
  SpriteLayer inn_background_s = SpriteLayer(
    "sprites/bar_inside.png", ren, 0, 0, 0 );
  
  Background background = Background( ren );
  Background trees = Background( ren );
  Background berry_inn = Background( ren );
  Background bar_inside = Background( ren );
  
  berry_inn.add_layer( backdrop_sprite );
  trees.add_layer( backdrop_sprite );
  background.add_layer( backdrop_sprite );
  bar_inside.add_layer( inn_background_s );
  
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
  trees.add_layer( far_town );
  trees.add_layer( near_town );
  
  background.add_layer( b_bush_1 );

  berry_inn.add_layer( far_town );
  berry_inn.add_layer( b_bush_3 );
  berry_inn.add_layer( b_bush_1 );

  bar_inside.add_layer( inn_background_s );
  /* End Backgrounds */

  

  /* Initialize Scenes */

  uint speed = 20;

  vector< Character > characters;
  characters.push_back( doug );

  vector< Character* > character_ps;
  character_ps.push_back( &lunius );
  character_ps.push_back( &doug );
  character_ps.push_back( &al );

  
  vector< Conversation > sketch_1_convos;
  sketch_1_convos.push_back( lunius_s1_c1 );

  Script sketch_script = Script( character_ps );
  sketch_script.insert_recruit_conversation( &lunius, lunius_s1_c1 );
  sketch_script.insert_conversation( &lunius, lunius_s1_c2 );
  sketch_script.insert_recruit_conversation( &doug, doug_s1_c1 );
  sketch_script.insert_conversation( &doug, doug_s1_c2 );
  sketch_script.insert_recruit_conversation( &al, al_s1_c1 );

  Script scene2_script = Script( character_ps );
  scene2_script.insert_recruit_conversation( &doug, doug_s2_c1 );
  scene2_script.insert_recruit_conversation( &lunius, lunius_s1_c1 );
  scene2_script.insert_conversation( &lunius, lunius_s2_c1 );
  scene2_script.insert_recruit_conversation ( &al, lunius_s1_c1 );
  scene2_script.insert_conversation( &al, lunius_s2_c1 );

  uint scene_1_size = 1000;
  uint scene_2_size = 1500;
  uint scene_3_size = 500;

  Scene sketch_1 =
    Scene( ren, background, characters, dirk,
	   sketch_script, speed, scene_1_size );

  vector< Character > ts_chars;
  ts_chars.push_back( lunius );
  
  vector< Character > bi_chars;
  bi_chars.push_back( al );
  
  Scene tree_scene =
    Scene( ren, trees, ts_chars, dirk, scene2_script, speed,
      scene_2_size );

  Scene bush_inn =
    Scene( ren, berry_inn, bi_chars, dirk, scene2_script, speed,
      scene_3_size );

    Scene bush_inn_2 =
    Scene( ren, bar_inside, bi_chars, dirk, scene2_script, speed,
      scene_3_size );

  /* End Scenes */

  
  /* Create Game and Play */

  Game fatty_rolls = Game();
  fatty_rolls.add_scene( sketch_1 );
  fatty_rolls.add_joined_scene( bush_inn );
  fatty_rolls.add_joined_scene( bush_inn_2 );
  fatty_rolls.add_scene( tree_scene );

  fatty_rolls.join_scenes( 1, 0, 600, 0 );
  fatty_rolls.join_scenes( 1, 1, 60, 0 );

  fatty_rolls.play();

  cleanup( ren, win );
  return 1;

}
