#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "cleanup.h"
#include <iostream>
#include <vector>

using namespace std;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError( std::ostream &os, const std::string &msg );

/**
* Loads a BMP image into a texture on the rendering device
* @param file The BMP image file to load
* @param ren The renderer to load the texture onto
* @return the loaded texture, or nullptr if something went wrong.
*/
void renderTexture(SDL_Texture *tex, SDL_Renderer *ren,
                   int x, int y, SDL_Rect *clip = nullptr );

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren);

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTexture( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect dst, SDL_Rect *clip = nullptr );

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

int main( int argc, char* argv[] )
{

  //initialize video
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    logSDLError( std::cout, "SDL_Init" );
    return 1;
  }


  //create window
  int window_width = 800;
  int window_height = 500;
  SDL_Window *win = SDL_CreateWindow("Labyrinth sketch 2",
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window_width, window_height,
                                     SDL_WINDOW_SHOWN);
  if (win == nullptr)
  {
    logSDLError( std::cout, "CreateWindow" );
    SDL_Quit();
    return 1;
  }

  //create renderer
  SDL_Renderer *ren =
    SDL_CreateRenderer(win, -1,
                       SDL_RENDERER_ACCELERATED
                       | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr)
  {
    cleanup( win );
    logSDLError( std::cout, "CreateRenderer" );
    SDL_Quit();
    return 1;
  }

  //get the background
  SDL_Texture *background = loadTexture( "background1.png", ren );
  if (background == nullptr)
  {
    cleanup( ren, win );
    logSDLError( std::cout, "loadTexture" );
    SDL_Quit();
    return 1;
  }

  //get the fatty
  SDL_Texture *faces = loadTexture( "facesheet.png", ren );
  if( faces == nullptr )
  {
    cleanup( ren, win );
    logSDLError( std::cout, "loadTexture" );
    SDL_Quit();
    return 1;
  }

  //get the speech
  SDL_Texture *speech = loadTexture( "speech.png", ren );
  if( speech == nullptr )
  {
    cleanup( ren, win );
    logSDLError( std::cout, "loadTexture" );
    SDL_Quit();
    return 1;
  }

  //get the speech
  SDL_Texture *speech_2 = loadTexture( "speech_2.png", ren );
  if( speech_2 == nullptr )
  {
    cleanup( ren, win );
    logSDLError( std::cout, "loadTexture" );
    SDL_Quit();
    return 1;
  }

  SDL_Rect speech_box;
  speech_box.x = 50;
  speech_box.y = 50;
  speech_box.w = 300;
  speech_box.h = 200;

  vector< SDL_Texture* > dialogue;
  dialogue.push_back( speech );
  dialogue.push_back( speech_2 );

  uint face_x = 400;
  uint face_y = 0;

  //clip sheet for fatty walking
  uint face_clip_width = 400;
  uint face_clip_height = 500;
  
  uint num_sprites = 2;
  vector< SDL_Rect > face_expressions;
  for( uint i = 0; i < num_sprites; i++ )
  {
    SDL_Rect face_clip;
    face_expressions.push_back( face_clip );
    face_expressions.at( i ).x = i * ( face_clip_width );
    face_expressions.at( i ).y = 0;
    face_expressions.at( i ).h = face_clip_height;
    face_expressions.at( i ).w = face_clip_width;
  }

  uint expression = 0;
  uint which_speech = 0;

  //render until click the x
  uint x_pos = 0;
  uint y_pos = 0;
  
  SDL_Event e;
  bool quit = false;
  while( !quit )
  {
    while( SDL_PollEvent( &e ) )
    {
      if( e.type == SDL_QUIT )
      {
        quit = true;
      }

      if( e.type == SDL_KEYDOWN )
      {
        switch( e.key.keysym.sym )
        {

        case SDLK_1:
          expression = 0;
          which_speech = 0;
          break;

        case SDLK_2:
          expression = 1;
          which_speech = 1;
          break;

        default:
          break;
        }
      }
    }
    
    SDL_RenderClear( ren );
    renderTexture( background, ren, x_pos, y_pos );
    renderTexture( faces, ren, face_x, face_y,
                   &face_expressions.at( expression ) );
    renderTexture( dialogue.at( which_speech ), ren, speech_box );
    SDL_RenderPresent( ren );
  }
  cleanup( background, ren, win, faces );
  return 1;
  
}


void logSDLError( std::ostream &os, const std::string &msg )
{
  os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
{
  SDL_Texture *texture = IMG_LoadTexture( ren, file.c_str() );
  if ( texture == nullptr )
    {
    logSDLError( std::cout, "LoadTexture" );
  }
  return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren,
                   int x, int y, SDL_Rect *clip )
{
  //Setup the destination rectangle to be at the position we want
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if( clip != nullptr )
  {
    dst.w = clip -> w;
    dst.h = clip -> h;
  }
  else
  {
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(ren, tex, NULL, &dst);
  }
  renderTexture( tex, ren, dst, clip );
}

void renderTexture( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect dst, SDL_Rect *clip )
{
  SDL_RenderCopy( ren, tex, clip, &dst );
}
