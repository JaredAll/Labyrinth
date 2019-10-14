#include "conversation.h"
Conversation::Conversation( string filepath, SDL_Renderer* renderer )
{
  ifstream in_file = ifstream( filepath );
  char c;
  const int DIALOGUE_LINE_SIZE = 100;
  char dialogue_line[ DIALOGUE_LINE_SIZE ];
  uint i = 0;
  while( in_file.get( c ) )
    {
      if( c != '\n' )
	{
	  dialogue_line[ i ] = c;
	  i++;
	}
      else
	{
	  dialogue_line[ i ] = '\0';
	  i = 0;
	  this -> add_dialogue( &dialogue_line[ 0 ], renderer );
	}
    } 
}

Conversation::Conversation()
{
  angry_response = "";
}

string Conversation::get_dialogue( uint index )
{
  return dialogue.at( index );
}

uint Conversation::get_length()
{
  return dialogue.size();
}

void Conversation::add_dialogue( char* words, SDL_Renderer* renderer )
{
  string message = string( words );
  dialogue.push_back( message );
}

void Conversation::set_angry_response( char* words, SDL_Renderer* renderer )
{
  string message = string( words );
  angry_response = message;
}

string Conversation::get_angry_response()
{
  return angry_response;
}
