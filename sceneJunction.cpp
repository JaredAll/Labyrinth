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
  scene2_link_position = scene1_link_position_param;
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

uint SceneJunction::get_next_scene( uint track )
{
  return track == track1_index ? scene2_index : scene1_index;
}

uint SceneJunction::get_next_track( uint scene )
{
  return scene == scene1_index ? track2_index : track1_index;
}

bool SceneJunction::contains( uint scene_pos,
                              uint track_pos,
                              int link_position )
{
  bool is_scene_1 = link_position == scene1_link_position;

  if( is_scene_1 )
  {
    return scene_pos == scene1_index &&
      track_pos == track1_index;
  }
  else
  {
    return scene_pos == scene2_index &&
      track_pos == track2_index;
  }
}
