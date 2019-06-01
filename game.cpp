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

void Game::add_joined_scene( Scene scene )
{
  joined_scenes.push_back( scene );
}

void Game::join_scenes( uint scene1_pos, uint scene2_pos,
                        int scene1_junction_pos,
                        int scene2_junction_pos )
{
  scene_links.push_back(
    SceneJunction(
      scene1_pos,  scene2_pos  ) );
  
  scenes.at( scene1_pos ).set_junction( scene1_junction_pos );
  joined_scenes.at( scene2_pos ).set_junction( scene2_junction_pos );
}

void Game::play()
{
  SDL_Event e;
  bool quit = false;
  bool main_track = true;
  int status = 0;
  while( !quit )
  {
    if( main_track )
    {
      status = scenes.at( current_scene ).play();
    }
    else
    {
      status = joined_scenes.at( current_scene ).play();
    }
    
    if( status == 3 )
    {
      uint next_scene_pos;
      for( uint i = 0; i < scene_links.size(); i++ )
      {
        if( scene_links.at( i ).contains( current_scene ) )
        {
          next_scene_pos =
            scene_links.at( i ).get_next_scene( main_track );
        }
      }

      if( main_track )
      {
        main_track = false;
      }
      else
      {
        main_track = true;
      }
      current_scene = next_scene_pos;
    }
    else if( status == 1 )
    {
      if( main_track )
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
      else
      {
        joined_scenes.at( current_scene ).stage_left();
      }
    }
    else if( status == 0 )
    {
      if( main_track )
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
        joined_scenes.at( current_scene ).stage_right();
      }
    }
    else
    {
      quit = true;
    }    
  }
}
