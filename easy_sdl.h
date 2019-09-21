#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
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
                   int x, int y, SDL_Rect *clip = nullptr,
                   SDL_Rect *dst = nullptr );

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
                    SDL_Rect *dst, SDL_Rect *clip = nullptr );

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
                        SDL_Rect *dst, SDL_Rect *clip );

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


