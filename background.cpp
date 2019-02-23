#include "background.h"
Background::Background( vector< SpriteLayer > param_layers )
: layers( param_layers )
{

}

Background::Background()
{
  vector< SpriteLayer > new_layers;
  layers = new_layers;
}

void Background::add_layer( SpriteLayer layer )
{
  layers.push_back( layer );
}

void Background::left( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).left( speed );
  }
}

void Background::right( uint speed )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).right( speed );
  }
}

void Background::draw()
{
  for( SpriteLayer layer : layers )
  {
    layer.draw();
  }
}

void Background::reset()
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).reset();
  }
}

void Background::reset( int offset )
{
  for( uint sprite = 0; sprite < layers.size(); sprite++  )
  {
    layers.at( sprite ).reset( offset );
  }
}
