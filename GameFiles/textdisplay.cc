#include "textdisplay.h"
#include "graphicdisplay.h"
#include <iostream>
using namespace std;

const int boardsize = 8;

TextDisplay::TextDisplay(GraphicDisplay *gDisplay): gDisplay(gDisplay){
	grid = new char *[boardsize]; //initializes the columns
	for (int x=0;x<boardsize;x++){
		grid[x] = new char[boardsize]; //initializes the rows
		for (int y=0;y<boardsize;y++){
			if (x%2==0&&y%2==0)
				grid[x][y] = '_'; //determines whether it is white square or not
			else if (x%2==1&&y%2==1)
				grid[x][y] = '_'; //_ is a white square
			else
				grid[x][y] = ' ';
		}
	}
}

void TextDisplay::draw(char c, int x, int y){
	grid[x][y] = c;
	gDisplay->draw(c, x, y);
}

void TextDisplay::undraw(int x, int y){
	if (x%2==0&&y%2==0)
		grid[x][y] = '_';
	else if (x%2==1&&y%2==1)
		grid[x][y] = '_';
	else
		grid[x][y] = ' ';

	gDisplay->undraw(x, y);
}

void TextDisplay::notifyWin(char c){
	cout << "Checkmate! ";
	this->notifyResign(c);
	gDisplay->notifyWin(c);
}

void TextDisplay::notifyCheck(char c){
	if (c=='b')
		cout << "Black ";
	else
		cout << "White ";
	cout << "is in check." << endl;
	gDisplay->notifyCheck(c);
}

void TextDisplay::notifyDraw(){
	cout << "Stalemate!" << endl;
	gDisplay->notifyDraw();
}

void TextDisplay::notifyResign(char c){
        if (c=='b')
                cout << "Black";
        else
                cout << "White";
        cout << " wins!" << endl;
	gDisplay->notifyResign(c);
}

void TextDisplay::clearBoard(){
	 for (int x=0;x<boardsize;x++){
		for (int y=0;y<boardsize;y++){
			if (x%2==0&&y%2==0)
                                grid[x][y] = '_';
               	 	else if (x%2==1&&y%2==1)
           	      		grid[x][y] = '_';
               	 	else
                      		grid[x][y] = ' ';
                }
        }
	gDisplay->clearBoard();
}

void TextDisplay::print(){
	for (int x = 0;x < boardsize; x++){
		cout << x + 1 << "   ";
		for (int y=0;y<boardsize;y++){
			cout << grid[x][y];
		}
		cout << endl;
	}
	cout << endl;
	cout << "    ";
	for(int i = 0; i < 8; i++){
		cout << (char) (i + 'a');
	}
	cout << endl;
}	

TextDisplay::~TextDisplay(){
	for (int x=0;x<boardsize;x++){
		delete [] grid[x];
	}
	delete [] grid;
	grid = NULL;
}
