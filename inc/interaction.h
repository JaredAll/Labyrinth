#ifndef INTERACTION_H
#define INTERACTION_H


#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <climits>
#include "background.h"
#include "character.h"
#include "conversation.h"
#include "script.h"
#include "text_box.h"
#include <unistd.h>

using namespace std;

/**
 * An interaction class
 * @auther Jared Allen
 * @version 20 July 2019
 */
class Interaction
{
public:

  /**
   * Constructor
   */
  Interaction( vector< string > messages,
               int param_scene_position,
               SDL_Renderer* renderer );

  /**
   * get the scene position
   * @return the scene position
   */
  int get_scene_position();

  /**
   * get the length of the interaction
   * @return the length of the interaction
   */
  uint get_interaction_length();

  /**
   * get the message at the given position
   * @param index the index of the message
   * @return the message
   */
  string get_message( uint index );

private:

  Text_box main_display;
  TTF_Font* font;
  SDL_Renderer* renderer;
  vector< string > messages;
  int scene_position;

};

#endif
