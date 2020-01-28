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
           -> get_screen_position().at( 0 ) -
           main_character -> get_screen_position().at( 0 ) );
    
    if( distance_from_speaker < speak_proximity )
    {
      speak_index = i;
      convo( speak_index,
             scene_dialogue -> speak_to( following_characters.at(
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
      abs( characters.at( i ) -> get_screen_position().at( 0 ) -
           main_character -> get_screen_position().at( 0 ) );
    if( distance_from_recruit < recruit_proximity )
    {
      recruit_index = i;
      found_recruit = true;
      convo( recruit_index,
             scene_dialogue -> speak_to( characters.at(
                                           recruit_index ) ), false );
      recruit_success = confirm_recruit(
        characters.at( recruit_index ) );
      
    }
  }

  if( recruit_success )
  {
    following_characters.push_back( characters.at( recruit_index ) );
    vector< Character* > remaining_characters;
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
  background -> draw();
          
  character -> gasp();
  
  prompt_display -> display( prompt_recruitment, renderer, font,
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
          character -> set_recruited();
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
           main_character -> get_position().at( 0 ) );
  
    if( distance_from_entry < entry_proximity )
    {
      entry = true;
      report.character_position =
        main_character -> get_position().at( 0 );

      for( uint i = 0; i < following_characters.size(); i++ )
      {
        following_characters.at( i ) ->
          set_stage_pos( main_character
                         -> get_screen_position().at( 0 ),
                         main_character
                         -> get_position().at( 0 ) );
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
           main_character -> get_position().at( 0 ) );
  
    if( distance_from_entry < entry_proximity )
    {
      prompt_display -> display( prompt_enter, renderer, font,
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
      abs( characters.at( i ) -> get_screen_position().at( 0 ) -
           main_character -> get_screen_position().at( 0 ) );
    if( distance_from_speaker < speaker_proximity )
    {
      prompt_display -> display( prompt_speak, renderer, font,
                                 prompt_speak.length() );
    }
  }
}

void Scene::convo( uint character_index, Conversation* conversation,
                   bool following )
{
  
  SDL_RenderClear( renderer );
  background -> draw();

  Character* speaker;
  if( following )
  {
    speaker = following_characters.at( character_index );
  }
  else
  {
    speaker = characters.at( character_index );
  }
    
  bool is_happy = true;
  uint convo_length = conversation -> get_length();
  string message = conversation -> get_dialogue( 0 );

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
          background -> draw();
          
          is_happy = true;
          
          conversation_position++;

          if( conversation_position == convo_length )
          {
            talking = false;
          }

          if( conversation_position < convo_length )
          {
            message =
              conversation -> get_dialogue(
                conversation_position );

            scroll_dialogue( message, renderer, font,
                             speaker, is_happy );

          }
        }
        else if( e.key.keysym.sym == SDLK_LEFT )
        {
          
          SDL_RenderClear( renderer );
          background -> draw();
          
          is_happy = false;

          message = conversation -> get_angry_response();

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
  background -> draw();
  draw_npcs();
  
  ducklings( count );
  prompt_speak();

  main_character -> stand();

  prompt_interact();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
}

void Scene::jump()
{

  int initial_y_velocity = 30;
  int gravity = -4;

  int jump_offset = 3;

  int y_velocity = initial_y_velocity;
  while( y_velocity >= ( -1 * initial_y_velocity ) + jump_offset * gravity )
  {
    SDL_RenderClear( renderer );
    background -> draw();
    draw_npcs();
    ducklings( 1 );

    if( y_velocity >= -1 * initial_y_velocity )
    {
      main_character -> jump( y_velocity );

      int main_char_pos_x = main_character -> get_screen_position().at( 0 );
      int main_char_pos_y = main_character -> get_screen_position().at( 1 );

      main_character -> set_screen_position( main_char_pos_x, main_char_pos_y - y_velocity );
    }
    else
    {
      main_character -> stand();
    }

    if( y_velocity <= initial_y_velocity + jump_offset * gravity &&
        y_velocity >= -1 * initial_y_velocity + jump_offset * gravity )
    {
      for( uint i = 0; i < following_characters.size(); i++ )
      {
        following_characters.at( i ) -> jump( y_velocity + -1 * jump_offset * gravity );
        int char_pos_x = following_characters.at( i ) -> get_screen_position().at( 0 );
        int char_pos_y = following_characters.at( i ) -> get_screen_position().at( 1 );

        following_characters.at( i ) -> set_screen_position( char_pos_x, char_pos_y -
                                                             ( y_velocity + -1 * jump_offset * gravity ) ); 
      }
    }
    else
    {
      for( uint i = 0; i < following_characters.size(); i++ )
      {
        following_characters.at( i ) -> stand();
      }
    }

    y_velocity += gravity;

    SDL_RenderPresent( renderer );
    ++counted_frames;
    usleep( 1000 );
  }
  SDL_Delay( 50 );
}

int Scene::lateral_jump( int x_unit_vector, int y_velocity, uint count )
{
  int x_velocity = speed * x_unit_vector;

  int gravity = -4;
  int initial_y_velocity = 30;
  
  SDL_RenderClear( renderer );

  if( x_unit_vector == 1 )
  {      
    background -> left( speed );
  }
  else
  {
    background -> right( speed );
  }

  background -> draw();

  if( y_velocity >= -1 * initial_y_velocity )
  {
    main_character -> jump( x_velocity, y_velocity );
    int main_char_pos_x = main_character -> get_screen_position().at( 0 );
    int main_char_pos_y = main_character -> get_screen_position().at( 1 );

    main_character -> set_screen_position( main_char_pos_x, main_char_pos_y - y_velocity );
  }
  else
  {
    main_character -> jump( x_velocity, 0 );
  }

  int jump_offset = 3;

  if( y_velocity <= initial_y_velocity + jump_offset * gravity &&
      y_velocity >= -1 * initial_y_velocity + jump_offset * gravity )
  {
    for( uint i = 0; i < following_characters.size(); i++ )
    {
      following_characters.at( i ) -> jump( x_velocity, y_velocity + -1 * jump_offset * gravity );
      int char_pos_x = following_characters.at( i ) -> get_screen_position().at( 0 );
      int char_pos_y = following_characters.at( i ) -> get_screen_position().at( 1 );

      following_characters.at( i ) -> set_screen_position( char_pos_x, char_pos_y -
                                                           ( y_velocity + -1 * jump_offset * gravity ) ); 
    }
  }
  else
  {
    for( uint i = 0; i < following_characters.size(); i++ )
    {
      following_characters.at( i ) -> jump( x_velocity, 0 );
    }
  }

  if( x_unit_vector == 1 )
  {
    draw_npcs( false );
    // ducklings( false, count );
  }
  else
  {
    draw_npcs( true );
    // ducklings( true, count );
  }

  y_velocity += gravity;

  ++counted_frames;
  SDL_RenderPresent( renderer );
  return y_velocity;
}

int Scene::lateral_screen_jump( int x_unit_vector, int y_velocity, uint count )
{
  int x_velocity = 5 * x_unit_vector;

  int gravity = -4;

  SDL_RenderClear( renderer );
  background -> draw();
  draw_npcs();

  int initial_y_velocity = 30;

  if( y_velocity >= -1 * initial_y_velocity )
  {
    int main_char_pos_x = main_character -> get_screen_position().at( 0 );
    int main_char_pos_y = main_character -> get_screen_position().at( 1 );
    main_character -> jump( x_velocity, y_velocity );
    main_character -> set_screen_position( main_char_pos_x + x_velocity, main_char_pos_y - y_velocity );
  }
  else
  {
    main_character -> stand();
  }
  
  int jump_offset = 3;

  if( y_velocity <= initial_y_velocity + jump_offset * gravity &&
      y_velocity >= -1 * initial_y_velocity + jump_offset * gravity )
  {
    for( uint i = 0; i < following_characters.size(); i++ )
    {
      following_characters.at( i ) -> jump( x_velocity, y_velocity + abs( jump_offset * gravity ) );
      int char_pos_x = following_characters.at( i ) -> get_screen_position().at( 0 );
      int char_pos_y = following_characters.at( i ) -> get_screen_position().at( 1 );

      following_characters.at( i ) -> set_screen_position( char_pos_x, char_pos_y -
                                                           ( y_velocity + abs( jump_offset * gravity ) ) ); 
    }
  }
  else
  {
    for( uint i = 0; i < following_characters.size(); i++ )
    {
      following_characters.at( i ) -> stand();
    }
  }
  
  ducklings( count );

  y_velocity += gravity;

  ++counted_frames;
  SDL_RenderPresent( renderer );
  return y_velocity;
}

void Scene::air_right( uint count )
{
  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character -> get_position().at( 0 );

  int gravity = -4;
  int initial_y_velocity = 30;
  int y_velocity = initial_y_velocity;
  double increment = 0.1;
  int jump_offset = 3;

  while( y_velocity >= -1 * (initial_y_velocity) + jump_offset * gravity )
  {
    main_char_pos = main_character -> get_position().at( 0 );
    if( main_char_pos < ( -1 * stage_center_edge ) ||
        main_char_pos >= stage_center_edge )
    {
      background -> draw();
      draw_npcs();
      ducklings( count );
      y_velocity = lateral_screen_jump( 1, y_velocity, count );
    } 
    else
    {
      background -> draw();
      ducklings( false, count );
      y_velocity = lateral_jump( 1, y_velocity, count );
    }
    increment += increment;
    count = ( count + ( int ) increment ) % 4;
  }
  SDL_Delay( 50 );
}

void Scene::right( uint count )
{
  SDL_RenderClear( renderer );

  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character -> get_position().at( 0 );
  if( main_char_pos < ( -1 * stage_center_edge ) ||
      main_char_pos >= stage_center_edge )
  {
    background -> draw();
    draw_npcs();
    ducklings( count );
    main_character -> walk_right( speed, count );
    main_character -> update_pos( true, speed );
  } 
  else
  {
    background -> left( speed );
    background -> draw();
    draw_npcs( false );
    ducklings( false, count );
    main_character -> walk_right( speed, count );
  }
  prompt_interact();
  prompt_speak();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
  SDL_Delay( 40 );
}

void Scene::air_left( uint count )
{
  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character -> get_position().at( 0 );

  int gravity = -4;
  int initial_y_velocity = 30;
  int y_velocity = initial_y_velocity;
  double increment = 0.1;
  int jump_offset = 3;
  
  while( y_velocity >= -1 * ( initial_y_velocity ) + jump_offset * gravity )
  {
    main_char_pos = main_character -> get_position().at( 0 );
    if( main_char_pos < ( -1 * stage_center_edge ) ||
        main_char_pos >= stage_center_edge )
    {
      background -> draw();
      draw_npcs();
      ducklings( count );
      y_velocity = lateral_screen_jump( -1, y_velocity, count );
    } 
    else
    {
      background -> draw();
      ducklings( true, count );
      y_velocity = lateral_jump( -1, y_velocity, count );
    }
    increment += increment;
    count = ( count + ( int ) increment ) % 4;
  }
  SDL_Delay( 50 );
}

void Scene::left( uint count )
{
  SDL_RenderClear( renderer );

  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );
  int main_char_pos = main_character -> get_position().at( 0 );
  
  if( main_char_pos < ( -1 * stage_center_edge ) ||
      main_char_pos >= stage_center_edge )
  {
    background -> draw();
    draw_npcs();
    ducklings( count );
    main_character -> walk_left( speed, count );
    main_character -> update_pos( false, speed );
  } 
  else
  {
    background -> right( speed );
    background -> draw();
    draw_npcs( true );
    ducklings( true, count ); 
    main_character -> walk_left( speed, count );
  }
  prompt_interact();
  prompt_speak();
  prompt_enter_linked_scene();
  SDL_RenderPresent( renderer );
  ++counted_frames;
  SDL_Delay( 40 );
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
    following_characters.at( i )->update_pos( left, speed );
    if( i == 0 )
    {
      following_characters.at( i )->follow(
        main_character, speed, count );
    }
    else
    {
      following_characters.at(
        i ) -> follow( following_characters.at( i - 1 ),
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
      following_characters.at( i )->follow(
        main_character, speed, count );
    }
    else
    {
      following_characters.at( i ) -> follow(
        following_characters.at( i - 1 ),
        speed, count );
    }
  }
}

void Scene::draw_npcs( bool left )
{
  for( uint i = 0; i < characters.size(); i++ )
  {
    characters.at( i ) -> update_pos( left, speed );
    characters.at( i ) -> stand();
  }
}

void Scene::draw_npcs()
{
  for( uint i = 0; i < characters.size(); i++ )
  {
    characters.at( i ) -> stand();
  }
}

vector< Character* > Scene::following_characters;





Scene::Scene(SDL_Renderer *param_renderer,
             Background *param_background,
             vector< Character* > param_characters,
             Character *param_main_character,
	     Script *param_scene_dialogue,
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
  dialogue_display( new Text_box( 25, 25, 100, 300 ) ),
  prompt_display( new Text_box( 25, 400, 100, 300 ) )
{
  
  window_size = 1000;
  stage_left_pos = maximum_stage_displacement * -1;
  stage_right_pos = maximum_stage_displacement;
  previous_junction_position = INT_MAX;
  
  TTF_Init();
  font = TTF_OpenFont( "/home/jared/Games/Labyrinth/resources/OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
}

Scene::~Scene()
{
  cout << "scene destroyed" << endl;
  if( main_character )
  {
    main_character -> ~Character();
    main_character = NULL;
  }

  if( background )
  {
    background -> ~Background();
    background = NULL;
  }
  
  for( uint i = 0; i < characters.size(); i++ )
  {
    if( characters.at( i ) )
    {
      characters.at( i ) -> ~Character();
      characters.at( i ) = NULL;
    }
  }
}

Report Scene::play()
{
  SDL_Event e;
  const Uint8 *state = SDL_GetKeyboardState( NULL );
  bool push = false;
  bool in_bounds = true;
  bool play = true;
  bool linked_scene_entry = false;
  uint count = 0;
  report = { Scene_States::exit_right, 0};

  float avg_frames_per_second = 0;
  
  while( in_bounds && play && !linked_scene_entry )
  {
    SDL_PumpEvents();
    
    int x_direction = 0;
    int y_direction = 0;

    avg_frames_per_second = ( counted_frames ) /
      ( SDL_GetTicks() / 1000.f );
    cout << avg_frames_per_second << "\r";
    
    if( main_character -> get_position().at( 0 ) > stage_right_pos )
    {
      in_bounds = false;
      report.status = Scene_States::exit_right;
    }

    if( main_character -> get_position().at( 0 ) < stage_left_pos )
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
      if( push || movement_key_pressed( state ) )
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
        if( e.key.keysym.sym == SDLK_DOWN )
        {
          recruit();
          push = false;
        }
        if( e.key.keysym.sym == SDLK_UP )
        {
          y_direction = 1;
        }
        if( !state[ SDL_SCANCODE_UP ] )
        {
          y_direction = 0;
        }
        if( e.key.keysym.sym == SDLK_RIGHT || state[ SDL_SCANCODE_RIGHT ] )
        {
          count = ( count + 1 ) % 4;
          x_direction = 1;
        }
        else if( e.key.keysym.sym == SDLK_LEFT || state[ SDL_SCANCODE_LEFT ] )
        {
          count = ( count + 1 ) % 4;
          x_direction = -1;
        }
      }
      else
      {
        x_direction = 0;
        y_direction = 0;
      }
    }
    if( linked_scene_entry )
    {
      report.status = Scene_States::switch_tracks;
    }
    marionette( x_direction, y_direction, count );
  }
  
  return report;
}

bool Scene::movement_key_pressed( const Uint8* state )
{
  return state[ SDL_SCANCODE_LEFT ] || state[ SDL_SCANCODE_RIGHT ];
}

void Scene::marionette( int x_direction, int y_direction, uint cadence )
{
  if( x_direction > 0 )
  {
    right( cadence );
  }

  if( x_direction < 0 )
  {
    left( cadence );
  }

  if( x_direction == 0 )
  {
    center( cadence );
  }

  if( y_direction > 0 && x_direction == 0 )
  {
    jump();
  }

  if( y_direction != 0 && x_direction < 0 )
  {
    air_left( cadence );
  }

  if( y_direction != 0 && x_direction > 0 )
  {
    air_right( cadence );
  }
}

void Scene::set_previous_junction_position( int position )
{
  previous_junction_position = position;
}

int Scene::get_previous_junction_position()
{
  return previous_junction_position;
}

void Scene::reset()
{
  background -> reset();
  main_character -> reset();
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ) -> reset();
  }
}

void Scene::stage_left_barrier()
{
  int main_char_width = 20;
  
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) - main_char_width;
  
  main_character -> set_stage_pos(
    main_char_width, (-1 * maximum_stage_displacement + main_char_width ) );
}

void Scene::stage_left()
{
  int main_char_width = 20;
  
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) - main_char_width;
  background -> reset( stage_width );
  
  main_character -> set_stage_pos(
    main_char_width, (-1 * maximum_stage_displacement + main_char_width ) );
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ) -> set_stage_pos(
      main_char_width, (-1 * maximum_stage_displacement + main_char_width ) );
  }
}

void Scene::stage_right()
{
  int main_char_width = 20;
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) + 2 * main_char_width;
  background -> reset( stage_width * -1 );
  
  main_character -> set_stage_pos( window_size - 2 * main_char_width,
                                   maximum_stage_displacement - main_char_width );
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ) -> set_stage_pos(
      window_size - 2 * main_char_width,
      maximum_stage_displacement - main_char_width );
  }
}

void Scene::stage_right_barrier()
{
  int main_char_width = 20;
  int stage_width =
    maximum_stage_displacement - ( window_size / 2 ) + 2 * main_char_width;
  
  main_character -> set_stage_pos( window_size - 2 * main_char_width,
                                   maximum_stage_displacement - main_char_width );  
}


void Scene::stage_junction( int junction_position )
{  
  int main_char_width = 20;
  int stage_center_edge = maximum_stage_displacement - ( window_size / 2 );

  int center_screen = window_size / 2;

  int stage_center_left_edge = -1 * stage_center_edge;
  int stage_center_right_edge = stage_center_edge;

  int new_screen_position = center_screen;
  int new_background_position = ( -1 * junction_position + main_char_width );
  if( junction_position < stage_center_left_edge )
  {
    new_screen_position = center_screen - abs( stage_center_left_edge - junction_position );
    new_background_position = stage_center_right_edge;
  }
  else if( junction_position > stage_center_right_edge )
  {
    new_screen_position = center_screen + abs( stage_center_right_edge - junction_position ) - 4 * main_char_width;
    new_background_position = stage_center_left_edge;
  }
  
  background -> reset( new_background_position );
  
  main_character
    -> set_stage_pos( new_screen_position,
                      junction_position);

  for( uint i = 0; i < characters.size(); i++ )
  {
    int old_character_position = characters.at( i ) ->
      get_position().at( 0 );

    int old_character_screen_position = characters.at( i ) ->
      get_screen_position().at( 0 );
    
    int new_character_position;
    int new_character_screen_position;

    if( previous_junction_position != INT_MAX )
    {
      if( previous_junction_position > junction_position )
      {
        new_character_position = old_character_position +
          abs( previous_junction_position -
               junction_position );

        new_character_screen_position = old_character_screen_position
          + abs( previous_junction_position -
                 junction_position );
      }
      else
      {
        new_character_position = old_character_position -
          abs( previous_junction_position -
               junction_position );

        new_character_screen_position = old_character_screen_position
          - abs( previous_junction_position -
                 junction_position );
      }

      characters.at( i ) -> set_stage_pos(
        new_character_screen_position,
        new_character_position );
    }
  }
  
  for( uint i = 0; i < following_characters.size(); i++ )
  {
    following_characters.at( i ) -> set_stage_pos(
      new_screen_position,
      junction_position);
  }

  previous_junction_position = junction_position;
}

void Scene::set_junction( int position )
{
  scene_junction_positions.push_back( position );
}

void Scene::add_follower( Character *character )
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
    background -> draw();
    happy ? speaker -> gasp() : speaker -> happy();
    dialogue_display -> display( message, renderer, font, letters );
    SDL_RenderPresent( renderer );
    ++counted_frames;
    usleep( milliseconds * milliseconds );
  }
}

void Scene::scroll_dialogue( string message, SDL_Renderer *renderer,
                             TTF_Font *font )
{
  for( uint letters = 0; letters <= message.length();
       letters++ )
  {
    uint milliseconds = 250;
    SDL_RenderClear( renderer );
    background -> draw();
    
    main_character -> stand();
    for( Character *follower : following_characters )
    {
      follower -> stand();
    }
    
    dialogue_display -> display( message, renderer, font, letters );
    SDL_RenderPresent( renderer );
    ++counted_frames;
    usleep( milliseconds * milliseconds );
  }
}


void Scene::add_interaction( vector< string > messages,
                             int scene_position,
                             SDL_Renderer* renderer )
{
  interactions.push_back(
    new Interaction( messages, scene_position, renderer ) );
}

void Scene::prompt_interact()
{
  string prompt_interact = "left shift to interact";
 
  uint interact_proximity = 60;

  for( uint i = 0; i < interactions.size(); i++ )
  {
    int distance_from_interaction =
      abs( interactions.at( i ) -> get_scene_position() -
           main_character -> get_position().at( 0 ) );
  
    if( distance_from_interaction < interact_proximity )
    {
      prompt_display -> display( prompt_interact, renderer, font,
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
      abs( interactions.at( i ) -> get_scene_position() -
           main_character -> get_position().at( 0 ) );
  
    if( distance_from_interaction < interact_proximity )
    {
      interaction_index = i;
      interact = true;
    }
  }

  if( interact )
  {
    cout << "interacting..." << endl;
    perform_interaction( interactions.at( interaction_index ) );
  }
}

void Scene::perform_interaction( Interaction *interaction )
{
  SDL_RenderClear( renderer );
  background -> draw();

  uint interaction_position = 0;
  
  string current_message
    = interaction -> get_message( interaction_position );
  
  uint interaction_length = interaction -> get_interaction_length();

  bool interacting = true;
  bool next = true;
  SDL_Event e;
  while( interacting )
  {
    while( SDL_PollEvent( &e ) )
    {
      if( next && interaction_position < interaction_length )
      {
        scroll_dialogue(
          interaction -> get_message(
            interaction_position ), renderer, font );
        
        next = false;
      }

      if( interaction_position == interaction_length )
      {
        interacting = false;
      }
      
      if( e.type == SDL_KEYDOWN )
      {
        if( e.key.keysym.sym == SDLK_RIGHT )
        {
          next = true;
          interaction_position++;
        }
        else
        {
          interacting = false;
        }
      }
    }
  }
}
