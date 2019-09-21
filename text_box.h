#ifndef TEXT_BOX
#define TEXT_BOX

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iostream>
#include "cleanup.h"

using namespace std;

/**
 * a class to represent a text box
 * @author Jared Allen
 * @version 1 June 2019
 */
class Text_box
{
public:

  /**
   * constructor
   * @param param_x the x pos
   * @param param_y the y pos
   * @param param_h the height
   * @param param_w the width 
   */
  Text_box( uint param_x, uint param_y, uint param_h,
    uint param_w );

  /**
   * display message on text box
   * @param message the message to be displayed 
   */
  void display( string message, SDL_Renderer *renderer,
                TTF_Font *font, uint letters );
  
private:

  uint x_pos;
  uint y_pos;
  uint height;
  uint width;
  vector< SDL_Rect* > letter_slots;
  SDL_Rect *display_box;
  vector< SDL_Texture *> letter_textures;
  string previous_message;

};

#endif
