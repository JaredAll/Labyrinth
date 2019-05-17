#include "game.h"

using namespace std;

Game::Game()
{
  vector< Scene > scenes;
  current_scene = 0;
}

void Game::add_scene( Scene scene )
{
  scenes.push_back( scene );
}

void Game::join_scenes( uint scene1_pos, uint scene2_pos,
                        int position )
{
  scene_links.push_back(
    SceneJunction(
      &scenes.at( scene1_pos ), &scenes.at( scene2_pos ),
      position ) );
  
  scenes.at( scene1_pos ).set_junction( position );
  scenes.at( scene2_pos ).set_junction( position );
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
