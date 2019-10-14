#ifndef PANEL_H
#define PANEL_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <climits>
#include "scene.h"
#include "background.h"
#include "character.h"
#include "conversation.h"
#include "script.h"
#include "text_box.h"
#include <unistd.h>

using namespace std;

/**
 * A panel class
 * @author Jared Allen
 * @version 5 July 2019
 */
class Panel
{
public:

  /**
   * Constructor
   */
  Panel( Background *background,
         SDL_Renderer* renderer);

  /**
   * displays the panel
   */
  bool display();
  
private:

  Text_box *main_display;
  Text_box *sub_display;
  TTF_Font* font;
  SDL_Renderer* renderer;
  Background* background;

};

#endif
