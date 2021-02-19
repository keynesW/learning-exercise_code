/*******************************************************************
 *
 *     File Name    :      ChessBoard.cpp
 *     Author       :      Keynes 
 *     QQ           :      1446160257  
 *     Email        :      1446160257@qq.com 
 *     Blog： :      http://www.    .com/ 
 *     Created Time :      Wed 18 Nov 2020 06:11:53 PM CST
 *     Description  :      Hello Word in C++ , GUN-style
 *
 ******************************************************************/
#include <iostream>
#include "ChessBoard.h" 
using namespace std;
ChessBoard:: ChessBoard():width(0),height(0),whitescore(0),blackscore(0){}
ChessBoard:: ChessBoard(int _width, int _height):width(_width),height(_height){}
ChessBoard:: ~ChessBoard(){}
void ChessBoard:: resize(int _width, int _height)
{
    cout << "chessboard resize ..." << endl;
    width = _width;
    height = _height;
}

void ChessBoard:: init()
{
    chessboard.clear();
    cout << "chessboard init ..." << endl;
    for(int i = 0 ; i < height ; i ++ )
    {
        for (int j = 0 ; j < width ; j++)
        {
            ChessPos chesspos(i,j);
            Chess chess(chesspos,COLOR_BLANK);
            chessboard.insert(chess);
            //addChess(chess);
            //ChessBoard.add(chess,COLOR_BLACK);
        }
    }
}
void ChessBoard:: addChess(Chess chess) 
{
    if(chessboard.at(chess.first) == COLOR_BLANK)
    {
        chessboard.erase(chess.first);
        chessboard.insert(chess);
    }
}
int ChessBoard:: getWhiteScore()
{
    return whitescore;
}
int ChessBoard:: getBlackScore()
{
    return blackscore;
}
int ChessBoard:: getWidth()
{
    return width;
}
int ChessBoard:: getHeight() 
{
    return height;
}
bool ChessBoard:: isOutranged(int row, int column)
{
    if( row >= height || row < 0 || column >= width || column < 0 )
        return true;
    return false;
}
bool ChessBoard:: isRepeat(int row, int column)
{
    ChessPos chesspos(row,column);
    if(chessboard.at(chesspos) == COLOR_BLANK)
        return false;
    return true;
}
ChessColor ChessBoard:: chessColor(int row, int column) 
{
    ChessPos chesspos(row,column);
    return chessboard.at(chesspos);
}
/*{{{
bool ChessBoard:: isWinner(Chess chess) 
{
    int cunt = 1;
//    Direction searchend = RIGHT;

    cout << "in is winner  cunt :" << cunt << endl;
    for(int i = 0 ; i < 4 ; i++)
    {
        cunt =  searchChess(chess,(Direction)i) + searchChess(chess,(Direction)(i+4));
        cout << "in is winner  cunt :" << cunt << endl;
        if(cunt > 4)
            return true;
    }
    //cout << "in is winner  cunt :" << cunt << endl;
    return false;
}
//与当前棋子连珠的棋子个数, 即连续同色
int ChessBoard:: searchChess(Chess chess, Direction direction) 
{
    int cunt = 0;
    int row = chess.first.first;
    int column = chess.first.second;
    ChessColor color = chess.second;
    ChessPos chessPos;

    cout << "in searchchess ..." << endl;
    cout << "row :" << row << endl;
    cout << "column : "<< column << endl;
    cout << "color : "<< color << endl;
    cout << "LEFT : " << direction <<endl;
    cout << "direction : " << direction <<endl;
    switch(direction)
    {
    case LEFT: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row,column -1);
        cout << (chessboard.at(chessPos)) << endl;
        cout << (chessboard.at(chessPos) == color) << endl;
        if( column > 0 && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row,column-1);
            Chess chess(chesspos,color);
            cunt =1 + searchChess(chess,direction);
            cout << "in search LEFT  cunt :" << cunt << endl; 
        } 
        cout << endl;
        break;

    case LEFTTOP: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row-1,column -1);
        if( row > 0 && column > 0  && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row-1,column-1);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search LEFTTOP  cunt :" << cunt << endl; 
        }
        cout << endl;
        break;
    case TOP: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row-1,column );
        if( row > 0 && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row-1,column);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search TOP  cunt :" << cunt << endl; 
        }
        cout << endl;
        break;
    case RIGHTTOP: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row-1,column+1 );
        if( row > 0 && column < width  && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row-1,column+1);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search RIGHTTOP cunt :" << cunt << endl; 
        }
        cout << endl;
        break;

////////////////////////////////////////////////////////////////////////////////////

    case LEFTBOTTOM: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row+1,column-1 );
        if( row < height && column > 0 && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row+1,column-1);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search LEFTBOTTOM cunt :" << cunt << endl; 
        }
        cout << endl;
        break;

    case BOTTOM: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row+1,column );
        if( row < height && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row+1,column);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search BOTTOM cunt :" << cunt << endl; 
        }
        cout << endl;
        break;

    case RIGHTBOTTOM: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row+1,column+1 );
        if( column < width && row < height && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row+1,column+1);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search RIGHTBOTTOM cunt :" << cunt << endl; 
        }
        cout << endl;
        break;

    case RIGHT: 
        cout << "in case " << endl; 
        chessPos = ChessPos(row,column+1 );
        if( column < width && chessboard.at(chessPos) == color )
        {
            ChessPos chesspos(row,column+1);
            Chess chess(chesspos,color);
            cunt += searchChess(chess,direction);
            cout << "in search RIGHT cunt :" << cunt << endl; 
        }
        cout << endl;
        break;
    default:
        cout << "default " << endl;
    }

    return cunt;
}
*//*}}}*/

bool ChessBoard::isWinner(Chess chess){
	int direction = 0;
	int count = 0;
	for(direction = 0; direction < 4; direction++){
		count = 1 + searchChess(chess, (Direction)direction) 
			+ searchChess(chess, (Direction)(direction + 4));
		if(count > 4){
			if(chess.second == COLOR_BLACK){
				blackscore += 1;
			}else{
				whitescore += 1;
			}
			return true;
		}
	}
	return false; 
}   

//搜索
int ChessBoard::searchChess(Chess chess, Direction direction){
	int row = chess.first.first;
	int column = chess.first.second;
	ChessColor chessColor = chess.second;
	ChessPos chessPos;
	int count = 0;
	switch (direction)
	{
		case LEFT:
			chessPos = ChessPos(row, column - 1); //左边位置
			if((column > 0) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case LEFTTOP:
			chessPos = ChessPos(row - 1, column - 1); //左上边角位置
			if((row > 0) && (column > 0) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor),direction);
			}
			break;
		case TOP:
			chessPos = ChessPos(row - 1, column); //上
			if((row > 0) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case RIGHTTOP:
			chessPos = ChessPos(row - 1, column + 1); //右上
			if((column < width - 1) && ( row > 0) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case RIGHT:
			chessPos = ChessPos(row, column + 1); //右方位置
			if((column < width - 1) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case RIGHTBOTTOM:
			chessPos = ChessPos(row + 1, column + 1); //右下角位置
			if((column < width - 1) && (row < height - 1) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case BOTTOM:
			chessPos = ChessPos(row + 1, column); //下方位置
			if((row < height - 1) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
		case LEFTBOTTOM:
			chessPos = ChessPos(row + 1, column - 1); //左下角位置
			if((column > 0) && (row < height - 1) && (chessboard.at(chessPos) == chessColor))
			{
				count = 1 + searchChess(Chess(chessPos, chessColor), direction);
			}
			break;
	}
	return count;
}

