#pragma once
#include "text.h"
#include "sound.h"
#include "sprite.h"
#include "thread.h"
#include "request.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Settings
{
	float screen_w;
	float screen_h;

	enum Activities
	{
		MOVE_LEFT = 0,
		MOVE_RIGHT,
		JUMP,
		ATTACK,
		SHIELD,
		JUMP_ATTACK,
		JUMP_SHIELD,
		PAUSE,
		CHAT,
		AMOUNT
	};
	std::vector<int> keys;

	enum GEAR_POS
	{
		TOP = 0,
		BOT,
		LEFT,
		RIGHT
	};
	std::vector<cmm::Sprite*> gears;

	// Table.
	std::vector<sf::Rect<float>> text_collisions;
	std::vector<cmm::Text*> state_texts;
	std::vector<cmm::Text*> active_texts;
	cmm::Text contactme;
	cmm::Sprite table;
	float tableMoves;
	float x1, x2;

	// Chart.
	cmm::Text info;
	cmm::Sprite chart;
	cmm::Sprite resetbutton;
	float chartMoves;
	float y1, y2;

	int target;

	// Sound.
	cmm::Sound click;
	cmm::Thread thread;

public:
	Settings();
	~Settings();
	void free();

	void load(const float &screen_w, const float &screen_h);
	bool handle(const sf::Event &event);
	void draw(sf::RenderWindow* &window);
	void mechanics(const double &elapsedTime);
	void fadein(const float &v, const int &max);
	void fadeout(const float &v, const int &min);

	// Support.
	void exsertTable(const double &elapsedTime);
	void shovelTable(const double &elapsedTime);
private:
	void resetKeys();
	void setKeys();
	void sendKeysThread();
	void sendKeys();
	void positionTable();
	void positionChart();
	bool isPossibleKey(const int &n);
	const std::string getName(const int &n);
public:
	void reset();

	void setThread();
	void reloadThread();
	const bool& isReady() const;	// values are loaded correctly from database
	void setVolume(const float &volume);
};

/*
enum  	Key {
Unknown = -1,
A = 0,
B,
C,
D, // 3
E,
F,
G,
H,
I,
J,
K, // 10
L,
M,
N,
O,
P, // 15
Q,
R,
S,
T,
U, // 20
V,
W,
X,
Y,
Z, // 25
Num0,
Num1,
Num2,
Num3,
Num4, // 30
Num5,
Num6,
Num7,
Num8,
Num9, // 35
Escape,
LControl,
LShift,
LAlt,
LSystem, // 40
RControl,
RShift,
RAlt,
RSystem,
Menu, // 45
LBracket,
RBracket,
SemiColon,
Comma,
Period,  // 50
Quote,
Slash,
BackSlash,
Tilde,
Equal, // 55
Dash,
Space, // 57
Return,
BackSpace,
Tab, // 60
PageUp,
PageDown,
End,
Home,
Insert, // 65
Delete,
Add,
Subtract,
Multiply,
Divide, // 70
Left, // 71
Right, // 72
Up, // 73
Down, // 74
Numpad0, // 75
Numpad1,
Numpad2,
Numpad3,
Numpad4,
Numpad5,
Numpad6,
Numpad7,
Numpad8,
Numpad9, // 84
F1,
F2,
F3,
F4,
F5,
F6,
F7,
F8,
F9,
F10,
F11,
F12,
F13,
F14,
F15,
Pause,
KeyCount
}
*/