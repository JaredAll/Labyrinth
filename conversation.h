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
   * default constructor
   */
  Conversation();
  
  /**
   * get dialogue at the index provided
   */
  string get_dialogue( uint index );

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
  string get_angry_response();




 private:

  vector< string > dialogue;
  string angry_response;



};

#endif
