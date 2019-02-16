#ifndef SCENE_H
#define SCENE_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "background.h"
#include "character.h"

/**
 * A scene class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Scene
{
public:

  /**
   * plays the scene
   */
  bool play();

  /**
   * resets the scene
   */
  void reset();

  /**
   * adds a following character
   */
  void add_follower( Character character );

  /**
   * sets the scene to the left
   */
  void stage_left();

  /**
   * sets the scene to the right
   */
  void stage_right();

  /**
   * Constructor
   * @param renderer the renderer
   * @param background the background
   * @param characters the characters
   * @param main_character the main character
   * @param speed the speed
   */
  Scene( SDL_Renderer *renderer, Background background,
         vector< Character > characters,
         Character main_character, uint speed );

private:

  /**
   * draw the stationary npcs
   * @param left the direction
   */
  void draw_npcs( bool left );

  /**
   * draw the stationary npcs when standing
   */
  void draw_npcs();

  /**
   * draw the following characters
   * @param left the direction
   */
  void ducklings( bool left );

  /**
   * draw the standing characters
   */
  void ducklings();

  /**
   * update the characters
   * @param left the direction
   */
  void update_characters( bool left );

  /**
   * update the characters
   * @param left the direction
   */
  void update_characters();
  
  SDL_Renderer *renderer;
  Background background;
  static vector< Character > following_characters;
  vector< Character > characters;
  Character main_character;
  uint speed;
  int stage_left_pos;
  int stage_right_pos;

};

void Scene::update_characters( bool left )
{
  draw_npcs( left );
  ducklings( left );
}

void Scene::update_characters()
{
  draw_npcs();
  ducklings();
}

void Scene::ducklings( bool left )
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).update_pos( left, speed );
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed );
    }
    else
    {
      following_characters.at(
        i ).follow( following_characters.at( i - 1 ),
                    speed );
    }
  }
}

void Scene::ducklings()
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed );
    }
    else
    {
      following_characters.at( i ).follow(
        following_characters.at( i - 1 ),
        speed );
    }
  }
}

void Scene::draw_npcs( bool left )
{
  for( uint i = 0; i < characters.size(); i++ )
    {
      characters.at( i ).update_pos( left, speed );
      characters.at( i ).stand();
    }
}

void Scene::draw_npcs()
{
  for( uint i = 0; i < characters.size(); i++ )
    {
      characters.at( i ).stand();
    }
}

vector< Character > Scene::following_characters;

Scene::Scene(SDL_Renderer *param_renderer,
             Background param_background,
             vector< Character > param_characters,
             Character param_main_character, uint param_speed )
: background( param_background ),
  characters( param_characters ),
  main_character( param_main_character ), speed( param_speed ),
  renderer( param_renderer)  
{
  int STAGE_SIZE = 500;
  stage_left_pos = STAGE_SIZE * -1;
  stage_right_pos = STAGE_SIZE;
}

bool Scene::play()
{
  SDL_Event e;
  bool quit = false;
  bool left = false;
  while( !quit )
  {    
    if( main_character.get_position().at( 0 ) > stage_right_pos )
    {
      quit = true;
      left = false;
    }

    if( main_character.get_position().at( 0 ) < stage_left_pos )
    {
      quit = true;
      left = true;
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
        
        SDL_RenderClear( renderer );

        background.left( speed );
        background.draw();
        draw_npcs( false );
        
        main_character.walk_right( speed );
        ducklings( false );
        
        SDL_RenderPresent( renderer );
        SDL_Delay( 200 );
      }
      else if( e.key.keysym.sym == SDLK_LEFT )
      {        
        SDL_RenderClear( renderer );

        background.right( speed );
        background.draw();
        draw_npcs( true );

        main_character.walk_left( speed );
        ducklings( true );
        
        SDL_RenderPresent( renderer );
        SDL_Delay( 200 );
      }
    }
    else
    {
      SDL_RenderClear( renderer );
      background.draw();
      draw_npcs();
      
      main_character.stand();
      ducklings();
      
      SDL_RenderPresent( renderer );
    }
  }
  return left;
}

void Scene::reset()
{
  background.reset();
  main_character.reset();
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset();
  }
}

void Scene::stage_left()
{
  background.reset( stage_right_pos );
  main_character.reset( stage_left_pos );
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset( stage_left_pos );
  }
}

void Scene::stage_right()
{
  background.reset( stage_left_pos );
  main_character.reset( stage_right_pos );
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset( stage_right_pos );
  }
}

void Scene::add_follower( Character character )
{
  following_characters.push_back( character );
}

#endif
