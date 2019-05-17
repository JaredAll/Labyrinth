#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "scene.h"
#include "sceneJunction.h"
#include <map>

using namespace std;

/**
 * A game class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Game
{
public:

  /**
   * Constructer
   */
  Game();

  /**
   * plays the game
   */   
  void play();

  /**
   * add scene to game
   */
  void add_scene( Scene scene );

  /**
   * join two scenes
   * @param scene1 the first scene
   * @param scene2 the second scene
   */
  void join_scenes( uint scene1_pos, uint scene2_pos,
                    int position );


private:

  vector< Scene > scenes;
  vector< SceneJunction > scene_links;
  uint current_scene;

};

#endif
