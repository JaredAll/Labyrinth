#include "game.h"
#include "scene_states.h"

using namespace std;

Game::Game()
{
  current_scene = 0;
}

Game::~Game()
{
  for(uint i = 0; i < scenes.size(); i++ )
  {
    for( uint j = 0; j < scenes.at( i ).size(); j++ )
    {
      if( scenes.at( i ).at( j ) )
      {
        scenes.at( i ).at ( j ) -> ~Scene();
        scenes.at( i ).at( j ) = NULL;
      }
    }
  }
}

void Game::set_introduction( Panel* panel )
{
  panels.push_back( panel );
}

void Game::add_scene( Scene* scene, uint scene_track )
{
  while( scenes.size() <= scene_track )
  {
    vector< Scene* > track;
    scenes.push_back( track );
  }
  
  scenes.at( scene_track ).push_back( scene );
}

void Game::join_scenes( uint track1_index,
                        uint track2_index,
                        uint scene1_pos,
                        uint scene2_pos,
                        int scene1_junction_pos,
                        int scene2_junction_pos )
{
  scene_links.push_back(
    new SceneJunction(
      track1_index, track2_index, scene1_pos,  scene2_pos,
      scene1_junction_pos, scene2_junction_pos ) );
  
  scenes.at( track1_index )
    .at( scene1_pos )
    -> set_junction( scene1_junction_pos );

  scenes.at( track2_index )
    .at( scene2_pos )
    -> set_junction( scene2_junction_pos );
  
}

void Game::play()
{
  
  bool begin;
  
  Panel* introduction = panels.at( 0 );
  begin = introduction -> display();
  
  if( begin )
  {
    SDL_Event e;
    bool quit = false;
    uint current_track = 1;
    Report report;
    report = { Scene_States::exit_right, 0 };

    while( !quit )
    {
      
      report = scenes
        .at( current_track )
        .at( current_scene )
        -> play();
      
      if( report.status == Scene_States::switch_tracks )
      {
        uint next_scene_pos;
        uint next_track;
        uint next_character_position;
          
        for( uint i = 0; i < scene_links.size(); i++ )
        {
          if( scene_links.at( i )
              -> contains( current_scene, current_track,
                           report.character_position ) )
          {
            next_scene_pos =
              scene_links.at( i ) -> get_next_scene( current_scene,
                                                     current_track );
            
            next_track = scene_links.at( i )
              -> get_next_track( current_scene,
                                 current_track );

            next_character_position =
              scene_links.at( i )
              -> get_next_character_position( current_scene,
                                              current_track );
          }
        }

        int previous_scene_junction_position = scenes
          .at( current_track )
          .at( current_scene )
          -> get_previous_junction_position();

        uint previous_track = current_track;
        uint previous_scene = current_scene;
        current_track = next_track;
        current_scene = next_scene_pos;
        
        scenes
          .at( current_track )
          .at( current_scene )
          -> stage_junction( next_character_position );

        for( uint i = 0; i < scenes.at( previous_track ).size();
             i++ )
        {
          for( uint j = 0; j < scene_links.size(); j++ )
          {
            if( scene_links.at( j )
                -> contains( i, previous_track,
                             report.character_position ) )
            {
              scenes
                .at( previous_track )
                .at( i )
                -> set_previous_junction_position(
                  report.character_position );
            }
          }
        }
        //TODO: check which scenes connect to a given scene and
        //set their previous scene junction positions accordingly.
        //still need to work out kinks so it works in all scenarios.
      }
      else if( report.status == Scene_States::exit_left )
      {
        if( current_scene > 0 )
        {
          current_scene--;
          scenes.at( current_track )
            .at( current_scene )
            -> stage_right();
        }
        else
        {
          scenes.at( current_track )
            .at( current_scene )
            -> stage_left_barrier();
        }
      }
      else if( report.status == Scene_States::exit_right )
      {
        if( current_scene < scenes.at( current_track ).size() - 1 )
        {
          current_scene++;
          scenes.at( current_track )
            .at( current_scene )
            -> stage_left();
        }
        else
        {
          scenes.at( current_track )
            .at( current_scene )
            -> stage_right_barrier();
        }
      }
      else
      {
        quit = true;
      }    
    }
  }
  else
  {
    return;
  }
}
