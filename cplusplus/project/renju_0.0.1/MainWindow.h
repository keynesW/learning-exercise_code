#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "iMainWindow.h"
#include "ChessBoard.h"
using namespace std;

class MainWindow : public IMainWindow{
    private:    
        ChessBoard chessboard;  
        Chess chess_record;
    public:
        MainWindow();
        ~MainWindow();
        //static MainWindow* getWindow(); 
        // static bool getWinner(); 

		void init() ;

		void update() ;
        bool getWinner();

		void showChessBoard() ;
        ChessColor getChessColor();

		void showMessageBox(string message) ;
		void showLastResult() ;

		void readChoice(int* choice) ;
		void readChessPos(ChessColor chessColor, int* row, int* column) ;
		void readChessBoardSize(int* rows, int* columns) ;
};
#endif
