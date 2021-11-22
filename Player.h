#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<iostream>
using namespace sf;
using namespace std;
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float movementSpeed;

	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();

	bool checkgameover = false;

public:
	Player();
	virtual ~Player();



	inline const bool isOver() { return checkgameover; }
	//Accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const sf::Vector2f pos, Vector2f mouse_position);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);
	void setmovementSpeed(float movementSpeed);
	void setattackCooldownMax(float attackCooldownMax);
	//Functions
	void move(const float dirX, const float dirY);
	const bool canAttack();
	void reset();
	
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};