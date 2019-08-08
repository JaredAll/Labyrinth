#ifndef INTERACTION_H
#define INTERACTION_H


#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "cleanup.h"
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
   * Constructor with font size
   */
  Interaction( vector< string > messages,
               int param_scene_position,
               SDL_Renderer* renderer,
               uint font_size );

  /**
   * executes the interaction
   * @param background the background of the scene
   */
  void interact( Background background );

  /**
   * get the scene position
   * @return the scene position
   */
  int get_scene_position();

private:

  /**
   * scroll text in display
   */
  void scroll_text( string message, SDL_Renderer *renderer,
                    TTF_Font *font, Background background );

  Text_box main_display;
  TTF_Font* font;
  SDL_Renderer* renderer;
  vector< string > messages;
  int scene_position;

};

#endif
