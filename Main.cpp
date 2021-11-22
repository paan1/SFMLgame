#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <SFML/Network.hpp>

#include "ScoreList.h"
#include "Game.h"
#include <time.h>


int main()
{
	ScoreList score_list("highscore.txt");
	score_list.loadFile();

    //RenderWindow window(VideoMode(1500, 900), "My Game", Style::Titlebar | Style::Close | Style::Fullscreen);

	RenderWindow window(sf::VideoMode(1500, 900), "human survive simulator", sf::Style::Close | sf::Style::Titlebar |Style::Fullscreen);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(false);
   // RenderWindow window(VideoMode(1366, 768), "Game", Style::Titlebar | Style::Close | Style::Fullscreen);
    srand(static_cast<unsigned>(time(NULL)));
    //srand(time(static_cast<unsigned>(0)));
	sf::Event event;

	
	Menu menu(&window, &score_list);
	Game game(&window,&menu,&score_list);
	
	
	
	bool onScreen = true;
	while (window.isOpen())
	{
		int state = menu.getStates();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::GainedFocus:
				onScreen = true;
				break;

			case sf::Event::LostFocus:
				onScreen = false;
				break;
			}
		}

		if (onScreen)
		{
			if (state == MENU)
			{
				game.gameReset();
				menu.mainMenuUpdate();
				menu.mainMenuRender();
			}
			if (state == NAME)
			{
				menu.nameUpdate(event);
				menu.mainMenuRenderComponent();
				menu.nameRender();
				if (menu.startCheck())
				{
					menu.started();
					
				}
			}
			if (state == PLAY)
			{
				if (!game.gameOverCheck())
				{
					game.run();
					menu.pauseCheck();
					
				}
				else
				{
					menu.gameOver();
				}
			}
			if (state == PAUSE)
			{
				menu.pauseMenuUpdate();
				menu.pauseMenuRender();
			}

			if (state == LEADERBOARD)
			{


				menu.leaderBoardMenuUpdate();
				menu.leaderBoardMenuRender();

			}
			if (state == GAMEOVER)
			{
				menu.gameOverMenuUpdate();
				menu.gameOverMenuRender();
				if (menu.tryAgainCheck())
				{
					game.gameReset();
					menu.tryAgainClickSetToFalse();
					menu.tryAgain();
				}
			}
		}
	}
		//window.clear();
		//window.draw(shape);
		//menu.render(window);
		//window.display();
	score_list.saveFile();

	
    return 0;
}