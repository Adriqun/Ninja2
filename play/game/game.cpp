#include "Game.h"
#include "own/file.h"

Game::Game()
{
	free();
}

Game::~Game()
{
	free();
}

void Game::free()
{
	table = false;
	loaded = false;
	
	background.free();
	knight.free();
	eye.free();
	tiles.free();
	objects.free();
	coins.free();
	skeletons.free();
}

void Game::reset()
{
	table = false;
	loaded = false;
	
	knight.reset();
	eye.reset();
	tiles.reset();
	objects.reset();
	coins.reset();
	skeletons.reset();
}



void Game::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Load background.
	background.setIdentity( "game-background" );
	background.load( "images/play/background.png" );
	background.setScale( scale_x, scale_y );
	
	knight.load( screen_w, screen_h );
	eye.load( screen_w, screen_h );
	tiles.load( screen_w, screen_h );
	objects.load( screen_w, screen_h );
	coins.load( screen_w, screen_h );
	skeletons.load( screen_w, screen_h, 0, "skeleton" );
}

void Game::handle( sf::Event& event )
{
	if( !knight.isDeath() )
	{
		knight.handle( event );
	}
}

void Game::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	window->setView( knight.getView() );
	coins.draw( window );
	knight.draw( window );
	tiles.draw( window );
	skeletons.draw( window );
	objects.draw( window );
	eye.draw( window );
	window->setView( window->getDefaultView() );
	// eye.drawShader( window );
	objects.drawFPS( window );
}

void Game::mechanics( double elapsedTime )
{
	if( !knight.isDeath() )
	{
		knight.jumping( elapsedTime );
		if( tiles.checkCollisionRect( knight.getRect() ) )
		{
			knight.backjumping( elapsedTime );
		}
		
		knight.gravity( elapsedTime );
		tiles.tickGravity( knight.getRect(), elapsedTime );
		if( tiles.checkCollisionRect( knight.getRect() ) )
		{
			knight.weightlessness( elapsedTime );
		}
		
		if( knight.jump() )
		{
			
		}
		
		if( knight.attack() )
		{
			
		}
		
		if( knight.moveLeft( elapsedTime ) )
		{
			if( tiles.checkCollisionRect( knight.getRect() ) || knight.getLeft() < tiles.getBorderX() )
			{
				knight.back( elapsedTime );
			}
		}
		else if( knight.moveRight( elapsedTime ) )
		{
			if( tiles.checkCollisionRect( knight.getRect() ) || knight.getRight() > tiles.getBorderX() +tiles.getScreenWidth() )
			{
				knight.back( elapsedTime );
			}
		}
		else
		{
			knight.idle( elapsedTime );
		}
	}
	else if( knight.isRemains() )
	{
		table = true;
	}
	
	// Knight the rest.
	if( knight.isAttacking() )
	{
		skeletons.harm( knight.getAttackRect(), knight.getDamage() );
	}
	knight.animation( elapsedTime );
	
	// Coins
	coins.mechanics( elapsedTime );
	
	// Skeletons
	skeletons.walk( knight.getRect(), elapsedTime );
	if( skeletons.isHarmed( knight.getRect() ) )
	{
		knight.harm( skeletons.getDamage() );
	}
	skeletons.mechanics( elapsedTime );
	
	// Set borders.
	tiles.setBorderX( knight.getViewX() );
	tiles.setBorderY( knight.getViewY() );
	objects.setBorderX( knight.getViewX() );
	objects.setBorderY( knight.getViewY() );
	coins.setBorderX( knight.getViewX() );
	coins.setBorderY( knight.getViewY() );
	skeletons.setBorderX( knight.getViewX() );
	skeletons.setBorderY( knight.getViewY() );
	
	eye.setPosition( knight.getRect().left +knight.getRect().width/2, knight.getRect().top -knight.getRect().height );
	eye.mechanics( elapsedTime, knight.getViewX(), knight.getViewY() );
	objects.mechanics( elapsedTime );
}



void Game::fadein( float v, int max )
{
	background.fadein( v, max );
	knight.fadein( v, max );
	eye.fadein( v, max );
	tiles.fadein( v, max );
	objects.fadein( v, max );
	coins.fadein( v, max );
	skeletons.fadein( v, max );
}

void Game::fadeout( float v, int min )
{
	background.fadeout( v, min );
	knight.fadeout( v, min );
	eye.fadeout( v, min );
	tiles.fadeout( v, min );
	objects.fadeout( v, min );
	coins.fadeout( v, min );
	skeletons.fadeout( v, min );
}



void Game::setUsername( string line )
{
	knight.setUsername( line );
}

void Game::setPlayable( bool playable )
{
	
}

void Game::setVolume( float volume )
{
	
}



bool Game::isTable()
{
	return table;
}

float Game::getAlpha()
{
	return background.getAlpha();
}



void Game::loading( int which )
{
	switch( which )
	{
		case 1:
		knight.setThread();
		break;
		
		case 2:
		tiles.setThread();
		break;
		
		case 3:
		objects.setThread();
		break;
		
		case 4:
		coins.setThread();
		break;
		
		case 5:
		skeletons.setThread();
		break;
		
		default:
		if( knight.isNull() && tiles.isNull() &&
			objects.isNull() && coins.isNull() &&
			skeletons.isNull() )
		{
			loaded = true;
		}
		break;
	}
}

int Game::getStatus()
{
	if( loaded )
	{
		if( knight.isReady() && tiles.isReady() &&
			objects.isReady() && coins.isReady() &&
			skeletons.isReady() )
		{
			return 2;
		}
		
		return 1;
	}
	
	return 0;
}

void Game::resetStatus()
{
	loaded = false;
}



void Game::turnCollision( bool collision )
{
	knight.turnCollision( collision );
	tiles.turnCollision( collision );
	skeletons.turnCollision( collision );
}

bool Game::getCollision()
{
	return skeletons.getCollision();
}

void Game::turnFPS( bool fps )
{
	objects.setFPS( fps );
}

bool Game::getFPS()
{
	return objects.getFPS();
}

void Game::commitSuicide()
{
	knight.commitSuicide();
}