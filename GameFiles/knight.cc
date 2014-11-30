#include "piece.h"
#include "knight.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;

Knight::Knight(Board *board): Piece(board) {}

Knight::~Knight() {
	if(validMoves.size() != 0) deleteValidMoves();
	if(legalMoves.size() != 0) deleteLegalMoves();
}

bool Knight::isLegal(int row, int col) {
        bool isLegal = false;
        if(isValid(row, col)){
                int oldRow = position.row;
                int oldCol = position.col;
                Piece *enemy = board->board[row][col];
                if(enemy != 0) board->removePiece(row, col);
                position.row = row;
                position.col = col;
                board->board[row][col] = this;
                board->board[oldRow][oldCol] = 0;
                board->updateValidMoves();

                if(board->isCheck(colour)){
                        isLegal = false;
                }
                else isLegal = true;
                position.row = oldRow;
                position.col = oldCol;
                board->board[row][col] = enemy;
                board->board[oldRow][oldCol] = this;
		if(enemy != 0){
			if(enemy->colour == 'b') board->black->push_back(enemy);
			else board->white->push_back(enemy);
		}
		board->updateValidMoves();
        }
        return isLegal;
}

bool Knight::updatePosition(int row, int col) {
	if(isValid(row, col)){
		int oldRow = position.row;
		int oldCol = position.col;
		Piece *enemy = board->board[row][col];
		if(enemy != 0) board->removePiece(row, col);
		position.row = row;
		position.col = col;
		board->board[row][col] = this;
		board->board[oldRow][oldCol] = 0;
		board->updateValidMoves();

		if(board->isCheck(colour)){
			position.row = oldRow;
			position.col = oldCol;
			board->board[row][col] = enemy;
			board->board[oldRow][oldCol] = this;
			cout << "Move puts king in check" << endl << endl;
			board->updateValidMoves();
			if(enemy != 0){
				if(enemy->colour == 'b') board->black->push_back(enemy);
				else board->white->push_back(enemy);
			}
			return false;
		}

		if(board->board[oldRow][oldCol] == 0 && enemy != 0){
			delete enemy;
		}

		char opp = colour == 'w' ? 'b' : 'w';
		if(board->isCheck(opp)){
			board->display->notifyCheck(opp);
		}

		board->updateLegalMoves();
		return true;
	}
	else{
		cout << "Illegal move" << endl << endl;
		return false;
	}
}

bool isL(int row, int col, int newrow, int newcol){ //checks if the movement follows a L shape that a knight should
	if(row == newrow + 2 && col == newcol + 1) return true;
	else if(row == newrow + 2 && col == newcol - 1) return true;
	else if(row == newrow - 2 && col == newcol + 1) return true;
	else if(row == newrow - 2 && col == newcol - 1) return true;
	else if(row == newrow + 1 && col == newcol + 2) return true;
	else if(row == newrow + 1 && col == newcol - 2) return true;
	else if(row == newrow - 1 && col == newcol + 2) return true;
	else if(row == newrow - 1 && col == newcol - 2) return true;
	else return false;
}


bool Knight::isValid(int row, int col){
	if(inRange(row, col) && isL(position.row, position.col, row, col)){
		if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)){
			return true;
		}
		
	}
	//if none of the cases were true, it is an invalid move
	return false;
}
