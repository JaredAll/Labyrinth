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
  bool left;
  while( !quit )
  {
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }
    }

    left = scenes.at( current_scene ).play();
    if( left )
    {
      if( current_scene > 0 )
      {
        current_scene--;
        scenes.at( current_scene ).stage_right();
      }
    }
    else
    {
      if( current_scene < scenes.size() - 1 )
      {
        current_scene++;
        scenes.at( current_scene ).stage_left();
      }
    }
  }
}

#endif
