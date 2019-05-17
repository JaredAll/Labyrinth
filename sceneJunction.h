#ifndef SCENEJUNCTION_H
#define SCENEJUNCTION_H

#include <stdio.h>
#include <iostream>
#include "scene.h"

using namespace std;

/**
 * A scene junction class
 * @author Jared Allen
 * @version 17 May 2019
 */
class SceneJunction
{
public:

  /**
   * Constructor
   * @param position the position of the junction
   */
  SceneJunction( Scene* scene1, Scene* scene2, int position );

  /**
   * default constructor
   */
  SceneJunction();

  /**
   * set the junction position
   */
  void link_scenes( Scene* scene1, Scene* scene2, int position );

  /**
   * get junction position
   */
  int get_position();

private:
  
  int junction_pos;
  Scene* scene1;
  Scene* scene2;


};

#endif
