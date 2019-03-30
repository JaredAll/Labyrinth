#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>

using namespace std;

/**
 * A conversation class
 * @author Jared Allen
 * @version 30 March 2019
 */
class Conversation
{
 public:

  /**
   * Constructor
   */
  Conversation();

  /**
   * get dialogue at the index provided
   */
  SDL_Texture* get_dialogue( uint index );

  /**
   * add dialogue to conversation
   */
  void add_dialogue( char* words, SDL_Renderer* renderer );




 private:

  vector< SDL_Texture* > dialogue;



};

#endif
