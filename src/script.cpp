#include "script.h"

Conversation* Script::speak_to( Character* character )
{

  cout << endl;
  cout << characters.size() << endl;
  uint speaker_index = UINT_MAX;
  for( uint i = 0; i < characters.size(); i++ )
  {
    if( characters.at( i ) -> equals( character ) )
    {
      speaker_index = i;
    }
  }

  cout << characters.size() << endl;
  if( !(*characters.at( speaker_index ) ).is_recruited() )
  {
    cout << "here" << endl;
    // cout << speaker_index << endl;
    return recruit_conversations.find(
      characters.at( speaker_index ) ) -> second;
  }

  vector< Conversation* > dialogue;  
  dialogue = conversations.find(
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
    vector< Conversation* > dialogue;
    conversations.insert( { characters.at( i ), dialogue } );
    lines.insert( { characters.at( i ), 0 } );

    Conversation* this_recruit_conversation;
    recruit_conversations.insert( { characters.at( i ),
          this_recruit_conversation } );
  }
}

void Script::insert_conversation( Character* character,
				  Conversation *conversation )
{
  ( conversations.find( character ) -> second ).push_back( conversation );
  
}

void Script::insert_recruit_conversation(
  Character* character,
  Conversation *conversation )
{
  ( recruit_conversations.find( character ) -> second ) =
    conversation;
}
