/*******************************************************************************
 * Author : 程柳峰
 * Email : xxx@xxx.com
 * Last modified : 2019-07-23 03:15
 * Filename : global.h
 * Description : 华清远见C++
 *******************************append******************************************/
#ifndef _GLOBAL_H
#define _GLOBAL_H
using namespace std;
#include <string>
#include <map>
#include <utility>

//棋子颜色类型

typedef string ChessColor;

#define COLOR_BLACK "AA"
#define COLOR_WHITE "BB"
#define COLOR_BLANK "||"

//坐标类型
typedef pair<int, int> ChessPos;

//棋子类，因为棋子类比较简单，所以直接使用pair<>作为棋子类，而无需自定义Chess类
typedef pair<ChessPos, ChessColor> Chess; 

//棋盘数据结构类型
typedef map<ChessPos, ChessColor> ChessBoardMap;

//以当前棋子为中心的8个方向
enum Direction{ 
	LEFT, LEFTTOP, TOP, RIGHTTOP, RIGHT, RIGHTBOTTOM, BOTTOM, LEFTBOTTOM 
};      
#endif
