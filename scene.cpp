#include "scene.h"

void Scene::speak()
{

  uint speak_proximity = 30;
  uint speak_index = 0;
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    int distance_from_speaker =
      abs( following_characters.at( i )
           .get_screen_position().at( 0 ) -
           main_character.get_screen_position().at( 0 ) );
    
    if( distance_from_speaker < speak_proximity )
    {
      speak_index = i;
      convo( speak_index,
             scene_dialogue.speak_to( &following_characters.at(
                                        speak_index ) ), true );
    }
  }
  return;
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
      convo( recruit_index,
             scene_dialogue.speak_to( &characters.at(
                                        recruit_index ) ), false );
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

void Scene::convo( uint character_index, Conversation conversation,
                   bool following )
{
  
  SDL_RenderClear( renderer );
  background.draw();

  Character* speaker;
  if( following )
  {
    speaker = &following_characters.at( character_index );
  }
  else
  {
    speaker = &characters.at( character_index );
  }
    
  (*speaker).happy();
  uint convo_length = conversation.get_length();

  
  SDL_Texture* message = conversation.get_dialogue( 0 );
  SDL_Rect message_rect;
  message_rect.x = 0;
  message_rect.y = 0;
  message_rect.w = 400;
  message_rect.h = 100;

  SDL_RenderPresent( renderer );

  
  bool talking = true;
  uint conversation_position = -1;
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
          
          (*speaker).gasp();

          conversation_position++;

          if( conversation_position == convo_length )
          {
            talking = false;
          }

          if( conversation_position < convo_length )
          {
            message =
              conversation.get_dialogue(
                conversation_position );
          }

          SDL_RenderCopy( renderer, message, NULL, &message_rect );
    
          SDL_RenderPresent( renderer );
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {
          
          SDL_RenderClear( renderer );
          background.draw();
          
          (*speaker).happy();

          message = conversation.get_angry_response();

          SDL_RenderCopy( renderer, message, NULL, &message_rect );
    
          SDL_RenderPresent( renderer );
        }
        else if( e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP )
        {
          talking = false;
        }
      }
    }
  }
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

  uint STAGE_CENTER = 225;
  int main_char_pos = main_character.get_position().at( 0 );
  int distance_from_edge = stage_size - abs(
    main_char_pos );
  if( distance_from_edge < STAGE_CENTER ||
      main_char_pos < STAGE_CENTER )
  {
    background.draw();
    main_character.update_pos( true, speed );
    main_character.walk_right( speed );
    draw_npcs();
    ducklings( false );
  } 
  else
  {
    background.left( speed );
    background.draw();
    draw_npcs( false );
  
    main_character.walk_right( speed );
    //scene_fade( true );
    ducklings( false );
  }
  
  SDL_RenderPresent( renderer );
  SDL_Delay( 200 );
}

void Scene::left()
{
  SDL_RenderClear( renderer );

  uint STAGE_CENTER = 225;
  int main_char_pos = main_character.get_position().at( 0 );
  int distance_from_edge = stage_size - abs(
    main_char_pos );
  if( distance_from_edge < STAGE_CENTER ||
      main_char_pos < STAGE_CENTER )
  {
    background.draw();
    main_character.update_pos( false, speed );
    main_character.walk_left( speed );
    draw_npcs();
    ducklings( true );
  } 
  else
  {
    background.right( speed );
    background.draw();
    draw_npcs( true );
  
    main_character.walk_left( speed );
    //scene_fade( true );
    ducklings( true );
  }
  
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
	     Script param_scene_dialogue,
	     uint param_speed )
: background( param_background ),
  characters( param_characters ),
  main_character( param_main_character ), speed( param_speed ),
  renderer( param_renderer), scene_dialogue( param_scene_dialogue )
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
        if( e.key.keysym.sym == SDLK_UP )
        {
          speak();
          push = false;
        }
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
  main_character.stage_left();
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).stage_left();
  }
}

void Scene::stage_right()
{
  background.reset( stage_left_pos );
  main_character.stage_right();
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).stage_right();
  }
}

void Scene::add_follower( Character character )
{
  following_characters.push_back( character );
}
