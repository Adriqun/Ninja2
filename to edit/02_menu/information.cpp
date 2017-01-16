/**
    information.h
    Purpose: class Information - to show text during keyboard state.

    @author Adrian Michalek
    @version 2016.11.02
	@email adrmic98@gmail.com
*/

#include "information.h"


Information::Information()
{
    nr = 0;
	text = NULL;
	
	info_nr = 0;
	info_text = NULL;
}

Information::~Information()
{
	if( text != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			text[ i ].free();
		}
		
		delete [] text;
		text = NULL;
		nr = 0;
	}
	
	if( info_text != NULL )
	{
		for( int i = 0; i < info_nr; i++ )
		{
			info_text[ i ].free();
		}
		
		delete [] info_text;
		info_text = NULL;
		info_nr = 0;
	}
}



void Information::load( int right, int top, int screen_h )
{
	nr = 8;
	text = new MyText[ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].setName( "information-text nr " + std::to_string( i ) );
		text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x98, 0x98, 0x98 );
	}
	
	
	text[ 0 ].setText( "Back" );
	text[ 1 ].setText( "esc" );
	
	text[ 2 ].setText( "Quit" );
	text[ 3 ].setText( "q" );
	
	text[ 4 ].setText( "Back in quit log" );
	text[ 5 ].setText( "b" );
	
	text[ 6 ].setText( "Pause" );
	text[ 7 ].setText( "p" );
	
	text[ 0 ].setPosition( right + 120, top );
	text[ 1 ].setPosition( right + 350, top );
	for( int i = 2; i < nr -1; i += 2 )
	{
		text[ i ].setPosition( right + 120, text[ i -2 ].getBot() + 10 );
		text[ i +1 ].setPosition( right + 350, text[ i -2 ].getBot() + 10 );
	}
	
	text[ 6 ].setPosition( text[ 6 ].getX() , text[ 6 ].getY() -7 );
	text[ 7 ].setPosition( text[ 7 ].getX() , text[ 7 ].getY() -8 );
	
	// info
	info_nr = 7;
	info_text = new MyText[ info_nr ];
	
	for( int i = 0; i < info_nr; i ++ )
	{
		info_text[ i ].setName( "information-text nr " + std::to_string( i ) );
		if( i != 1 || i != 3 || i != 5 )
			info_text[ i ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	}
	//8Ca93e
	//8c001a
	info_text[ 5 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x8C, 0x00, 0x1A );
	info_text[ 1 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0xFF, 0xDE, 0x00 );
	info_text[ 3 ].setFont( "data/fonts/Jaapokki-Regular.otf", 25, 0x8C, 0xA9, 0x3E );
	
	info_text[ 0 ].setText( "instructions: " );
	info_text[ 1 ].setText( "click on" );
	info_text[ 2 ].setText( " activity, press " );
	info_text[ 3 ].setText( "'+'" );
	info_text[ 4 ].setText( " to add, press " );
	info_text[ 5 ].setText( "'-'" );
	info_text[ 6 ].setText( " to remove" );
	
	info_text[ 0 ].setPosition( 10, screen_h - info_text[ 0 ].getHeight() - 20 );
	for( int i = 1; i < info_nr; i ++ )
	{
		info_text[ i ].setPosition( info_text[ i -1 ].getRight() + 10, info_text[ 0 ].getY() );
	}
}

void Information::draw( sf::RenderWindow &window )
{
	for( int i = 0; i < nr; i++ )
	{
		window.draw( text[ i ].get() );
	}
	
	for( int i = 0; i < info_nr; i++ )
	{
		window.draw( info_text[ i ].get() );
	}
}

void Information::fadein( int j, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadein( j, max );
	}
	
	for( int i = 0; i < info_nr; i++ )
	{
		info_text[ i ].fadein( j, max );
	}
}

void Information::fadeout( int j, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		text[ i ].fadeout( j, min );
	}
	
	for( int i = 0; i < info_nr; i++ )
	{
		info_text[ i ].fadeout( j, min );
	}
}