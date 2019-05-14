#ifndef SCRIPT_H
#define SCRIPT_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "conversation.h"
#include "character.h"

using namespace std;

/**
 * A script class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Script
{
 public:

  /**
   * talk to this character
   * @param character the character to speak to
   */
  void speak_to( Character &character );


  
 private:

   vector< Conversation > conversations;



};

#endif
  
