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
  int play();

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
   * have a conversation with a character
   */
  void convo( uint character_index );

  /**
   * update the scene right
   */
  void right();

  /**
   * update the scene left
   */
  void left();

  /**
   * update the scene center
   */
  void center();

  /**
   * convert npc to follower
   */
  bool recruit();

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

bool Scene::recruit()
{
  uint recruit_proximity = 30;
  uint recruit_index = 0;
  bool found_recruit = false;
  
  for( uint i = 0; i < characters.size(); i++ )
  {
    int distance_from_recruit =
      abs( characters.at( i ).get_position().at( 0 ) -
           main_character.get_position().at( 0 ) );
    if( distance_from_recruit < recruit_proximity )
    {
      recruit_index = i;
      found_recruit = true;
      convo( recruit_index );
    }
  }

  if( found_recruit )
  {
    following_characters.push_back( characters.at( recruit_index ) );
    vector< Character > remaining_characters;
    for( uint i = 0; i < characters.size(); i++ )
    {
      if( i != recruit_index )
      {
        remaining_characters.push_back( characters.at( i ) );
      }
    }
    characters = remaining_characters;
  }
  return found_recruit;
  
}

void Scene::convo( uint character_index )
{
  bool talking = true;
  SDL_Event e;
  while( talking )
  {
    
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_KEYDOWN )
      {
        talking = false;
      }
    }
    
    SDL_RenderClear( renderer );
    background.draw();
    
    characters.at( character_index ).talk();
    
    SDL_RenderPresent( renderer );
  }
}

void Scene::center()
{
  SDL_RenderClear( renderer );
  background.draw();
  draw_npcs();
  
  main_character.stand();
  ducklings();
  
  SDL_RenderPresent( renderer );
}

void Scene::right()
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

void Scene::left()
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

int Scene::play()
{
  SDL_Event e;
  bool push = false;
  int status = 0;
  bool in_bounds = true;
  bool play = true;
  
  while( in_bounds && play )
  {
    if( main_character.get_position().at( 0 ) > stage_right_pos )
    {
      in_bounds = false;
      status = 0;
    }

    if( main_character.get_position().at( 0 ) < stage_left_pos )
    {
      in_bounds = false;
      status = 1;
    }
    
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        status = 2;
        play = false;
      }
      if( e.type == SDL_KEYDOWN )
      {
        push = true;
      }
      else
      {
        push = false;
      }
    }
    
    if( play )
    {
      if( push )
      {
        if( e.key.keysym.sym == SDLK_DOWN )
        {
          recruit();
        }
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
          right();
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {        
          left();
        }
      }
      else
      {
        center();
      }
    }
  }
  return status;
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
