#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_

#include "display.h"
class Xwindow;

class GraphicDisplay: public windowDisplay {
	Xwindow *window;
	public:
	GraphicDisplay();
	~GraphicDisplay();
	void clearBoard();
	void draw(char, int, int);
	void undraw(int, int);
	void notifyWin(char);
	void notifyCheck(char);
	void notifyDraw();
	void notifyResign(char);
	void updateScore(float, float);
	void clearMessage();
};

#endif
