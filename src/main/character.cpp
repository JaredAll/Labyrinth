#include "character.h"
Character::Character( string param_name,
                      Sprite *param_full_body,
                      Sprite *param_torso, uint param_force,
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
    SDL_Rect *clip = new SDL_Rect();
    walking_clips.push_back( clip );
    walking_clips.at( i ) -> x = i * ( full_body -> get_width() /
                                       num_walking_sprites );
    walking_clips.at( i ) -> y = 0;
    walking_clips.at( i ) -> h = full_body -> get_height();
    walking_clips.at( i ) -> w = full_body -> get_width() /
      num_walking_sprites;
  }

  for( uint i = 0; i < num_talking_sprites; i++ )
  {
    SDL_Rect *clip = new SDL_Rect();
    talking_clips.push_back( clip );
    talking_clips.at( i ) -> x = i * ( torso -> get_width() / 2 );
    talking_clips.at( i ) -> y = 0;
    talking_clips.at( i ) -> h = torso -> get_height();
    talking_clips.at( i ) -> w = torso -> get_width() / 2;
  }

  x_pos = 0;
  y_pos = 0;
  stride = 1;
  facing_left = false;
  recruited = false;

  setRenderComponent( full_body );
}

Character::~Character()
{
  if( full_body )
  {
    full_body -> ~Sprite();
  }

  if( torso )
  {    
    torso -> ~Sprite();
  }
}

void Character::happy()
{
  uint face = 0;
  torso -> set_source( talking_clips.at( face ) );
}

void Character::gasp()
{
  uint face = 1;
  torso -> set_source( talking_clips.at( face ) );
}

void Character::walk_right( uint speed, uint count )
{
  if( count == 3 )
  {
    stride = ( stride + 1 ) % walking_clips.size();
  }

  full_body -> set_source( walking_clips.at( stride ) );
  
  set_position( x_pos + speed,
                y_pos );

  facing_left = false;
}

void Character::walk_left( uint speed, uint count )
{
  if( count == 3 )
  {
    stride = ( stride + 1 ) % walking_clips.size();
  }

  full_body -> set_source( walking_clips.at( stride ) );
  set_position( x_pos - speed,
                y_pos );
  facing_left = true;
}

void Character::jump( int x_velocity, int y_velocity )
{
  stride = 2;
  full_body -> set_source( walking_clips.at( stride ) );

  y_pos = y_pos + y_velocity;
  x_pos = x_pos + x_velocity;

  set_position( x_pos, y_pos );  
}

void Character::jump( int y_velocity )
{
  stride = 2;
  full_body -> set_source( walking_clips.at( stride ) );

  y_pos = y_pos + y_velocity;
  set_position( x_pos, y_pos );
}

void Character::stand()
{
  stride = 1;
  full_body -> set_source( walking_clips.at( stride ) );
}

void Character::set_position( int new_x, int new_y )
{
  x_pos = new_x;
  y_pos = new_y;
}

void Character::set_screen_position( int new_x, int new_y )
{
  full_body -> set_position( new_x, new_y );
}

vector< int >Character::get_screen_position()
{
  vector< int > position;
  position.push_back( full_body -> get_x() );
  position.push_back( full_body -> get_y() );
  return position;
}

vector< int > Character::get_position()
{
  vector< int > position;
  position.push_back( x_pos );
  position.push_back( y_pos );
  return position;
}

void Character::follow( Character* leader, uint speed, uint count )
{
  uint follow_distance = 130;
  int leader_x = leader -> get_screen_position().at( 0 );
  int position_from_leader = leader_x -
    get_screen_position().at( 0 );

  uint distance_from_leader = abs( position_from_leader );

  if( distance_from_leader > follow_distance )
  {
    if( position_from_leader > 0 )
    {
      update_pos( true, speed );
      walk_right( speed, count );
    }
    else if( position_from_leader < 0 )
    {
      update_pos( false, speed );
      walk_left( speed, count );
    }
  }
  else
  {
    stand();
  }
}

void Character::update()
{
  
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
  full_body -> reset_position();
}

void Character::reset( uint new_x )
{
  x_pos = new_x;
  y_pos = 0;
  full_body -> reset_position();
}

string Character::get_name()
{
  return name;
}

bool Character::equals( Character* character )
{
  return ( name == character -> get_name() );
}

void Character::set_stage_pos( int screen_pos, int pos )
{
  x_pos = pos;
  full_body -> set_position( screen_pos );
}

void Character::set_recruited()
{
  recruited = true;
}

bool Character::is_recruited()
{
  return recruited;
}
