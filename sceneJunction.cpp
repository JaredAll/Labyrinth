#include "sceneJunction.h"

SceneJunction::SceneJunction(  uint track1_index_param,
                               uint track2_index_param,
                               uint scene1_index_param,
                               uint scene2_index_param )
{
  track1_index = track1_index_param;
  track2_index = track2_index_param;
  scene1_index = scene1_index_param;
  scene2_index = scene2_index_param;
}

SceneJunction::SceneJunction()
{
  scene1_index = 0;
  scene2_index = 0;
}

void SceneJunction::link_scenes( uint track1_index_param,
                                 uint track2_index_param,
                                 uint scene1_pos,
                                 uint scene2_pos )
{
  track1_index = track1_index_param;
  track2_index = track2_index_param;
  scene1_index = scene1_pos;
  scene2_index = scene2_pos;
}

uint SceneJunction::get_next_scene( uint track )
{
  return track == track1_index ? scene2_index : scene1_index;
}

uint SceneJunction::get_next_track( uint scene )
{
  return scene == scene1_index ? track2_index : track1_index;
}

bool SceneJunction::contains( uint scene_pos, uint track_pos )
{
  return ( scene_pos == scene1_index || scene_pos == scene2_index )
    && (track_pos == track1_index || track_pos == track2_index );
}
