#include "sceneJunction.h"

SceneJunction::SceneJunction(  uint track1_index_param,
                               uint track2_index_param,
                               uint scene1_index_param,
                               uint scene2_index_param,
                               int scene1_link_position_param,
                               int scene2_link_position_param)
{
  track1_index = track1_index_param;
  track2_index = track2_index_param;
  scene1_index = scene1_index_param;
  scene2_index = scene2_index_param;
  scene1_link_position = scene1_link_position_param;
  scene2_link_position = scene2_link_position_param;
}

SceneJunction::SceneJunction()
{
  track1_index = 0;
  track2_index = 0;
  scene1_index = 0;
  scene2_index = 0;
  scene1_link_position = 0;
  scene2_link_position = 0;
}

void SceneJunction::link_scenes( uint track1_index_param,
                                 uint track2_index_param,
                                 uint scene1_index_param,
                                 uint scene2_index_param,
                                 int scene1_link_position_param,
                                 int scene2_link_position_param)
{
  track1_index = track1_index_param;
  track2_index = track2_index_param;
  scene1_index = scene1_index_param;
  scene2_index = scene2_index_param;
  scene1_link_position = scene1_link_position_param;
  scene2_link_position = scene2_link_position_param;
}

uint SceneJunction::get_next_scene( uint scene, uint track )
{
  uint next_scene;
  if( track == track1_index )
  {
    if( scene == scene1_index )
    {
      next_scene = scene2_index;
    }
  }
  else
  {
    next_scene = scene1_index;
  }
  return next_scene;
}

uint SceneJunction::get_next_track( uint scene, uint track )
{
  uint next_track;
  if( scene == scene1_index )
  {
    if( track == track1_index )
    {
      next_track = track2_index;
    }
  }
  else
  {
    next_track = track1_index;
  }
  return next_track;
}

bool SceneJunction::contains( uint scene_pos,
                              uint track_pos,
                              int link_position )
{
  int junction_proximity = 60;
  return ( abs( link_position - scene1_link_position ) <
           junction_proximity &&
           scene_pos == scene1_index &&
           track_pos == track1_index ) ||
    ( abs( link_position - scene2_link_position ) <
      junction_proximity
      && scene_pos == scene2_index &&
      track_pos == track2_index );
}

int SceneJunction::get_next_character_position( uint scene,
                                                uint track )
{
  int next_character_position;
  if( track == track1_index )
  {
    if( scene == scene1_index )
    {
      next_character_position = scene2_link_position;
    }
  }
  else
  {
    next_character_position = scene1_link_position;
  }
  return next_character_position;
}

