#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <iostream>

class windowDisplay {
	public:
	virtual ~windowDisplay();
	//draw the current grid to the screen
	virtual void draw(char, int, int)=0;
	//remove the piece if it exists at the specified position
	virtual void undraw(int, int)=0;
	//print the winner
	virtual void notifyWin(char)=0;
	//print who is in check
	virtual void notifyCheck(char)=0;
	//print that there is a draw
	virtual void notifyDraw()=0;
	//print who has resigned
	virtual void notifyResign(char)=0;
	//clear the board
	virtual void clearBoard()=0;
};

#endif
