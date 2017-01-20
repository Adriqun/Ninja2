#pragma once

#include "drawable/sprite.h"
#include "block.h"
#include <vector>

class Plant
{
	vector <sf::Uint8> blocks;
public:

	sf::Uint8 nr;
	int startX, endX;
	int startY, endY;

	Plant();
	~Plant();
	
	void clear();
	void add( sf::Uint8 block );
	bool available( sf::Uint8 block );
	unsigned getSize();
	sf::Uint8 getBlocksNr( sf::Uint8 n );
};

class Vegetation
{
	sf::Uint8 min;
	vector <Plant*> plants;
	vector <Block*> blocks;
	vector <MySprite*> sprites;
	
public:

	Vegetation();
	~Vegetation();
	void free();
	
	void load( int type, vector < Block* > b );
	void draw( sf::RenderWindow* &window );
	
	void fadein( int v = 1, int max = 0xFF );
	void fadeout( int v = 1, int min = 0 );
	
	int strToInt( string s );
	int getSpecialNr( string line, int nr, char c );
};