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

  SDL_Renderer *renderer;
  Background background;
  vector< Character > following_characters;
  Character main_character;
  uint speed;
  int stage_left_pos;
  int stage_right_pos;

};

Scene::Scene(SDL_Renderer *param_renderer,
             Background param_background,
             vector< Character > param_following_characters,
             Character param_main_character, uint param_speed )
: background( param_background ),
  following_characters( param_following_characters ),
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
  bool left;
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
        
        main_character.walk_right( speed );
        for( uint i = 0; i < following_characters.size(); i++ )
        {
          following_characters.at( i ).update_pos( false, speed );
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
        
        SDL_RenderPresent( renderer );
        SDL_Delay( 200 );
      }
      else if( e.key.keysym.sym == SDLK_LEFT )
      {        
        SDL_RenderClear( renderer );

        background.right( speed );
        background.draw();

        main_character.walk_left( speed );
        for( uint i = 0; i < following_characters.size(); i++ )
        {
          following_characters.at( i ).update_pos( true, speed );
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
        
        SDL_RenderPresent( renderer );
        SDL_Delay( 200 );
      }
    }
    else
    {
      SDL_RenderClear( renderer );
      background.draw();

      main_character.stand();
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

#endif
