#include "engine.h"
#include <stdio.h>
#include <cstdlib>

Engine::Engine()
{
	// Set seed.
	srand(static_cast<int>(time(NULL)));

	// Set core.
	core = std::make_unique<Core>(STATES::LOADING, 21, 21, 29, 0xFF);
	core->create("Combat Halloween");
	core->setIcon("images/other/icon.png");

	// Set loading.
	loading = new Loading;
	loading->load(core->getWidth(), core->getHeight());
}

void Engine::loop()
{
	while (core->open)
	{
		core->clear();
		events();
		states();
		core->display();
	}
}

void Engine::load()
{
	loading->mechanics(core->getElapsedTime());
	loading->draw(core->getWindow());

	switch (loading->getState())
	{
	case 1:
		initialization = new Initialization;
		initialization->load(core->getWidth(), core->getHeight());
		break;

	case 20:
		login = new Login;
		login->load(core->getWidth(), core->getHeight());
		break;

	case 25:
	menu = new Menu;
	menu->load( core->getWidth(), core->getHeight() );
	break;
	
		//	case 70:
		//	level = new Level;
		//	level->load( core->getWidth(), core->getHeight() );
		//	break;
	
		//	case 71:
		//	play = new Play;
		//	play->load( core->getWidth(), core->getHeight() );
		//	break;

		//	case 95:
		//	table = new Table;
		//	table->load( core->getWidth(), core->getHeight() );
		//	break;

		//	case 96:
		//	editor = new Editor;
		//	editor->load( core->getWidth(), core->getHeight() );
		//	break;

	case 101:
		loading->beReady();
		break;
	}

	if (loading->isReady())
	{
		delete loading;
		loading = NULL;
		core->state = INIT;	// SET FIRST STATE.
	}
}

void Engine::events()
{
	while (core->isEvent())
	{
		if (core->getEvent().type == sf::Event::Closed)
		{
			core->open = false;
		}

		switch (core->state)
		{
		case LOGIN: 	login->handle(core->getEvent()); 	break;
		case MENU: 		menu->handle( core->getEvent() ); 	break;
				/*case LEVEL: 	level->handle( core->getEvent() );	break;
			case PLAY: 		play->handle( core->getEvent() ); 	break;
			case TABLE: 	table->handle( core->getEvent() ); 	break;*/
		}
	}
}

void Engine::states()
{
	if (core->state == LOADING)
	{
		load();
	}

	if (core->state == INIT)
	{
		initialization->mechanics(core->getElapsedTime());
		initialization->draw(core->getWindow());

		if (initialization->isNext())
		{
			core->state = LOGIN;
			delete initialization;
			initialization = NULL;
		}
	}

	if (core->state == LOGIN)
	{
		login->mechanics(core->getElapsedTime());
		login->draw(core->getWindow());
		if (login->isNext())	core->state = MENU;
	}

	if (core->state == MENU)
	{
		menu->head(core->getWindow(), core->getElapsedTime());
		/*if (menu->isPrev()) // add editor exe
		else */if (menu->isNext())	core->state = LEVEL;
		else if (menu->isExit())	core->open = false;
	}

	/*if( core->getState() == LEVEL )
	{
	level->loadSound();
	level->head( core->getWindow(), core->getElapsedTime() );

	if( level->isNext() )
	{
	level->saveSound();
	core->getState() = PLAY;
	}
	else if( level->isBack() )
	{
	level->saveSound();
	core->getState() = MENU;
	}
	}

	if( core->getState() == PLAY )
	{
	play->loadSound();
	play->head( core->getWindow(), core->getElapsedTime() );

	if( play->isMenu() )
	{
	play->saveSound();
	core->getState() = MENU;
	}
	else if( play->isLevel() )
	{
	play->saveSound();
	core->getState() = LEVEL;
	}
	else if( play->isTable() )
	{
	play->saveSound();
	core->getState() = TABLE;
	}
	else if( play->isEditor() )
	{
	play->saveSound();
	core->getState() = EDITOR;
	}
	}

	if( core->getState() == TABLE )
	{
	table->loadSound();
	table->head( core->getWindow(), core->getElapsedTime() );

	if( table->isMenu() )
	{
	table->saveSound();
	core->getState() = MENU;
	}
	else if( table->isLevel() )
	{
	table->saveSound();
	core->getState() = LEVEL;
	}
	}

	if( core->getState() == EDITOR )
	{
	editor->head( core->getWindow(), core->getElapsedTime() );

	if( editor->isBack() )
	{
	core->getState() = MENU;
	}
	else if( editor->isPlay() )
	{
	core->getState() = PLAY;
	play->setMessage( editor->getMessage() );
	}
	}*/
}