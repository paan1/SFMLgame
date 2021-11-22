#ifndef ENEMY_H
#define ENEMY_H

#include<SFML/Graphics.hpp>
#include<iostream>
using namespace sf;
using namespace std;
class Enemy
{
private:
	sf::Texture texture;
	unsigned pointCount;
	sf::RectangleShape shape;
	Vector2f  direction;
	Vector2f  directionNorm;
	int random;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;
	void initVariables();
	void initShape();
	void initTexture();
	void initSprite();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	//Accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//Functions
	void enemyspeed();
	void update(Vector2f pos);
	void render(sf::RenderTarget* target);
};

#endif //!ENEMY_H