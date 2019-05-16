#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <fstream>

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
  Conversation( string filepath, SDL_Renderer* renderer );

  /**
   * get dialogue at the index provided
   */
  SDL_Texture* get_dialogue( uint index );

  /**
   * add dialogue to conversation
   */
  void add_dialogue( char* words, SDL_Renderer* renderer );

  /**
   * get length of the dialogue vector
   */
  uint get_length();

  /**
   * set an angry response
   */
  void set_angry_response( char* words, SDL_Renderer* renderer );

  /**
   * get angry response
   */
  SDL_Texture* get_angry_response();




 private:

  vector< SDL_Texture* > dialogue;
  SDL_Texture* angry_response;



};

#endif
