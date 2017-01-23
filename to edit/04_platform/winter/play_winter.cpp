#include "play_winter.h"

Play_winter::Play_winter()
{
	state = 0;
	
	// Create play_winter objects.
	sound = new Sound;
	hero = new Hero;
	bg = new Moving_bg;
	brick = new Brick;
	kunai = new Kunai;
	heart = new Heart;
	scope = new Scope;
	greenery = new Greenery;
	ladder = new Ladder;
}

Play_winter::~Play_winter()
{
	free();
}

void Play_winter::free()
{
	delete sound;
	delete hero;
	delete bg;
	delete brick;
	delete kunai;
	delete heart;
	delete scope;
	delete greenery;
	delete ladder;
}

	
void Play_winter::load( int screen_w, int screen_h )
{
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	bg->load( "data/sprites/play/2.png", screen_w, screen_h );
	brick->load( screen_w, screen_h, 18, 2 );
	kunai->load();
	heart->load();
	greenery->load( 2 );
	ladder->load( 2 );
}

void Play_winter::setHero( int screen_w, int screen_h, int type )
{
	hero->load( screen_w, screen_h, "data/sprites/hero/" + to_string( type ) + "/" );
	bg->setXY( hero->getX(), hero->getY() );
}

void Play_winter::setWorldsize( int size )
{
	ladder->positioning( brick->positioning( size, ladder->getW( 0 ), ladder->getH( 0 ),
	ladder->getW( 1 ), ladder->getH( 1 ) ) );
	
	greenery->positioning( brick->getBlocks() );
}


void Play_winter::handle( sf::Event &event )
{
	// hero->handle( event );
}

void Play_winter::draw( sf::RenderWindow* &window )
{
	mechanics();
	
	bg->fadein( 2 );
	brick->fadein( 2 );
	hero->fadein( 2 );
	kunai->fadein( 2 );
	heart->fadein( 2 );
	greenery->fadein( 2 );
	ladder->fadein( 2 );

	
	bg->draw( window );
	greenery->drawBG( window, screen_w );
	ladder->draw( window, screen_w );
	hero->draw( window );
	kunai->draw( window );
	brick->draw( window );
	greenery->draw( window, screen_w );
	heart->draw( window );
}

	
int Play_winter::getState()
{
	return state;
}

void Play_winter::set( int state, Sound* sound )
{
	state = 0;
	
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

	
bool Play_winter::isQuit()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::nextState()
{
	if( state == 1 )
	{
		return true;
	}
	
	return false;
}

bool Play_winter::backToLevel()
{
	if( state == 2 )
	{
		state = 0;
		return true;
	}
		
	return false;
}

	
void Play_winter::reloadMusic()
{
	// music->reload();
}

