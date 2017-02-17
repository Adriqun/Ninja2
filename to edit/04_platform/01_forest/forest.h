#pragma once

// Sound
#include "sound/sound.h"

// Hero stuff
#include "04_platform/hero/hero.h"
#include "04_platform/hero/kunai.h"
#include "04_platform/hero/heart.h"
#include "04_platform/hero/scope.h"

// World stuff
#include "04_platform/world/brick/brick.h"
#include "04_platform/world/background/effect.h"
#include "04_platform/world/background/background.h"
#include "04_platform/world/islands/islands.h"
#include "04_platform/world/water/water.h"
#include "04_platform/world/wall/wall.h"
#include "04_platform/world/ladder/ladder.h"
#include "04_platform/world/greenery/greenery.h"
#include "04_platform/world/background/day.h"

// Enemy
#include "04_platform/enemy/mine/mine_factory.h"
#include "04_platform/enemy/skeleton/skeleton_factory.h"

class Forest
{
	int state;
	string info;
	
	int screen_w;
	int screen_h;
	
	// sound
	Sound sound;
	
	// hero
	Hero* hero;
	Kunai* kunai;
	Heart* heart;
	Scope* scope;
	
	// world
	Brick* brick;
	Effect* effect;
	Background* background;
	Islands* islands;
	Water* water;
	Wall* wall;
	Ladder* ladder;
	Greenery* greenery;
	Day* day;
	
	// enemy
	Mine_factory* mine_factory;
	Skeleton_factory* skeleton_factory;
	
public:

	Forest();
    ~Forest();
    void free();
	void reset();
	
    void load( int screen_w, int screen_h, unsigned FPS );
    void handle( sf::Event &event );
    void draw( sf::RenderWindow* &window );
	
	bool positioning( int type, int size, int flatness, int difficuly );
	string getInfo();
	
	bool nextState();
	bool backToLevel();
	void mechanics();
};