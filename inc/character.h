#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "sprite.h"
#include <unistd.h>
#include "game_component.h"

using namespace std;

/**
 * A character class
 * @author Jared Allen
 * @version 9 February 2019
 */
class Character : public GameComponent
{
public:

  /**
   * Constructor
   * @param full_body the full body sprite
   * @param torso the torso sprite
   */
  Character( string name,
             Sprite *full_body, Sprite *torso, uint force,
             uint diversion, uint stealth, uint num_walking_sprites,
             uint num_talking_sprites );

  void update();

  /**
   * Destructor
   */
  ~Character();

  /**
   * set character happy expression 
   */
  void happy();
  
  /**
   * set character gasp expression
   */
  void gasp();
  
  /**
   * make the character walk left
   * @param speed the speed that the character walks
   * @param count the characters cycle count
   */
  void walk_left( uint speed, uint count );

  /**
   * make the character walk right
   * @param speed the speed that the character walks
   * @param count the characters walking cycle count
   */
  void walk_right( uint speed, uint count );

  /**
   * make the character jump
   */
  void jump( int y_velocity );

  /**
   * make the character jump laterally
   */
  void jump( int x_velocity, int y_velocity );

  /**
   * make the character stand
   */
  void stand();

  /**
   * set the characters coordinates
   */
  void set_position( int x, int y );
  
  /**
   * set the characters screen coordinates
   */
  void set_screen_position( int x, int y );

  /**
   * get the characters coordinates
   */
  vector< int > get_screen_position();

  /**
   * get the characters coordinates
   */
  vector< int > get_position();

  /**
   * make NPCs follow the character
   */
  void follow( Character* leader, uint speed, uint count );

  
  /**
   * update characters position
   */
  void update_pos( bool left, uint speed );

  /**
   * reset characters position
   */
  void reset();

  /**
   *reset characters position with offset
   */
  void reset( uint offset );

  /**
   * determine if two characters are equal
   */
  bool equals( Character *character );

  /**
   * gets the name of the character
   */
  string get_name();

  /**
   * set stage position
   */
  void set_stage_pos( int screen_pos, int pos );

  /**
   * recruit a character
   */
  void set_recruited();

  /**
   * determine if character has been recruited
   */
  bool is_recruited();


private:

  string name;
  bool recruited;

  bool facing_left;
  int x_pos;
  int y_pos;

  uint num_walking_sprites;
  uint num_talking_sprites;

  Sprite *full_body;
  vector< SDL_Rect* > walking_clips;
  uint stride;
  
  Sprite *torso;
  vector< SDL_Rect* > talking_clips;
  
  uint force;
  uint diversion;
  uint stealth;

};

#endif

  

