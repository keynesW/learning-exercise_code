/*******************************************************************
 *
 *     File Name    :      game.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 06:11:23 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include "game.h"
#include <iostream>
#include <cstring>
int winner_flag = 0;

using namespace std;

Game *Game::pgame = new Game;
MainWindow* Game::pwindow = new MainWindow;


Game:: Game(){}
Game::~Game(){}

Game *Game:: getGame()
{
    return pgame ;
}
Game & Game::operator=(const Game & ref_g){
    *this = ref_g;
    return *this;
}

void Game::start()
{
    pwindow->init();
    pwindow->showChessBoard(); 

    do{
        while( ! pwindow->getWinner() )
        {
            pwindow->update();
            pwindow->showChessBoard(); 
        }
        pwindow->showLastResult();
        pwindow->init();
    }
    while(resume());

    end();
}

bool Game::resume()
{
    int choice = 0 ;
    pwindow->readChoice( &choice );
    return choice;
}
void Game::end()
{
    string msg("game over ~");
    pwindow->showMessageBox(msg);
    pwindow->showLastResult();

}
