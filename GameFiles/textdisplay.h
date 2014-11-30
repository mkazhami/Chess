#ifndef _TEXTDISPLAY_H_
#define _TEXTDISPLAY_H_
#include <iostream>
#include <sstream>

#include "display.h"
class GraphicDisplay;

class TextDisplay: public windowDisplay {
	char **grid;
	GraphicDisplay *gDisplay;
	public:
	TextDisplay(GraphicDisplay *);
	~TextDisplay();
	void clearBoard();
	void draw(char, int, int);
	void undraw(int, int);
	void notifyWin(char);
	void notifyCheck(char);
	void notifyDraw();
	void notifyResign(char);
	void print();
};

#endif
