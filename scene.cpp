#include "scene.h"

uint counted_frames = 0;

void Scene::speak()
{

  uint speak_proximity = 60; 
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
  uint recruit_proximity = 60;
  uint recruit_index = 0;
  bool found_recruit = false;
  bool recruit_success = false;
  
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
      recruit_success = confirm_recruit(
        &characters.at( recruit_index ) );
      
    }
  }

  if( recruit_success )
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
  return recruit_success;
}

bool Scene::confirm_recruit( Character* character )
{

  string prompt_recruitment = "Recruit? y/n";
  
  SDL_RenderClear( renderer );
  background.draw();
          
  (*character).gasp();
  
  prompt_display.display( prompt_recruitment, renderer, font,
                          prompt_recruitment.length() );
  SDL_RenderPresent( renderer );
  ++counted_frames;

  bool recruit = false;
  bool deciding = true;
  SDL_Event e;

  while( deciding )
  {
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_KEYDOWN )
      {
        if( e.key.keysym.sym == SDLK_y )
        {
          recruit = true;
          (*character).set_recruited();
        }
        else if( e.key.keysym.sym == SDLK_n )
        {
          recruit = false;
        }
        deciding = false;
      }
    }
  }
  return recruit; 
}

bool Scene::enter()
{
  bool entry = false;
  uint entry_proximity = 60;

  for( uint i = 0; i < scene_junction_positions.size();
       i++ )
  { 
    int distance_from_entry =
      abs( scene_junction_positions.at( i ) -
           main_character.get_position().at( 0 ) );
  
    if( distance_from_entry < entry_proximity )
    {
      entry = true;
      report.character_position = scene_junction_positions.at( i );

      for( uint i = 0; i < following_characters.size(); i++ )
      {
        following_characters.at( i ).
          set_stage_pos( main_character
                         .get_screen_position().at( 0 ),
                         main_character
                         .get_position().at( 0 ) );
      }
      
    }
  }
  return entry;
}

void Scene::prompt_enter_linked_scene()
{

  string prompt_enter = "right shift to enter";

  uint entry_proximity = 60;

  for( uint i = 0; i < scene_junction_positions.size(); i++ )
  {
    int distance_from_entry =
      abs( scene_junction_positions.at( i ) -
           main_character.get_position().at( 0 ) );
  
    if( distance_from_entry < entry_proximity )
    {
      prompt_display.display( prompt_enter, renderer, font,
                              prompt_enter.length() );
    }
  }
}

void Scene::prompt_speak()
{

  string prompt_speak = "down to speak";
  
  uint speaker_proximity = 60;
  
  for( uint i = 0; i < characters.size(); i++ )
  {
    int distance_from_speaker =
      abs( characters.at( i ).get_screen_position().at( 0 ) -
           main_character.get_screen_position().at( 0 ) );
    if( distance_from_speaker < speaker_proximity )
    {
      prompt_display.display( prompt_speak, renderer, font,
                              prompt_speak.length() );
    }
  }
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
    
  bool is_happy = true;
  uint convo_length = conversation.get_length();
  string message = conversation.get_dialogue( 0 );

  scroll_dialogue( message, renderer, font, speaker, is_happy );
    
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
          
          is_happy = true;
          
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

            scroll_dialogue( message, renderer, font,
                             speaker, is_happy );

          }
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {
          
          SDL_RenderClear( renderer );
          background.draw();
          
          is_happy = false;

          message = conversation.get_angry_response();

          scroll_dialogue( message, renderer, font, speaker,
                           is_happy );

          
          SDL_RenderPresent( renderer );
          ++counted_frames;
          
        }
        else if( e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_UP )
        {
          talking = false;
        }
      }
    }
  }
}

void Scene::center( uint count )
{
  SDL_RenderClear( renderer );
  background.draw();
  draw_npcs();
  
  ducklings( count );
  prompt_speak();

  main_character.stand();

  prompt_interact();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
}

void Scene::right( uint count )
{
   
  SDL_RenderClear( renderer );

  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character.get_position().at( 0 );
  if( main_char_pos < ( -1 * stage_center_edge ) ||
      main_char_pos >= stage_center_edge )
  {
    background.draw();
    draw_npcs();
    ducklings( count );
    main_character.walk_right( speed, count );
    main_character.update_pos( true, speed );
  } 
  else
  {
    background.left( speed );
    background.draw();
    draw_npcs( false );
    ducklings( false, count );
    main_character.walk_right( speed, count );
  }
  prompt_interact();
  prompt_speak();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
  SDL_Delay( 50 );
}

void Scene::left( uint count )
{
  SDL_RenderClear( renderer );

  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character.get_position().at( 0 );
  
  if( main_char_pos < ( -1 * stage_center_edge ) ||
      main_char_pos >= stage_center_edge )
  {
    background.draw();
    draw_npcs();
    ducklings( count );
    main_character.walk_left( speed, count );
    main_character.update_pos( false, speed );
  } 
  else
  {
    background.right( speed );
    background.draw();
    draw_npcs( true );
    ducklings( true, count ); 
    main_character.walk_left( speed, count );
  }
  prompt_interact();
  prompt_speak();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
  SDL_Delay( 50 );
}

void Scene::update_characters( bool left, uint count )
{
  draw_npcs( left );
  ducklings( left, count );
}

void Scene::update_characters( uint count )
{
  draw_npcs();
  ducklings( count );
}

void Scene::ducklings( bool left, uint count )
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).update_pos( left, speed );
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed, count );
    }
    else
    {
      following_characters.at(
        i ).follow( following_characters.at( i - 1 ),
                    speed, count );
    }
  }
}

void Scene::ducklings( uint count )
{
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    if( i == 0 )
    {
      following_characters.at( i ).follow(
        main_character, speed, count );
    }
    else
    {
      following_characters.at( i ).follow(
        following_characters.at( i - 1 ),
        speed, count );
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
	     uint param_speed,
             uint param_maximum_stage_displacement )
  :
  background( param_background ),
  characters( param_characters ),
  main_character( param_main_character ),
  speed( param_speed ),
  renderer( param_renderer),
  scene_dialogue( param_scene_dialogue ),
  maximum_stage_displacement( param_maximum_stage_displacement ),
  dialogue_display( 25, 25, 100, 300 ),
  prompt_display( 25, 400, 100, 300 )
{
  
  window_size = 1000;
  stage_left_pos = maximum_stage_displacement * -1;
  stage_right_pos = maximum_stage_displacement;
  
  TTF_Init();
  font = TTF_OpenFont( "OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
  
}




Report Scene::play()
{
  SDL_Event e;
  bool push = false;
  bool in_bounds = true;
  bool play = true;
  bool linked_scene_entry = false;
  uint count = 0;
  report = { Scene_States::exit_right, 0 };

  float avg_frames_per_second = 0;
  
  while( in_bounds && play && !linked_scene_entry )
  {
    
    avg_frames_per_second = ( counted_frames ) /
      ( SDL_GetTicks() / 1000.f );
    cout << avg_frames_per_second << "\r";
    
    if( main_character.get_position().at( 0 ) > stage_right_pos )
    {
      in_bounds = false;
      report.status = Scene_States::exit_right;
    }

    if( main_character.get_position().at( 0 ) < stage_left_pos )
    {
      in_bounds = false;
      report.status = Scene_States::exit_left;
    }
    
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        report.status = Scene_States::quit;
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
        if( e.key.keysym.sym == SDLK_LSHIFT )
        {
          interact();
          push = false;
        }
        if( e.key.keysym.sym == SDLK_RSHIFT )
        {
          cout << "e" << endl;
          linked_scene_entry = enter();
          push = false;
        }
        if( e.key.keysym.sym == SDLK_UP )
        {
          speak();
          push = false;
        }
        if( e.key.keysym.sym == SDLK_DOWN )
        {
          recruit();
          push = false;
        }
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
          count = ( count + 1 ) % 4;
          right( count );
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {
          count = ( count + 1 ) % 4;
          left( count );
        }
      }
      else
      {
        center( count );
      }
    }
    if( linked_scene_entry )
    {
      report.status = Scene_States::switch_tracks;
    }
  }
  
  return report;
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
  int main_char_width = 20;
  
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) - main_char_width;
  background.reset( stage_width );
  
  main_character.set_stage_pos(
    main_char_width, (-1 * maximum_stage_displacement + main_char_width ) );
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).set_stage_pos(
    main_char_width, (-1 * maximum_stage_displacement + main_char_width ) );
  }
}

void Scene::stage_right()
{
  int main_char_width = 20;
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) + 2 * main_char_width;
  background.reset( stage_width * -1 );
  
  main_character.set_stage_pos( window_size - 2 * main_char_width,
                                maximum_stage_displacement - main_char_width );
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).set_stage_pos(
      window_size - 2 * main_char_width,
      maximum_stage_displacement - main_char_width );
  }
}

void Scene::stage_junction( int junction_position )
{
  int main_char_width = 20;
  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );

  int center_screen = window_size / 2;

  int stage_center_left_edge = -1 * stage_center_edge;
  int stage_center_right_edge = stage_center_edge;

  background.reset( -1 * (junction_position + main_char_width) );

  int new_screen_position = center_screen;
  if( junction_position < stage_center_left_edge )
  {
    new_screen_position = center_screen - abs( stage_center_left_edge - junction_position );
  }
  else if( junction_position > stage_center_right_edge )
  {
    new_screen_position = center_screen + abs( stage_center_right_edge - junction_position ) - 4 * main_char_width;
  }
  
  main_character
    .set_stage_pos( new_screen_position,
                    junction_position);
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ).set_stage_pos(
      window_size / 2,
      junction_position);
  }
}

void Scene::set_junction( int position )
{
  scene_junction_positions.push_back( position );
}

void Scene::add_follower( Character character )
{
  following_characters.push_back( character );
}

void Scene::scroll_dialogue( string message, SDL_Renderer *renderer,
                             TTF_Font *font, Character *speaker,
                             bool happy )
{
  for( uint letters = 0; letters <= message.length();
       letters++ )
  {
    uint milliseconds = 250;
    SDL_RenderClear( renderer );
    background.draw();
    happy ? (*speaker).gasp() : (*speaker).happy();
    dialogue_display.display( message, renderer, font, letters );
    SDL_RenderPresent( renderer );
    ++counted_frames;
    usleep( milliseconds * milliseconds );
  }
}

void Scene::add_interaction( vector< string > messages,
                             int scene_position,
                             SDL_Renderer* renderer,
                             uint font_size )
{
  interactions.push_back(
    Interaction( messages, scene_position, renderer, font_size ) );
}

void Scene::prompt_interact()
{
  string prompt_interact = "left shift to interact";
 
  uint interact_proximity = 60;

  for( uint i = 0; i < interactions.size(); i++ )
  {
    int distance_from_interaction =
      abs( interactions.at( i ).get_scene_position() -
           main_character.get_position().at( 0 ) );
  
    if( distance_from_interaction < interact_proximity )
    {
      prompt_display.display( prompt_interact, renderer, font,
                              prompt_interact.length() );
    }
  } 
}

void Scene::interact()
{
  uint interact_proximity = 60;

  uint interaction_index = 0;
  bool interact = false;
  
  for( uint i = 0; i < interactions.size(); i++ )
  {
    int distance_from_interaction =
      abs( interactions.at( i ).get_scene_position() -
           main_character.get_position().at( 0 ) );
  
    if( distance_from_interaction < interact_proximity )
    {
      interaction_index = i;
      interact = true;
    }
  }

  if( interact )
  {
    cout << "interacting..." << endl;
    interactions.at( interaction_index ).interact( background );
  }
}
