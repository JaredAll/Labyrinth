#include "character.h"
Character::Character( string param_name,
                      Sprite param_full_body,
                      Sprite param_torso, uint param_force,
                      uint param_diversion, uint param_stealth,
                      uint param_num_walking,
                      uint param_num_talking )
  : name( param_name ), full_body( param_full_body ), torso( param_torso ),
  force( param_force ), diversion( param_diversion ),
  stealth( param_stealth ), num_walking_sprites( param_num_walking ),
  num_talking_sprites( param_num_talking )
{

  for( uint i = 0; i < num_walking_sprites; i++ )
  {
    SDL_Rect clip;
    walking_clips.push_back( clip );
    walking_clips.at( i ).x = i * ( full_body.get_width() /
      num_walking_sprites );
    walking_clips.at( i ).y = 0;
    walking_clips.at( i ).h = full_body.get_height();
    walking_clips.at( i ).w = full_body.get_width() /
      num_walking_sprites;
  }

  for( uint i = 0; i < num_talking_sprites; i++ )
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

void Character::happy()
{
  uint face = 0;
  torso.set_source( &talking_clips.at( face ) );
  torso.draw();
}

void Character::gasp()
{
  uint face = 1;
  torso.set_source( &talking_clips.at( face ) );
  torso.draw();
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

vector< int >Character::get_screen_position()
{
  vector< int > position;
  position.push_back( full_body.get_x() );
  position.push_back( full_body.get_y() );
  return position;
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
  uint follow_distance = 130;
  int leader_x = leader.get_screen_position().at( 0 );
  int position_from_leader = leader_x -
    get_screen_position().at( 0 );

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
  }
  else
  {
    set_screen_position(
      get_screen_position().at( 0 ) + speed,
      get_screen_position().at( 1 ) );
  }
}

void Character::reset()
{
  x_pos = 0;
  y_pos = 0;
  full_body.reset_position();
}

void Character::reset( uint new_x )
{
  x_pos = new_x;
  y_pos = 0;
  full_body.reset_position();
}

string Character::get_name()
{
  return name;
}

bool Character::equals( Character character )
{
  return ( name == character.get_name() );
}

void Character::set_stage_pos( int screen_pos, int pos )
{
  x_pos = pos;
  full_body.set_position( screen_pos );
}
  
