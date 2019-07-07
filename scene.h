#ifndef SCENE_H
#define SCENE_H

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
 * A scene class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Scene
{
public:

  /**
   * plays the scene
   */
  int play();

  /**
   * resets the scene
   */
  void reset();

  /**
   * adds a following character
   */
  void add_follower( Character character );

  /**
   * sets the scene to the left
   */
  void stage_left();

  /**
   * sets the scene to the right
   */
  void stage_right();

  /**
   * adds conversation to scene
   */
  void add_conversation( Conversation conversation );

  /**
   * Constructor
   * @param renderer the renderer
   * @param background the background
   * @param characters the characters
   * @param main_character the main character
   * @param speed the speed
   */
  Scene( SDL_Renderer *renderer, Background background,
         vector< Character > characters,
         Character main_character,
	 Script scene_dialogue,
	 uint speed,
         uint stage_size );

  /**
   * set scene junction
   * @param pos the junction position
   */
  void set_junction( int position );

  /**
   * determine entry to linked scene
   */
  bool enter();

private:

  /**
   * have a conversation with a character
   * @param conversation the conversation
   * @param following if the character is currently following
   */
  void convo( uint character_index, Conversation conversation,
    bool following );

  /**
   * update the scene right
   * @param count the character walking cycle count
   */
  void right( uint count );

  /**
   * update the scene left
   * @param count the character walking cycle count
   */
  void left( uint count );

  /**
   * update the scene center
   */
  void center();

  /**
   * convert npc to follower
   */
  bool recruit();

  /**
   * ask to confirm recruitment
   */
  bool confirm_recruit( Character* character );

  /**
   * speak to npc
   */
  void speak();

  /** 
   * prompt to speak
   */
  void prompt_speak();

  /**
   * prompt to enter linked scene
   */
  void prompt_enter_linked_scene();

  /**
   * draw the stationary npcs
   * @param left the direction
   */
  void draw_npcs( bool left );

  /**
   * draw the stationary npcs when standing
   */
  void draw_npcs();

  /**
   * draw the following characters
   * @param left the direction
   */
  void ducklings( bool left );

  /**
   * draw the standing characters
   */
  void ducklings();

  /**
   * update the characters
   * @param left the direction
   */
  void update_characters( bool left );

  /**
   * update the characters
   * @param left the direction
   */
  void update_characters();

  /**
   * scroll dialogue
   * @param message the message to display
   * @param renderer the renderer
   * @param font the font
   * @param speaker the speaker
   */
  void scroll_dialogue( string message, SDL_Renderer *renderer,
                        TTF_Font *font, Character *speaker,
                        bool happy );

  /**
   * fade into and out of scenes
   * @param left the direction
   */
  void scene_fade( bool left );
  
  SDL_Renderer *renderer;
  Background background;
  static vector< Character > following_characters;
  vector< Character > characters;
  Script scene_dialogue;
  Character main_character;
  uint speed;
  
  int stage_left_pos;
  int stage_right_pos;
  int stage_size;
  int window_size;

  vector< int > scene_junction_positions;
  
  TTF_Font *font;
  Text_box dialogue_display;
  Text_box prompt_display;

};

#endif
