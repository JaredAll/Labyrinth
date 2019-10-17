#ifndef SCENE_H
#define SCENE_H

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
#include "scene_states.h"
#include "interaction.h"
#include <unistd.h>

using namespace std;

struct Report
{
  Scene_States status;
  int character_position;
};


/**
 * A scene class
 * @author Jared Allen
 * @version 8 February 2019
 */
class Scene
{
public:

  /** 
   * add an interaction
   */
  void add_interaction( vector< string > messages,
                        int scene_position,
                        SDL_Renderer* renderer );

  /**
   * prompt interaction
   */
  void prompt_interact();

  /**
   * perform interaction if within proximity
   */
  void interact();

  /**
   * Set the stage to a position based on the junction position
   * @param junction position the position to set the stage to
   */
  void stage_junction( int junction_position );

  /**
   * plays the scene
   */
  Report play();

  /**
   * determines whether a movement key is being held down
   */
  bool movement_key_pressed( const Uint8* state );

  /**
   * moves the main character
   */
  void marionette( int x_velocity, int y_velocity, uint cadence );

  /**
   * sets previous scene junction position
   */
  void set_previous_junction_position( int position );

  /**
   * gets the previous scene junction position
   */
  int get_previous_junction_position();

  /**
   * resets the scene
   */
  void reset();

  /**
   * adds a following character
   */
  void add_follower( Character* character );

  /**
   * sets the scene to the left
   */
  void stage_left();

  /**
   * sets the scene to the left barrier
   */
  void stage_left_barrier();

  /**
   * sets the scene to the right
   */
  void stage_right();

  /** 
   * sets the scene to the right barrier
   */
  void stage_right_barrier();

  /**
   * adds conversation to scene
   */
  void add_conversation( Conversation* conversation );

  /**
   * Constructor
   * @param renderer the renderer
   * @param background the background
   * @param characters the characters
   * @param main_character the main character
   * @param speed the speed
   */
  Scene( SDL_Renderer *renderer, Background* background,
         vector< Character* > characters,
         Character* main_character,
	 Script* scene_dialogue,
	 uint speed,
         uint maximum_stage_displacement );

  /**
   * Destructor
   */
  ~Scene();

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
  void convo( uint character_index, Conversation* conversation,
              bool following );
  /**
   * update the scene jumping right
   * @param count the character walking cycle count
   */
  void air_right( uint count );

  /**
   * update the scene right
   * @param count the character walking cycle count
   */
  void right( uint count );

  /**
   * update the scene left while jumping
   * @param count the character walking cycle count
   */
  void air_left( uint count );

  /**
   * update the scene left
   * @param count the character walking cycle count
   */
  void left( uint count );

  /**
   * update the scene center
   */
  void center( uint count );

  /**
   * update the scene jump
   */
  void jump();

  /**
   * update the scene lateral jump
   * @param x_unit_vector the x directional vector
   * @param count the character walking cycle count
   */
  int lateral_jump( int x_unit_vector, int y_velocity, uint count );

  /**
   * update the scene lateral screen jump
   * @param x_unit_vector the x directional vector
   * @param count the character walking cycle count
   */
  int lateral_screen_jump( int x_unit_vector, int y_velocity, uint count );

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
  void ducklings( bool left, uint count );

  /**
   * draw the standing characters
   */
  void ducklings( uint count );

  /** 
   * update the characters
   * @param left the direction
   */
  void update_characters( bool left, uint count );

  /**
   * update the characters
   * @param left the direction
   */
  void update_characters( uint count );

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
   * scroll dialogue
   * @param message the message to display
   * @param renderer the renderer
   * @param font the font
   */
  void scroll_dialogue( string message, SDL_Renderer *renderer,
                        TTF_Font *font );

  
  /**
   * fade into and out of scenes
   * @param left the direction
   */
  void scene_fade( bool left );

  /**
   * perform an interaction with the scene
   * @param interaction the interaction to perform
   */
  void perform_interaction( Interaction* interaction );
  
  SDL_Renderer *renderer;
  Background* background;
  static vector< Character* > following_characters;
  vector< Character* > characters;
  Script* scene_dialogue;
  
  Character* main_character;
  uint speed; 
  
  int stage_left_pos;
  int stage_right_pos;
  int maximum_stage_displacement;
  int window_size;

  int previous_junction_position;

  vector< int > scene_junction_positions;
  vector< Interaction* > interactions;
  
  TTF_Font *font;
  Text_box* dialogue_display;
  Text_box* prompt_display;

  Report report;

};

#endif
