#include "desert/play_desert.h"

Play_desert::Play_desert()
{
	state = new State;
	hero = new Hero;
	bg = new MySprite;
}

Play_desert::~Play_desert()
{
	free();
}

void Play_desert::free()
{
	delete state;
	delete hero;
	delete bg;
}

	
void Play_desert::load( int screen_w, int screen_h )
{
	hero->load( screen_w, screen_h );
	bg->setName( "play_desert-bg" );
	bg->load( "data/sprites/play/3.png" );
	//...
}


void Play_desert::handle( sf::Event &event )
{
	hero->handle( event );
}

void Play_desert::draw( sf::RenderWindow* &window )
{
	window->draw( bg->get() );
	hero->draw( window );
	
	bg->fadein( 2 );
	hero->fadein( 2 );
}

	
State* Play_desert::getState()
{
	return state;
}

void Play_desert::set( State* state )
{
	this->state = state;
	state->state = 0;
	
	/*
	// Set chunks
	if( !state->cSwitch )
	{
		backtomenu->turn();
		choice->turn();
	}
	
	// Set music volume
	music->setVolume( state->mVolume );
	
	// Set chunk volume
	backtomenu->setVolume( state->cVolume );
	choice->setVolume( state->cVolume );
	*/
}

	
bool Play_desert::isQuit()
{
	if( state->state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_desert::nextState()
{
	if( state->state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_desert::backToLevel()
{
	if( state->state == 2 )
	{
		state->state = 0;
		// backtomenu->setState( 0 );
		return true;
	}
		
	return false;
}

	
void Play_desert::reloadMusic()
{
	// music->reload();
}

