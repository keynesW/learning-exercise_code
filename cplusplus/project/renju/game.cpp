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
//MainWindow* Game::pwindow = MainWindow::getWindow();

/*
*/

Game:: Game(){}
Game::~Game(){}

Game *Game:: getGame()
{
    return pgame ;
}
void Game::start()
{
    int choice = 1 ;
    static ChessColor color = COLOR_WHITE;
    int row,column;

    do{
        cout << "in start() ..." << endl;
        pwindow->showMessageBox("please input the boardsize,eg : 10 * 10");
        cin >> row;
        cin >> column;
        cout << row << "  " << column << endl;
        pwindow->readChessBoardSize(&row,&column);
        pwindow->init();
        pwindow->showChessBoard();

        //while( ! MainWindow::getWinner() )
        while( ! winner_flag )
        {
            cin >> row;
            cin >> column;
            system("clear");
            //strcpy( color, (strcmp( color, "aa" ) ? "aa":"bb") );
            color = (( color == COLOR_BLACK ) ? COLOR_WHITE:COLOR_BLACK);
            cout << color << endl;
            try{
                pwindow->readChessPos( color,&row,&column );
            }
            catch(out_of_range e)
            {
                color = (( color == COLOR_BLACK ) ? COLOR_WHITE:COLOR_BLACK);
                //cout << e.what() << endl; 
                string msg("out_of_range please reinput");
                pwindow->showMessageBox(msg);
                //continue;
            }
            catch(string msg)
            {
                color = (( color == COLOR_BLACK ) ? COLOR_WHITE:COLOR_BLACK);
                //cout << msg << endl;
                pwindow->showMessageBox(msg);
                //continue;
            }
            pwindow->update();
        }
        pwindow->showLastResult();
        cin >> choice;
        pwindow->readChoice( &choice );
        winner_flag = 0 ;
    }
    while(choice == 1);
    end();
}

bool Game::resume()
{
    return 0;
}
void Game::end()
{
}
