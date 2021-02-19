#ifndef _IMAINWINDOW_H
#define _IMAINWINDOW_H
using namespace std;
#include <string>
#include "global.h"

class IMainWindow{
	public:
		virtual void init() = 0;
		virtual void update() = 0;
		virtual void showChessBoard() = 0;
		virtual void showMessageBox(string message) = 0;
		virtual void showLastResult() = 0;
		virtual void readChoice(int* choice) = 0;
		virtual void readChessPos(ChessColor chessColor, int* row, int* column) = 0;
		virtual void readChessBoardSize(int* rows, int* columns) = 0;
};
#endif
