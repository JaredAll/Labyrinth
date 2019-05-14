#include "scene.h"

void Scene::scene_fade( bool left )
{
  uint SCREEN_CENTER = 400;
  int distance_from_edge = stage_size - abs(
    main_character.get_position().at( 0 ) );
  if( distance_from_edge < SCREEN_CENTER )
  {
    main_character.update_pos( left, speed );
  }
  
}

bool Scene::recruit()
{
  uint recruit_proximity = 30;
  uint recruit_index = 0;
  bool found_recruit = false;
  
  for( uint i = 0; i < characters.size(); i++ )
  {
    int distance_from_recruit =
      abs( characters.at( i ).get_screen_position().at( 0 ) -
           main_character.get_screen_position().at( 0 ) );
    if( distance_from_recruit < recruit_proximity )
    {
      recruit_index = i;
      found_recruit = true;
      convo( recruit_index, conversations.at( 0 ) );
    }
  }

  if( found_recruit )
  {
    following_characters.push_back( characters.at( recruit_index ) );
    vector< Character > remaining_characters;
    for( uint i = 0; i < characters.size(); i++ )
    {
      if( i != recruit_index )
      {
        remaining_characters.push_back( characters.at( i ) );
      }
    }
    characters = remaining_characters;
  }
  return found_recruit;
  
}

void Scene::convo( uint character_index, Conversation conversation )
{
  
  SDL_RenderClear( renderer );
  background.draw();
    
  characters.at( character_index ).happy();
  uint convo_length = conversation.get_length();

  
  SDL_Texture* message = conversation.get_dialogue( 0 );
  SDL_Rect message_rect;
  message_rect.x = 0;
  message_rect.y = 0;
  message_rect.w = 400;
  message_rect.h = 100;

  SDL_RenderPresent( renderer );

  
  bool talking = true;
  uint conversation_position = 0;
  SDL_Event e;
  while( talking )
  {
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_KEYDOWN )
      {
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
                
          SDL_RenderClear( renderer );
          background.draw();
          
          characters.at( character_index ).gasp();

          SDL_RenderCopy( renderer, message, NULL, &message_rect );
    
          SDL_RenderPresent( renderer );

	  conversation_position++;
	  message = conversation.get_dialogue( conversation_position % convo_length );
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {
          
          SDL_RenderClear( renderer );
          background.draw();
          
          characters.at( character_index ).happy();
    
          SDL_RenderPresent( renderer );
        }
        else if( e.key.keysym.sym == SDLK_DOWN )
        {
          talking = false;
        }
      }
    }
  }
}

void Scene::add_conversation( Conversation conversation )
{
  conversations.push_back( conversation );
}

void Scene::center()
{
  SDL_RenderClear( renderer );
  background.draw();
  draw_npcs();
  
  main_character.stand();
  ducklings();
  
  SDL_RenderPresent( renderer );
}

void Scene::right()
{
   
  SDL_RenderClear( renderer );
  
  background.left( speed );
  background.draw();
  draw_npcs( false );
  
  main_character.walk_right( speed );
  //scene_fade( true );
  ducklings( false );
  
  SDL_RenderPresent( renderer );
  SDL_Delay( 200 );
}

void Scene::left()
{
  SDL_RenderClear( renderer );
          
  background.right( speed );
  background.draw();
  draw_npcs( true );
  
  main_character.walk_left( speed );
  //scene_fade( false );
  ducklings( true );
  
  SDL_RenderPresent( renderer );
  SDL_Delay( 200 );
}

void Scene::update_characters( bool left )
{
  draw_npcs( left );
  ducklings( left );
}

void Scene::update_characters()
{
  draw_npcs();
  ducklings();
}

void Scene::ducklings( bool left )
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).update_pos( left, speed );
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed );
    }
    else
    {
      following_characters.at(
        i ).follow( following_characters.at( i - 1 ),
                    speed );
    }
  }
}

void Scene::ducklings()
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed );
    }
    else
    {
      following_characters.at( i ).follow(
        following_characters.at( i - 1 ),
        speed );
    }
  }
}

void Scene::draw_npcs( bool left )
{
  for( uint i = 0; i < characters.size(); i++ )
    {
      characters.at( i ).update_pos( left, speed );
      characters.at( i ).stand();
    }
}

void Scene::draw_npcs()
{
  for( uint i = 0; i < characters.size(); i++ )
    {
      characters.at( i ).stand();
    }
}

vector< Character > Scene::following_characters;

Scene::Scene(SDL_Renderer *param_renderer,
             Background param_background,
             vector< Character > param_characters,
             Character param_main_character,
	     vector< Conversation > param_conversations,
	     uint param_speed )
: background( param_background ),
  characters( param_characters ),
  main_character( param_main_character ), speed( param_speed ),
  renderer( param_renderer), conversations( param_conversations )
{
  stage_size = 500;
  stage_left_pos = stage_size * -1;
  stage_right_pos = stage_size;
}

int Scene::play()
{
  SDL_Event e;
  bool push = false;
  int status = 0;
  bool in_bounds = true;
  bool play = true;
  
  while( in_bounds && play )
  {
    if( main_character.get_position().at( 0 ) > stage_right_pos )
    {
      in_bounds = false;
      status = 0;
    }

    if( main_character.get_position().at( 0 ) < stage_left_pos )
    {
      in_bounds = false;
      status = 1;
    }
    
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        status = 2;
        play = false;
      }
      if( e.type == SDL_KEYDOWN )
      {
        push = true;
      }
      else
      {
        push = false;
      }
    }
    
    if( play )
    {
      if( push )
      {
        if( e.key.keysym.sym == SDLK_DOWN )
        {
          recruit();
        }
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
          right();
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {        
          left();
        }
      }
      else
      {
        center();
      }
    }
  }
  return status;
}

void Scene::reset()
{
  background.reset();
  main_character.reset();
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset();
  }
}

void Scene::stage_left()
{
  background.reset( stage_right_pos );
  main_character.reset( stage_left_pos );
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset( stage_left_pos );
  }
}

void Scene::stage_right()
{
  background.reset( stage_left_pos );
  main_character.reset( stage_right_pos );
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).reset( stage_right_pos );
  }
}

void Scene::add_follower( Character character )
{
  following_characters.push_back( character );
}
