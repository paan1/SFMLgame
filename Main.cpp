#include <iostream>
#include "Game.h"
#include <time.h>

using namespace sf;
int main()
{
   // RenderWindow window(VideoMode(1366, 768), "Game", Style::Titlebar | Style::Close | Style::Fullscreen);
    
    srand(static_cast<unsigned>(time(NULL)));

    //srand(time(static_cast<unsigned>(0)));
    Game game;

    game.run();

    
    return 0;
}