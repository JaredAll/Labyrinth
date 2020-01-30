#include "panel.h"


Panel::Panel( Background *param_background,
              SDL_Renderer* param_ren ) :
  main_display( new Text_box( 200, 200, 200, 600 ) ),
  sub_display( new Text_box( 225, 275, 100, 400 ) ),
  background( param_background ),
  renderer( param_ren )
{
  TTF_Init();
  font = TTF_OpenFont( "/home/jared/Games/Labyrinth/resources/OpenSans-Bold.ttf", 16 );

  if( font == NULL )
  {
    printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
  }
}

bool Panel::display()
{
  bool begin = false;
  bool quit = false;
  SDL_Event e;

  while( !begin && !quit )
  {
    background -> draw();
      
    string main_message = "DENIZEN DIRK";
    main_display -> display( main_message, renderer, font,
                          main_message.length() );
    
    string sub_message = "press any button to play";
    sub_display -> display( sub_message, renderer, font,
                         sub_message.length() );
    
    SDL_RenderPresent( renderer );

    SDL_PollEvent( &e );
    if( e.type == SDL_QUIT )
    {
      quit = true;
    }
    if( e.type == SDL_KEYDOWN )
    {
      begin = true;
    }
  }
  return begin;
}

