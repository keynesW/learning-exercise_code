/*******************************************************************
 *
 *     File Name    :      MainWindow.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog£º :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 06:12:48 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/

#include "MainWindow.h"
#include <iostream>
extern int winner_flag;
using namespace std;

MainWindow::MainWindow(){}
MainWindow::~MainWindow(){}

/*
MainWindow * MainWindow:: pwd = new MainWindow;
MainWindow* MainWindow::getWindow()
{
    return pwd;
}

bool MainWindow:: getWinner()
{
    return chessboard.isWinner(record_chess);
    //return false;
}
*/
void MainWindow::init()
{
//    int row ,column;
//    char del;
    cout << "in MainWindow init() ..." << endl;
    //readChessBoardSize();
///////////////////////////////////
//////////////////////////////////
}

void MainWindow::update()
{
    showChessBoard(); 
}

void MainWindow::showChessBoard()
{
    cout << "show chessboard ..." << endl;
    char str[20] = {'\0'};
    const char * ptr_arr[] = {"||","AA","BB",nullptr};

    const char *ptr = ptr_arr[0];
    //for( int j = 1 ; j <= column ; j ++)
    for( int j = 1 ; j <= chessboard.getWidth() ; j ++)
    {
        sprintf(str,"%5d",j);
        cout << str;
    }
    cout << endl;

    for( int i = 1 ; i <= chessboard.getHeight(); i ++)
    //for( int i = 1 ; i <= row; i ++)
    {
        sprintf(str,"%3d",i);
        cout << str;
        for(int j = 1; j <= chessboard.getWidth() ; j++ )
        //for(int j = 1; j <= column ; j++ )
        {
            ChessColor color = chessboard.chessColor(i-1,j-1);
            if (color == COLOR_BLACK)  
                ptr = ptr_arr[1];
            else
            if(color == COLOR_WHITE)
                ptr =  ptr_arr[2];
            else
                ptr = ptr_arr[0];
            
            sprintf(str,"%s---",ptr);
            cout << str;
        }
        cout << endl;

        sprintf(str,"%3c",' ');
        cout << str;
        for(int j = 1; j <= chessboard.getWidth() ; j++ )
        //for(int j = 1; j <= column ; j++ )
        {
        //    sprintf(str,"||--");
            sprintf(str,"||   ");
            cout << str;
        }
        cout << endl;
    }

    sprintf(str,"%3c",' ');
    cout << str;
    for(int j = 1; j <= chessboard.getWidth() ; j++ )
    //for(int j = 1; j <= column ; j++ )
    {
        sprintf(str,"||---");
        cout << str;
    }
    cout << endl;

}
void MainWindow::showMessageBox(string message)
{
    //cout << "in MainWindow init() ..." << endl;
    cout << "-------------------------------------------------" << endl;
    cout <<  "     " << message <<  endl;//"|    " <<"    |" << endl;
    cout << "-------------------------------------------------" << endl;

}
void MainWindow::showLastResult()
{
    char str[60] = {'\0'};
    sprintf(str,"white %d : %d  black ",chessboard.getWhiteScore(),chessboard.getBlackScore());
    string msg(str);
    showMessageBox(msg);
    sprintf(str,"enter 1 for another round, 0 to quit");
    showMessageBox(str);
}
void MainWindow::readChoice(int* choice)
{
    
}
void MainWindow::readChessPos(ChessColor chessColor, int* row, int* column)
{
    if(chessboard.isRepeat(*row-1,*column -1))
    {
        //cout << "position repeat please reinput" << endl;
        string message("posRepeat please reinput");
        throw message;
    }
    ChessPos chesspos(*row-1,*column-1);
    //ChessPos chesspos(*row,*column);
    Chess chess(chesspos,chessColor);
    cout << "chess to define winner" << endl;
    cout << chess.first.first << endl;
    cout << chess.first.second << endl;
    chessboard.addChess(chess);

    if(!chessboard.isWinner(chess))
    {
        winner_flag = 0;
    }
    else
        winner_flag = 1;
}
void MainWindow::readChessBoardSize(int* rows, int* columns)
{
    //row = *rows;
    //column = *columns;
    //chessboard.resize(row,column);
    chessboard.resize(*columns,*rows); 
    chessboard.init();
    cout <<  *rows << "   " << *columns << endl;
    //cout <<  chessboard.width << "   " << chessboard.height << endl;
} 
