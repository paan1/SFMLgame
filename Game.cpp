#include "Game.h"

//Private functions


void Game::initTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");
	//this->textures

}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/The Wanderer.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	this->pointText.setPosition(1000.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("score:");

	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(100);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//Init player GUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));



	hpbar.loadFromFile("Textures/Haert.png");
	hpbarpixel.setSize({ 50,50 });
	hpbarpixel.setPosition(0, 15);
	hpbarpixel.setTexture(&hpbar);

	scorebar.loadFromFile("Textures/scorebar.png");
	scorbarpixel.setSize({ 300,100});
	scorbarpixel.setPosition(925, 10);
	scorbarpixel.setTexture(&scorebar);



}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background3.png"))
	{
		std::cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	//this->worldBackground.setPosition(850.f, 750.f);
	this->worldBackground.setScale(3.5f, 3.5f);
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSystems()
{
	this->points = 0;
}

void Game::initPlayer()
{
	this->player = new Player();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}

void Game::initItem()
{
	this->itemTexture[0].loadFromFile("Textures/item1.png");
	this->itemTexture[1].loadFromFile("Textures/item2.png");
	this->itemTexture[2].loadFromFile("Textures/item3.png");

	//this->itemSpawnTimerMax = 1.f;
	this->setScale[0] = 1.f;
	this->setScale[1] = 1.f;
	this->setScale[2] = 1.f;


}

//Con/Des
Game::Game(RenderWindow* window,Menu* menu, ScoreList* score_list)
{	
	this->score_list = score_list;
	this->menu = menu;
	this->window = window;
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSystems();

	this->initPlayer();
	this->initEnemies();
	this->initItem();
	
}

Game::~Game()
{
	
}

//Functions
void Game::run()
{
	while (this->window->isOpen())
	{
		//deltatime = clock.restart().asSeconds();

		this->updatePollEvents();

		if (this->player->getHp() > 0)
			this->update();
		deltaTime = time.restart().asSeconds();
		itemtimer += deltaTime;
		checktimer += deltaTime;

		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		
		if (e.Event::type == sf::Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape)
			this->window->close();



		//if (this->maintime.getElapsedTime().asSeconds() >= 10)
		//{

			//for (auto* enemy : this->enemies)
			//{
			//	enemy->enemyspeed();
			//}
		//	maintime.restart();
		//}


	}
}

void Game::updateInput()
{
	//Move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"],
				this->player->getPos().x + this->player->getBounds().width / 2.f,
				this->player->getPos().y,
				0.f,
				-1.f,
				5.f
			)
		);
	}
}

void Game::updateGUI()
{
	std::stringstream ss;

	ss << "Score: " << this->points;

	this->pointText.setString(ss.str());
	this->pointText.setScale(3.f, 3.f);

	//Update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));


	//Gui
	
	
}

void Game::updateWorld()
{


}

void Game::updateCollision()
{
	//Left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//Right world collison
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//Top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//Bottom world collision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();

		//Bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			//Delete bullet
			//delete this->bullets.at(counter);
			this->bullets.erase(this->bullets.begin() + counter);
		}

		++counter;
	}
}

void Game::updateEnemies()
{
	//Spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//Update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update({ player->getPos().x + player->getBounds().width / 2 + 50, player->getPos().y + player->getBounds().height / 2 });

		//Bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{
			//Delete enemy
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		//Enemy player collision
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);
			this->enemies.erase(this->enemies.begin() + counter);
		}
		if (this->points > 100 && this->points <= 1000)
		{
			this->spawnTimerMax = 40.f;
		}
		else if (this->points > 1000 && this->points <= 1500)
		{
			this->spawnTimerMax = 35.f;
		}
		else if (this->points > 1500 && this->points <= 2000)
		{
			this->spawnTimerMax = 30.f;
		}
		else if (this->points > 2000)
		{
			this->spawnTimerMax = 20.f;
		}
		++counter;
	}
}

void Game::updateItem()
{
	this->itemSpawnTimer += this->deltaTime;
	if (itemtimer >= itemspawntime)
	{
		itemtimer = 0;
		this->randomItem = rand() % 3;
		this->items.push_back(new Item(&this->itemTexture[randomItem], rand() % this->window->getSize().x,
			(50.f), this->setScale[randomItem], this->randomItem));
	}
	if (this->timecooldownspeedmove.getElapsedTime().asSeconds() >= 2)
	{
		this->player->setmovementSpeed(2.f);
	}
	if (this->timecooldownspeedbulled.getElapsedTime().asSeconds() >= 2)
	{
		this->player->setattackCooldownMax(10.f);
	}
	for (int i = 0; i < items.size(); i++)
	{
		this->items[i]->updateItem();
		if (this->items[i]->getBounds().intersects(this->player->getBounds()))
		{

			if (this->items[i]->itemType() == 0)
			{
				this->player->setHp(100);
				delete this->items[i];
				this->items.erase(this->items.begin() + i);
			}
			else if (this->items[i]->itemType() == 1)
			{
				this->timecooldownspeedmove.restart();
				this->player->setmovementSpeed(3.f);
				delete this->items[i];
				this->items.erase(this->items.begin() + i);


			}
			else if (this->items[i]->itemType() == 2)
			{
				this->timecooldownspeedbulled.restart();
				this->player->setattackCooldownMax(4.0f);
				delete this->items[i];
				this->items.erase(this->items.begin() + i);
			}

		}
		
		/*else if (this->items[i]->deleteItem())
		{
			delete this->items[i];
			this->items.erase(this->items.begin() + i);
		}*/
		
		
		
	}
	
	if (checktimer >= 6)
	{
		checktimer = 0;
		if (itemspawntime > 5)
		{
			itemspawntime -= 1;
		}
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				//delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				//delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->updateInput();

	this->player->update();

	this->updateCollision();

	this->updateBullets();

	this->updateEnemies();

	this->updateCombat();

	this->updateGUI();

	this->updateWorld();

	this->updateItem();
}

void Game::gameReset()
{
	player->reset();
	this->points = 0;
	enemies.clear();

}

void Game::renderGUI()
{
	this->window->draw(this->scorbarpixel);
	this->window->draw(this->pointText);
	
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
	this->window->draw(this->hpbarpixel);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	this->window->clear();

	//Draw world
	this->renderWorld();

	//Draw all the stuffs
	this->player->render(*this->window);

	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}

	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	for (auto* item : this->items)
	{
		item->render(this->window);
	}


	this->renderGUI();

	//Game over screen
	if (this->player->getHp() <= 0)
	{
		this->menu->start = false;
		this->menu->states = MENU;
		this->window->draw(this->gameOverText);
		this->score_list->addEntry(this->menu->enteredName,this->points);
		overgame = true;
	}
	this->window->display();
}


