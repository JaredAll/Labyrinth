#include "script.h"

Conversation Script::speak_to( Character* character )
{
  uint speaker_index = UINT_MAX;
  for( uint i = 0; i < characters.size(); i++ )
  {
    if( (*characters.at( i ) ).equals( *character ) )
    {
      speaker_index = i;
    }
  }

  vector< Conversation > dialogue =
    conversations.find(
      characters.at( speaker_index ) ) -> second;
  
  uint line =
    lines.find( characters.at( speaker_index ) ) -> second;

  uint new_line = line + 1;
  
  lines.find( characters.at( speaker_index ) ) -> second =
    new_line % dialogue.size();
  
  return dialogue.at( line );
}

Script::Script( vector< Character* > param_characters ) :
characters( param_characters )
{
  for( uint i = 0; i < characters.size(); i++ )
  {
    vector< Conversation > dialogue;
    conversations.insert( { characters.at( i ), dialogue } );
    lines.insert( { characters.at( i ), 0 } );
  }

}

void Script::insert_conversation( Character* character,
				  Conversation conversation )
{
  ( conversations.find( character ) -> second ).push_back( conversation );
  
}
