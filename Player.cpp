#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 2.0f;

	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//Load a texture from file
	if (!this->texture.loadFromFile("Textures/player.png"))
	{
		std::cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}
}

void Player::initSprite()
{
	//Set the texture to the sprite
	this->sprite.setTexture(this->texture);

	//Resize the sprite
	this->sprite.scale(0.9f, 0.9f);
	this->sprite.setPosition(850.f, 750.f);
}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Player::~Player()
{

}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}

void Player::setPosition(const sf::Vector2f pos, Vector2f mouse_position)
{
	this->sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::setHp(const int hp)
{
	this->hp = hp;
}

void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.2f;
}

//Functions
void Player::update()
{
	this->updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}