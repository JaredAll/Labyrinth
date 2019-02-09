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

/**
* Draw an SDL_Texture to an SDL_Renderer at some destination rect
* taking a clip of the texture if desired and flipped horizontally
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param dst The destination rectangle to render the texture to
* @param clip The sub-section of the texture to draw (clipping rect)
*		default of nullptr draws the entire texture
*/
void renderTextureFlip( SDL_Texture *tex, SDL_Renderer *ren,
                        SDL_Rect dst, SDL_Rect *clip );

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height and flipped horizontally
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
* @param clip the portion of the texture to draw
*/
void renderTextureFlip(SDL_Texture *tex, SDL_Renderer *ren,
                       int x, int y, SDL_Rect *clip );


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

void renderTextureFlip(SDL_Texture *tex, SDL_Renderer *ren,
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
    SDL_RenderCopyEx(ren, tex, NULL, &dst, 0, 0,
                     SDL_FLIP_HORIZONTAL);
  }
  renderTextureFlip( tex, ren, dst, clip );
}

void renderTextureFlip( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect dst, SDL_Rect *clip )
{
  SDL_RenderCopyEx( ren, tex, clip, &dst, 0, 0,
                    SDL_FLIP_HORIZONTAL );
}


void renderTexture( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect dst, SDL_Rect *clip )
{
  SDL_RenderCopy( ren, tex, clip, &dst );
}
