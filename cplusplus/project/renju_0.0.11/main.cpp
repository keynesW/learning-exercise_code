using namespace std;
#include <iostream>
#include <cstdio>
#include "game.h"

int main(){
	Game* game = Game::getGame();
    cout << "game starting ..." << endl;
 	game->start();
    
    return 0;
}
