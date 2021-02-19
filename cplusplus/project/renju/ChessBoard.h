#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_

#include "iChessBoard.h"

class ChessBoard:public IChessBoard{
    private:
        ChessBoardMap chessboard;
        int whitescore;
        int blackscore;
        int width;
        int height;
	public:
        ChessBoard();
        ChessBoard(int _width, int _height);
        ~ChessBoard();
		void resize(int _width, int _height);
		void init();
		void addChess(Chess chess); 
		int getWhiteScore();
		int getBlackScore();
		int getWidth();
		int getHeight() ;
		bool isOutranged(int row, int column);
		bool isRepeat(int row, int column) ;
		ChessColor chessColor(int row, int column) ;

		bool isWinner(Chess chess) ;
		//与当前棋子连珠的棋子个数, 即连续同色
		int searchChess(Chess chess, Direction direction) ;
};
#endif
