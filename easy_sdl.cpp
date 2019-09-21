#include "easy_sdl.h"
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
                   int x, int y, SDL_Rect *clip,
                   SDL_Rect* dst )
{
  //Setup the destination rectangle to be at the position we want
  dst -> x = x;
  dst -> y = y;
  if( clip != nullptr )
  {
    dst -> w = clip -> w;
    dst -> h = clip -> h;
  }
  else
  {
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &( dst -> w ), &( dst -> h ) );
    SDL_RenderCopy(ren, tex, NULL, dst);
  }
  renderTexture( tex, ren, dst, clip );
}

void renderTextureFlip(SDL_Texture *tex, SDL_Renderer *ren,
                   int x, int y, SDL_Rect *clip )
{
  //Setup the destination rectangle to be at the position we want
  SDL_Rect *dst = new SDL_Rect();
  dst -> x = x;
  dst -> y = y;
  if( clip != nullptr )
  {
    dst -> w = clip -> w;
    dst -> h = clip -> h;
  }
  else
  {
    //Query the texture to get its width and height to use
    SDL_QueryTexture(tex, NULL, NULL, &( dst -> w ), &( dst -> h ) );
    SDL_RenderCopyEx(ren, tex, NULL, dst, 0, 0,
                     SDL_FLIP_HORIZONTAL);
  }
  renderTextureFlip( tex, ren, dst, clip );
}

void renderTextureFlip( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect *dst, SDL_Rect *clip )
{
  SDL_RenderCopyEx( ren, tex, clip, dst, 0, 0,
                    SDL_FLIP_HORIZONTAL );
}


void renderTexture( SDL_Texture *tex, SDL_Renderer *ren,
                    SDL_Rect *dst, SDL_Rect *clip )
{
  SDL_RenderCopy( ren, tex, clip, dst );
}
