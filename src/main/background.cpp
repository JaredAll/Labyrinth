#include "background.h"
Background::Background( vector< SpriteLayer* > param_layers,
                        SDL_Renderer *ren )
  : layers( param_layers ), blank_screen(
    new SpriteLayer( "/home/jared/Games/Labyrinth/resources/sprites/blank_screen.png", ren, 0, 0, 0 ) )
{

}

Background::~Background()
{
  for( uint i = 0; i < layers.size(); i++ )
  {
    if( layers.at( i ) )
    {
      layers.at( i ) -> ~SpriteLayer();
      layers.at( i ) = NULL;
    }
  }
}

Background::Background( SDL_Renderer *ren ) :
blank_screen( new SpriteLayer( "/home/jared/Games/Labyrinth/resources/sprites/blank_screen.png", ren,
                           0, 0, 0 ) )
{
  vector< SpriteLayer* > new_layers;
  layers = new_layers;
}

void Background::add_layer( SpriteLayer *layer )
{
  layers.push_back( layer );
}

void Background::left( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ) -> left( speed );
  }
}

void Background::right( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ) -> right( speed );
  }
}

void Background::draw()
{
  for( SpriteLayer *layer : layers )
  {
    layer -> draw();
  }
}

void Background::blank()
{
  blank_screen -> draw();
}

void Background::reset()
{
  for( uint sprite = 0; sprite < layers.size(); sprite++ )
  {
    layers.at( sprite ) -> reset();
  }
}

void Background::reset( int offset )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ) -> reset( offset );
  }
}
