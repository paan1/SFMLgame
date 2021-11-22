#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3; //min = 3 max = 10
	this->type = 0;
	this->speed = static_cast<float>(this->pointCount / 3);
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
}

void Enemy::initShape()
{
	random = rand() % 3;
	if (random == 0)
	{
		
		texture.loadFromFile("Textures/enyme1.png");
	}
	else if (random  == 1)
	{
		texture.loadFromFile("Textures/enyme2.png");
	}
	else if (random == 2)
	{
		texture.loadFromFile("Textures/enyme3.png");
	}
	this->shape.setRotation(180);
	this->shape.setTexture(&texture);
	this->shape.setSize({ 100,100 });
	//this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();

	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

//Accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::enemyspeed()
{
	speed += 1;
}

//Functions
void Enemy::update(Vector2f pos)
{
	direction = pos - shape.getPosition();
	directionNorm = direction / sqrt((direction.x * direction.x + direction.y * direction.y));
	this->shape.move(directionNorm.x * speed, directionNorm.y * speed);
	this->shape.setRotation(atan2(this->directionNorm.y, this->directionNorm.x) * 180 / 3.14159265359 + 90);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}