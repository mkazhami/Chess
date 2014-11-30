#include "piece.h"
#include "bishop.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;

Bishop::Bishop(Board *board): Piece(board) {}

Bishop::~Bishop() {
	if(validMoves.size() != 0) deleteValidMoves();
	if(legalMoves.size() != 0) deleteLegalMoves();
}

bool Bishop::isLegal(int row, int col) {
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
                //board->updateValidMoves();
		if(enemy != 0){
	                if(enemy->colour == 'b') board->black->push_back(enemy);
        	        else board->white->push_back(enemy);
			//board->display->draw(enemy->id, row, col);
		}
		board->updateValidMoves();
        }
        return isLegal;
}

bool Bishop::updatePosition(int row, int col) {
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

//checks if the inputs are between 0 and 7 and checks if the movement is diagonal
bool Bishop::inRange(int row, int col){
        if(row < 0 || row > 7 || col < 0 || col > 7) return false;
        if(absolute(position.row - row) != absolute(position.col - col)) return false;
        if(row == position.row && col == position.col) return false;
        return true;
}

bool Bishop::isValid(int row, int col){
	int rowTemp = row;
	int colTemp = col;
	if(inRange(row, col)){
		//checks if there are no pieces between where it starts and its destination by going through 4 different cases
		//since a bishop only has 4 directions of movement
		if(row > position.row){
			if(col > position.col){
				while(rowTemp > position.row + 1 && colTemp > position.col + 1){
					rowTemp--;
					colTemp--;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
			else{
				while(rowTemp > position.row + 1 && colTemp < position.col - 1){
					rowTemp--;
					colTemp++;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
		}
		else{
			if(col > position.col){
				while(rowTemp < position.row - 1 && colTemp > position.col + 1){
					rowTemp++;
					colTemp--;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
			else{
				while(rowTemp < position.row - 1 && colTemp < position.col - 1){
					rowTemp++;
					colTemp++;
					if(board->board[rowTemp][colTemp] != 0) return false;
				}
			}
		}
		
		//check if spot is empty or contains an enemy
		if(board->board[row][col] == 0 || (board->board[row][col]->colour != colour)) return true;
	}
	//if none of the cases were true, it is an invalid move
	return false;
}
