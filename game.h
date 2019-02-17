#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "scene.h"

/**
 * A game class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Game
{
public:

  /**
   * Constructer
   */
  Game();

  /**
   * plays the game
   */   
  void play();

  /**
   * add scene to game
   */
  void add_scene( Scene scene );


private:

  vector< Scene > scenes;
  uint current_scene;

};

Game::Game()
{
  vector< Scene > scenes;
  current_scene = 0;
}

void Game::add_scene( Scene scene )
{
  scenes.push_back( scene );
}

void Game::play()
{
  SDL_Event e;
  bool quit = false;
  int status = 0;
  while( !quit )
  {
    status = scenes.at( current_scene ).play();
    if( status == 1 )
    {
      if( current_scene > 0 )
      {
        current_scene--;
        scenes.at( current_scene ).stage_right();
      }
      else
      {
        scenes.at( current_scene ).stage_left();
      }
    }
    else if( status == 0 )
    {
      if( current_scene < scenes.size() - 1 )
      {
        current_scene++;
        scenes.at( current_scene ).stage_left();
      }
      else
      {
        scenes.at( current_scene ).stage_right();
      }
    }
    else
    {
      quit = true;
    }    
  }
}

#endif
