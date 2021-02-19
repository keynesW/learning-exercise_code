#ifndef _ICHESSBOARD_H 
#define _ICHESSBOARD_H 
#include "global.h" 
class IChessBoard{
public:
		virtual void resize(int width, int height) = 0;
		virtual void init() = 0;
		virtual void addChess(Chess chess) = 0;
		virtual int getWhiteScore() = 0;
		virtual int getBlackScore() = 0;
		virtual int getWidth() = 0;
		virtual int getHeight() = 0; 
        virtual bool isOutranged(int row, int column) = 0; 
        virtual bool isRepeat(int row, int column) = 0;
		virtual ChessColor chessColor(int row, int column) = 0;
		virtual bool isWinner(Chess chess) = 0;
		//与当前棋子连珠的棋子个数, 即连续同色
		virtual int searchChess(Chess chess, Direction direction) = 0;
};
#endif
