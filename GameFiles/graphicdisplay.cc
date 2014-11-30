#include "board.h"
#include "window.h"
#include "display.h"
#include "graphicdisplay.h"
#include <iostream>
#include <sstream>
using namespace std;

GraphicDisplay::GraphicDisplay() {
	window = new Xwindow(500, 560);
	//create black base
	window->fillRectangle(0,0,500,560, Xwindow::Black);
	//create checkered pattern and legend (on the sides)
	for(int i = 0; i < 8; i++){
		stringstream ss;
		string s;
		char c = i + 'a';
		ss << c;
		ss >> s;
		window->drawString(i*(450/8) + 50, 10, s, Xwindow::White);
		window->drawString(i*(450/8) + 50, 490, s, Xwindow::White);
		stringstream ss1;
		string s1;
		ss1 << i + 1;
		ss1 >> s1;
		for(int j = 0; j < 8; j++){
			
			if(i % 2 == 0 && j % 2 == 0){
				window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
			}
			else if(i % 2 == 1 && j % 2 == 1){
				window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
			}
			else{
				window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Brown);
			}
		}
		window->drawString(10, i*(450/8) + 50, s1, Xwindow::White);
		window->drawString(485, i*(450/8) + 50, s1, Xwindow::White);
        }
}

GraphicDisplay::~GraphicDisplay() {
	delete window;
}

void GraphicDisplay::clearBoard() {
	//redraw checkered pattern
	for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                        if(i % 2 == 0 && j % 2 == 0){
                                window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
                        }
                        else if(i % 2 == 1 && j % 2 == 1){
                                window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
                        }
                        else{
                                window->fillRectangle(i*(450/8) + 25, j*(450/8) + 25, 450/8, 450/8, Xwindow::Brown);
                        }
                }
        }	
}

void GraphicDisplay::draw(char c, int row, int col) {
	//draw square for piece
	if(c >= 'a' && c <= 'z'){
		window->fillRectangle(col*(450/8) + 35, row*(450/8) + 40, 450/8 - 22, 450/8 - 27, Xwindow::Black);
	}
	else{
		window->fillRectangle(col*(450/8) + 35, row*(450/8) + 40, 450/8 - 22, 450/8 - 27, Xwindow::White);
	}
	//draw the string for the piece inside the square
	if(c == 'p') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "pawn", Xwindow::White);
	else if(c == 'b') window->drawString(col*(450/8) + 35, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "bishop", Xwindow::White);
	else if(c == 'r') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "rook", Xwindow::White);
	else if(c == 'n') window->drawString(col*(450/8) + 35, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "knight", Xwindow::White);
	else if(c == 'q') window->drawString(col*(450/8) + 37, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "queen", Xwindow::White);
	else if(c == 'k') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "king", Xwindow::White);
	else if(c == 'P') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "PAWN", Xwindow::Black);
	else if(c == 'B') window->drawString(col*(450/8) + 35, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "BISHOP", Xwindow::Black);
	else if(c == 'R') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "ROOK", Xwindow::Black);
	else if(c == 'N') window->drawString(col*(450/8) + 35, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "KNIGHT", Xwindow::Black);
	else if(c == 'Q') window->drawString(col*(450/8) + 37, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "QUEEN", Xwindow::Black);
	else if(c == 'K') window->drawString(col*(450/8) + 40, ((row*(450/8) + 30) + ((row+1)*(450/8) + 30))/2, "KING", Xwindow::Black);
}

void GraphicDisplay::undraw(int row, int col) {
	//redraw the specific square on the board
	if(row % 2 == 0 && col % 2 == 0){
		window->fillRectangle(col*(450/8) + 25, row*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
	}
	else if(row % 2 == 1 && col % 2 == 1){
		window->fillRectangle(col*(450/8) + 25, row*(450/8) + 25, 450/8, 450/8, Xwindow::Red);
	}
	else{
		window->fillRectangle(col*(450/8) + 25, row*(450/8) + 25, 450/8, 450/8, Xwindow::Brown);
	}
}

void GraphicDisplay::notifyWin(char c) {
	//refill message area
	window->fillRectangle(0, 500, 500, 30, Xwindow::Black);
	//draw message
	if(c == 'w'){
		window->drawString(205, 515, "White wins!", Xwindow::White);
	}
	else{
		window->drawString(205, 515, "Black wins!", Xwindow::White);
	}
}

void GraphicDisplay::notifyCheck(char c) {
	//refill message area
	window->fillRectangle(0, 500, 500, 30, Xwindow::Black);
	//draw message
	if(c == 'w'){
                window->drawString(195, 515, "White is in check!", Xwindow::White);
        }
        else{
                window->drawString(195, 515, "Black is in check!", Xwindow::White);
        }
}

void GraphicDisplay::notifyDraw() {
	//refill message area
	window->fillRectangle(0, 500, 500, 30, Xwindow::Black);
	//draw message
	window->drawString(210, 515, "Stalemate!", Xwindow::White);
}

void GraphicDisplay::notifyResign(char c) {
	//refill message area
	window->fillRectangle(0, 500, 500, 30, Xwindow::Black);
	//draw message
	if(c == 'w'){
		window->drawString(200, 515, "Black resigned", Xwindow::White);
                window->drawString(205, 525, "White wins!", Xwindow::White);
        }
        else{
		window->drawString(200, 515, "White resigned", Xwindow::White);
                window->drawString(205, 525, "Black wins!", Xwindow::White);
        }
}

void GraphicDisplay::updateScore(float white, float black){
	//clear old score
	window->fillRectangle(0, 532, 500, 28, Xwindow::Black);
	//obtain string form of the numbers and print them
	stringstream ss;
	stringstream ss1;
	string sWhite;
	string sBlack;
	ss << white;
	ss1 << black;
	ss >> sWhite;
	ss1 >> sBlack;
	window->drawString(5, 550, "                            White - " + sWhite + "                                  Black - " + sBlack, Xwindow::White);
}

void GraphicDisplay::clearMessage() {
	//refill message area
	window->fillRectangle(0, 500, 500, 30, Xwindow::Black);
}
