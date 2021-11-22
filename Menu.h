#pragma once
#include <SFML/Graphics.hpp>
#include "ScoreList.h"

using namespace sf;
enum STATE { MENU, PLAY, PAUSE, LEADERBOARD, GAMEOVER, NAME };

class Menu
{
private:

	ScoreList* score_list;
	sf::Event event;
	//sf::View view;
	sf::Font font;
	sf::Vector2f buttonSize = { 350.f, 80.f };
	sf::Clock debounce;
	sf::Clock KeyClock;

	sf::RectangleShape greyScreen;

	//MAIN_MENU
	sf::Text title;
	sf::Text myname;
	sf::Texture textture1;
	sf::Texture textture2;
	sf::Texture textture3;
	sf::Text playButtonText;
	sf::Text leaderBoardButtonText;
	sf::Text exitButtonText;
	sf::RenderWindow* window;
	sf::RectangleShape playButton;
	sf::RectangleShape leaderBoardButton;
	sf::RectangleShape exitButton;
	sf::RectangleShape mainBackground;
	

	//PAUSE_MENU
	
	sf::Text resumeButtonText;
	sf::Text mainMenuButtonText;
	sf::RectangleShape resumeButton;
	sf::RectangleShape mainMenuButton;

	//LEADERBOARD_MENU
	
	sf::Text leaderBoardTitle;
	sf::Text backButtonText;
	sf::RectangleShape frame;
	sf::RectangleShape backButton;

	//GAMEOVER_MENU
	sf::Text gameOverTitle;
	sf::Text tryAgainButtonText;
	sf::RectangleShape tryAgainButton;

	//NAME_MENU
	sf::RectangleShape nameFrame;
	sf::RectangleShape nameFill;
	sf::RectangleShape confirmButton;
	sf::Text confirmButtonText;
	sf::Text name;


	//backgronp
	RectangleShape backgroun;
	Texture texturemenu;
	int buttonTextSize;

	RectangleShape backgrounleaderBoard;
	Texture texturemenuleader;

	RectangleShape backgrounnameBoard;
	Texture texturename;

	bool tryAgainClick = false;
	bool enableToType = true;
	float transitionDebounce;
	int playerScore;
public:
	Menu(sf::RenderWindow* window, ScoreList* score_list);
	inline int getStates() { return states; }
	inline bool tryAgainCheck() { return tryAgainClick; }
	inline bool startCheck() { return start; }
	inline void tryAgainClickSetToFalse() { tryAgainClick = false; }
	inline void gameOver() { states = GAMEOVER; }
	inline void tryAgain() { states = PLAY; }
	inline void setScore(int score) { playerScore = score; }
	inline void started() { start = false; }
	std::string enteredName;
	int states;
	bool start = false;

	void nameReset();
	void pauseCheck();
	void mainMenuUpdate();
	void mainMenuRender();
	void leaderBoardMenuUpdate();
	void leaderBoardMenuRender();
	void pauseMenuUpdate();
	void pauseMenuRender();
	void gameOverMenuUpdate();
	void gameOverMenuRender();
	void nameUpdate(sf::Event& event);
	void nameRender();
	void mainMenuRenderComponent();
};
