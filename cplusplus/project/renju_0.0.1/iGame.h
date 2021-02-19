#ifndef _IGAME_H
#define _IGAME_H
using namespace std;
class IGame{
	public:
		virtual void start() = 0;
		virtual bool resume() = 0;
		virtual void end() = 0;
};
#endif 
