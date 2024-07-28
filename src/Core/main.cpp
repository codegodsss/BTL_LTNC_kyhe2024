#include "Game.hpp"



int main(int /*argc*/, char* argv[])
{
    Game& game = Game::getInstance();
    game.init(argv[0]);
    
    game.run();
    return 0;


    
}
