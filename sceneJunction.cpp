#include "sceneJunction.h"

SceneJunction::SceneJunction( int position )
{
  junction_pos = position;
}

SceneJunction::SceneJunction()
{
  junction_pos = 0;
}

int SceneJunction::get_position()
{
  return junction_pos;
}

void SceneJunction::set_position( int position )
{
  junction_pos = position;
}
