#ifndef SCRIPT_H
#define SCRIPT_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "conversation.h"
#include "character.h"
#include <map>
#include <climits>

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
   * Constructor
   */
  Script( vector< Character* > characters );

  /**
   * talk to this character
   * @param character the character to speak to
   * @return the conversation to be had
   */
  Conversation* speak_to( Character* character );

  /**
   * insert new conversation into a character's dialogue
   * @param character the character pointer
   * @param conversation the conversation pointer
   */
  void insert_conversation( Character* character, Conversation
			    *conversation );

  /**
   * insert recruitment conversation into a character's dialogue
   * @param character the character pointer
   * @param conversation the conversation pointer
   */
  void insert_recruit_conversation(
    Character* character,
    Conversation *conversation );

  
 private:

  vector< Character* > characters;
  map< Character*, vector< Conversation* > > conversations;
  map< Character*, Conversation* > recruit_conversations;
  map< Character*, uint > lines;


};

#endif
  
