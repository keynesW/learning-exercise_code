#ifndef _GAME_H_
#define _GAME_H_
#include "iGame.h"
#include "MainWindow.h"

extern int  winner_flag;
using namespace std;

class Game:public IGame{

    static Game *pgame;
    static MainWindow * pwindow;

    private:
        Game();
        Game(const Game & ref_g);
        Game & operator=(const Game & ref_g);
    public:
        ~Game();
        static Game * getGame();

		void start();
		bool resume();
		void end();
};
#endif


