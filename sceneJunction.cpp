#include "sceneJunction.h"

SceneJunction::SceneJunction( Scene* scene1, Scene* scene2,
                              int position )
{
  this -> scene1 = scene1;
  this -> scene2 = scene2;
  junction_pos = position;
}

SceneJunction::SceneJunction()
{
  junction_pos = 0;
  scene1 = nullptr;
  scene2 = nullptr;
}

int SceneJunction::get_position()
{
  return junction_pos;
}

void SceneJunction::link_scenes( Scene* scene1,
                                 Scene* scene2, int position )
{
  this -> scene1 = scene1;
  this -> scene2 = scene2;
  junction_pos = position;
}
