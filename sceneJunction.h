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
  SceneJunction( uint track1_index,
                 uint track2_index,
                 uint scene1_index,
                 uint scene2_index,
                 int scene1_link_position,
                 int scene2_link_position );

  /**
   * default constructor
   */
  SceneJunction();

  /**
   * set the junction position
   */
  void link_scenes( uint track1_index,
                    uint track2_index,
                    uint scene1_index,
                    uint scene2_index,
                    int scene1_link_position,
                    int scene2_link_position );

  /**
   * get next scene
   * @param track the track of the next scene
   * or not
   */
  uint get_next_scene( uint track );

  /**
   * get next track
   * @param scene the scene of the current track
   * or not
   */
  uint get_next_track( uint scene );

  /**
   * determine whether sceneJunction contains a scene
   */
  bool contains( uint scene_pos, uint track_pos, int link_position );
  
private:

  uint track1_index;
  uint track2_index;
  uint scene1_index;
  uint scene2_index;
  int scene1_link_position;
  int scene2_link_position;


};

#endif
