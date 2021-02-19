#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "iMainWindow.h"
#include "ChessBoard.h"
using namespace std;

class MainWindow : public IMainWindow{
    private:    
//        int choice;
//        static MainWindow * pwd;
//        MainWindow(const MainWindow & ref_mw);
/////////////////////////////////////////////////////////
        //int row,column;
        //static ChessColor color;
        ChessBoard chessboard;  
/////////////////////////////////////////////////////////
    public:
        MainWindow();
        ~MainWindow();
        //static MainWindow* getWindow(); 
        // static bool getWinner(); 

		void init() ;

		void update() ;
		void showChessBoard() ;

		void showMessageBox(string message) ;
		void showLastResult() ;

		void readChoice(int* choice) ;
		void readChessPos(ChessColor chessColor, int* row, int* column) ;
		void readChessBoardSize(int* rows, int* columns) ;
};
#endif
