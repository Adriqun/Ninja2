#include "heart.h"
#include <fstream>

Heart_bit::Heart_bit()
{
	x = y = 0;
	alpha = 0;
}

Heart_bit::~Heart_bit()
{
	free();
}

void Heart_bit::free()
{
	x = y = 0;
	alpha = 0;
}



Heart::Heart()
{
	max = 0;
	life = 0;
}

Heart::~Heart()
{
	free();
}

void Heart::free()
{
	max = 0;
	life = 0;
	
	if( !fill_bits.empty() )
	{
		for( auto &it :fill_bits )
		{
			it->free();
		}
		
		fill_bits.clear();
	}
	
	if( !grey_bits.empty() )
	{
		for( auto &it :grey_bits )
		{
			it->free();
		}
		
		grey_bits.clear();
	}
	
	if( !frame_bits.empty() )
	{
		for( auto &it :frame_bits )
		{
			it->free();
		}
		
		frame_bits.clear();
	}
	
	fill.free();
	grey.free();
	frame.free();
}

void Heart::reset()
{
	life = fill_bits.size() *0xFF;
	harm( 0 );
}



void Heart::load()
{
	free();
	
	fstream file;
	
	file.open( "data/txt/panel/heart.txt" );
	if( file.bad() )
	{
		printf( "Cannot open data/txt/panel/heart.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		max = strToInt( line );
	}
	file.close();
	
	file.open( "data/txt/panel/heart_current.txt" );
	if( file.bad() )
	{
		printf( "Cannot open data/txt/panel/heart_current.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		int nr = strToInt( line );
		
		fill.setName( "heart-fill" );
		fill.load( "data/sprites/hero/heart/fill.png");
		
		frame.setName( "heart-frame" );
		frame.load( "data/sprites/hero/heart/frame.png");
		
		grey.setName( "heart-grey_square" );
		grey.load( "data/sprites/hero/grey/grey_square.png");
		
		for( int i = 0; i < nr; i++ )
		{
			fill_bits.push_back( new Heart_bit() );
			fill_bits[ fill_bits.size() -1 ]->alpha = 0xFF;
			fill_bits[ fill_bits.size() -1 ]->x = 10 + (fill.getWidth() +10) *i;
			fill_bits[ fill_bits.size() -1 ]->y = 10;
			
			frame_bits.push_back( new Heart_bit() );
			frame_bits[ frame_bits.size() -1 ]->x = 10 + (frame.getWidth() +10) *i;
			frame_bits[ frame_bits.size() -1 ]->y = 10;
		}
		
		for( int i = 0; i < max; i++ )
		{
			grey_bits.push_back( new Heart_bit() );
			grey_bits[ grey_bits.size() -1 ]->x = 5 + (frame.getWidth() +10) *i;
			grey_bits[ grey_bits.size() -1 ]->y = 5;
		}
	}
	file.close();

	reset();
}

void Heart::draw( sf::RenderWindow* &window )
{
	for( auto &it :grey_bits )
	{
		grey.setPosition( it->x, it->y );
		window->draw( grey.get() );
	}
	
	for( auto &it :fill_bits )
	{
		fill.setPosition( it->x, it->y );
		fill.setAlpha( it->alpha );
		window->draw( fill.get() );
	}
	
	for( auto &it :frame_bits )
	{
		frame.setPosition( it->x, it->y );
		window->draw( frame.get() );
	}
	
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 0 ) ) )
	{
		harm( -4 );
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 1 ) ) )
	{
		harm( 4 );
	}
}



void Heart::fadein( int v, int max )
{
	grey.fadein( v, max );
	frame.fadein( v, max );
}

void Heart::fadeout( int v, int min )
{
	fill.fadeout( v, min );
	grey.fadeout( v, min );
	frame.fadeout( v, min );
}



void Heart::harm( int damage )
{
	life += damage;
	
	int temporary_life = 0;
	for( auto &it :fill_bits )
	{
		temporary_life += it->alpha;
	}
	
	if( temporary_life != life )
	{
		temporary_life = life;
		
		for( auto &it :fill_bits )
		{
			it->alpha = 0;
		}
		
		if( temporary_life > 0 )
		{
			for( auto &it :fill_bits )
			{
				if( temporary_life < 0xFF )
				{
					it->alpha = temporary_life;
					break;
				}
				else
				{
					it->alpha = 0xFF;
				}
				
				temporary_life -= 0xFF;
			}
		}
	}
}

bool Heart::isDead()
{
	if( life <= 0 )
	{
		return true;
	}
	
	return false;
}

int Heart::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp +s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}