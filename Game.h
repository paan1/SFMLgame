#pragma once
//#define _CRT_SECURE_NO_WARNINGS

#include<map>
#include<string>
#include<sstream>
#include<cstdlib>
#include<iostream>
#include<vector>
#include <math.h>

#include "ScoreList.h"
#include "Menu.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"

using namespace sf;
using namespace std;
class Game
{
private:

	ScoreList* score_list;
	Menu* menu;
	float itemspawntime = 20;
	float itemtimer;
	float	checktimer;
	float deltaTime;
	Clock clock;
	Clock time;
	Clock timecooldownspeedmove;
	Clock timecooldownspeedbulled;
	Clock maintime;

	//Window
	sf::RenderWindow* window;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;
	Texture hpbartex;

	RectangleShape hpbarpixel;
	Texture hpbar;

	RectangleShape scorbarpixel;
	Texture scorebar;


	sf::Text gameOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	unsigned points;

	//Player
	Player* player;
	bool overgame = false;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	//Enemies
	float spawnTimer;
	float spawnTimerMax;
	std::vector<Enemy*> enemies;
	
	//Score
	

	//item
	std::vector<Item*> items;
	float itemSpawnTimer;
	float itemSpawnTimerMax;
	float setScale[3];
	int randomItem;
	sf::Texture itemTexture[3];
	sf::Sprite itemSprite;

	//Private functions
	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initItem();

public:
	Game(RenderWindow* window,Menu* menu,ScoreList* score_list);
	virtual ~Game();

	//Functions
	void run();
	inline const bool gameOverCheck() { return overgame; }

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateItem();
	void updateCombat();
	void update();
	void gameReset();
	void renderGUI();
	void renderWorld();
	void render();
	
};