#include "sceneJunction.h"

SceneJunction::SceneJunction( uint scene1_index_param,
                              uint scene2_index_param )
{
  scene1_index = scene1_index_param;
  scene2_index = scene2_index_param;
}

SceneJunction::SceneJunction()
{
  scene1_index = 0;
  scene2_index = 0;
}

void SceneJunction::link_scenes( uint scene1_pos,
                                 uint scene2_pos )
{
  scene1_index = scene1_pos;
  scene2_index = scene2_pos;
}

uint SceneJunction::get_next_scene( bool main_scene )
{
  if( main_scene )
  {
    return scene2_index;
  }
  else
  {
    return scene1_index;
  }
}

bool SceneJunction::contains( uint scene_pos )
{
  return ( scene_pos == scene1_index || scene_pos == scene2_index );
}
