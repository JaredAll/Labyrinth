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
  SceneJunction( uint scene1_index, uint scene2_index );

  /**
   * default constructor
   */
  SceneJunction();

  /**
   * set the junction position
   */
  void link_scenes( uint scene1_index,
                    uint scene2_index );

  /**
   * get next scene
   * @param main_scene whether the scene is on the main track
   * or not
   */
  uint get_next_scene( bool main_scene );

  /**
   * determine whether sceneJunction contains a scene
   */
  bool contains( uint scene_pos );
  
private:

  uint scene1_index;
  uint scene2_index;


};

#endif
