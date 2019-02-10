#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>
#include "sprite.h"

/**
 * A character class
 * @author Jared Allen
 * @version 9 February 2019
 */
class Character
{
public:

  /**
   * Constructor
   * @param full_body the full body sprite
   * @param torso the torso sprite
   */
  Character( Sprite full_body, Sprite torso, uint force,
             uint diversion, uint stealth );
  
  /**
   * make the character walk left
   * @param speed the speed that the character walks
   */
  void walk_left( uint speed );

  /**
   * make the character walk right
   * @param speed the speed that the character walks
   */
  void walk_right( uint speed );

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
  void follow( Character leader, uint speed );

  
  /**
   * update characters position
   */
  void update_pos( bool left, uint speed );



private:

  bool facing_left;
  int x_pos;
  int y_pos;

  Sprite full_body;
  vector< SDL_Rect > walking_clips;
  uint stride;
  
  Sprite torso;
  vector< SDL_Rect > talking_clips;

  
  uint force;
  uint diversion;
  uint stealth;

};

Character::Character( Sprite param_full_body,
                      Sprite param_torso, uint param_force,
                      uint param_diversion, uint param_stealth )
: full_body( param_full_body ), torso( param_torso ),
  force( param_force ), diversion( param_diversion ),
  stealth( param_stealth )
{

  uint walking_sprites = 2;
  for( uint i = 0; i < walking_sprites; i++ )
  {
    SDL_Rect clip;
    walking_clips.push_back( clip );
    walking_clips.at( i ).x = i * ( full_body.get_width() / 2 );
    walking_clips.at( i ).y = 0;
    walking_clips.at( i ).h = full_body.get_height();
    walking_clips.at( i ).w = full_body.get_width() / 2;
  }

  uint talking_sprites = 2;
  for( uint i = 0; i < talking_sprites; i++ )
  {
    SDL_Rect clip;
    talking_clips.push_back( clip );
    talking_clips.at( i ).x = i * ( torso.get_width() / 2 );
    talking_clips.at( i ).y = 0;
    talking_clips.at( i ).h = torso.get_height();
    talking_clips.at( i ).w = torso.get_width() / 2;
  }

  x_pos = 0;
  y_pos = 0;
  stride = 1;
  facing_left = false;

}

void Character::walk_right( uint speed )
{
  stride = ( stride + 1 ) % walking_clips.size();
  full_body.set_source( &walking_clips.at( stride ) );
  full_body.draw();
  
  set_position( x_pos + speed,
                y_pos );
  facing_left = false;
}

void Character::walk_left( uint speed )
{
  stride = ( stride + 1 ) % walking_clips.size();
  full_body.set_source( &walking_clips.at( stride ) );
  full_body.flip_draw();
  
  set_position( x_pos - speed,
                y_pos );
  facing_left = true;
}

void Character::stand()
{
  stride = 1;
  full_body.set_source( &walking_clips.at( stride ) );
  if( facing_left )
  {
    full_body.flip_draw();
  }
  else
  {
    full_body.draw();
  }
}

void Character::set_position( int new_x, int new_y )
{
  x_pos = new_x;
  y_pos = new_y;
}

void Character::set_screen_position( int new_x, int new_y )
{
  full_body.set_position( new_x, new_y );
}

vector< int > Character::get_screen_position()
{
  return full_body.get_position();
}

vector< int > Character::get_position()
{
  vector< int > position;
  position.push_back( x_pos );
  position.push_back( y_pos );
  return position;
}

void Character::follow( Character leader, uint speed )
{
  uint follow_distance = 200;
  int leader_x = leader.get_position().at( 0 );
  int position_from_leader = leader_x - get_position().at( 0 );

  uint distance_from_leader = abs( position_from_leader );

  if( distance_from_leader > follow_distance )
  {
    if( position_from_leader > 0 )
    {
      update_pos( true, speed );
      walk_right( speed );
    }
    else if( position_from_leader < 0 )
    {
      update_pos( false, speed );
      walk_left( speed );
    }
  }
  else
  {
    stand();
  }
}

void Character::update_pos( bool left, uint speed )
{
  if( !left )
  {
    set_screen_position(
      get_screen_position().at( 0 ) - speed,
      get_screen_position().at( 1 ) );
    set_position(
      get_position().at( 0 ) - speed,
      get_position().at( 1 ) );
  }
  else
  {
    set_screen_position(
      get_screen_position().at( 0 ) + speed,
      get_screen_position().at( 1 ) );
    set_position(
      get_position().at( 0 ) + speed,
      get_position().at( 1 ) );
  }
}
  

#endif

  

