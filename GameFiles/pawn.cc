#include "piece.h"
#include "pawn.h"
#include "posn.h"
#include "board.h"
#include <iostream>
using namespace std;

Pawn::Pawn(Board *board): Piece(board) { //constructor for pawn
	doubleMove = -1; //sets doubleMove to -1 to show that it hasn't performed a move that skips a space. Unique to pawn
}

Pawn::~Pawn() { //destructor for pawn
	if(validMoves.size() != 0) deleteValidMoves(); //deletes valid moves
	if(legalMoves.size() != 0) deleteLegalMoves(); //deletes legal moves
	id = 0;
}

bool Pawn::isLegal(int row, int col) { //returns true if moving to this position doesn't put the same side's king in check
					// no permanent moves are made
        bool isLegal = false; 
        if(isValid(row, col)){ //first checks if moving there obeys the piece's movement rules
		//then it temporarily moves to the position specified from the argument
                int oldRow = position.row;
                int oldCol = position.col;
                Piece *enemy = board->board[row][col];
                if(enemy != 0) board->removePiece(row, col);
                position.row = row;
                position.col = col;
                board->board[row][col] = this;
                board->board[oldRow][oldCol] = 0;
                board->updateValidMoves();
		//then it checks whether it puts the same side's king in check
                if(board->isCheck(colour)){
                        isLegal = false;
                }
                else isLegal = true;
		//then moves everything back where it was
                position.row = oldRow;
                position.col = oldCol;
                board->board[row][col] = enemy;
                board->board[oldRow][oldCol] = this;
                //if it removed an enemy it put it back on the board and the vector
		if(enemy != 0){
                	if(enemy->colour == 'b') board->black->push_back(enemy);
                	else board->white->push_back(enemy);
		//	board->display->draw(enemy->id, row, col);
		}
		board->updateValidMoves();
        }
        return isLegal;
}


bool Pawn::isEnPassant(int row, int col){ //checks if the pawn can perform an en passant. Unique to pawn
	//checks two sides differently since pawns can only move only up or only down
	if(colour == 'w' && row == position.row - 1 && (col == position.col + 1 || col == position.col -1)){
		Piece *possiblePawn = 0;
		if(col > position.col) possiblePawn = board->board[position.row][position.col + 1];
		else if(col < position.col) possiblePawn = board->board[position.row][position.col - 1];
		else return false;
		//similar to the isLegal function
		if(possiblePawn != 0 && possiblePawn->id == 'p' && possiblePawn->doubleMove == board->moveCount-1 && board->board[row][col] == 0){
			int oldRow = position.row;
			int oldCol = position.col;
			position.row = row;
			position.col = col;
			board->board[row][col] = this;
			board->board[oldRow][oldCol] = 0;
			board->display->undraw(row+1, col);
			board->removePiece(row+1, col);
			board->board[row+1][col] = 0;
			board->updateValidMoves();

			if(board->isCheck(colour)){
				board->board[row][col] = 0;
				board->board[oldRow][oldCol] = this;
				board->board[row+1][col] = possiblePawn;
				board->black->push_back(possiblePawn);
				board->updateValidMoves();
				board->display->draw(possiblePawn->id, row+1, col);
				return false;	
			}
			
			delete possiblePawn;
			board->display->draw(id, row, col);
			
			if(board->isCheck('b')){
				board->display->notifyCheck('b');
			}
			return true;
		}
		return false;
	}
	//does the same for the black side
	else if(colour == 'b' && row == position.row + 1 && (col == position.col + 1 || col == position.col -1)){
		Piece *possiblePawn = 0;
		if(col > position.col) possiblePawn = board->board[position.row][position.col + 1];
		else if(col < position.col) possiblePawn = board->board[position.row][position.col - 1];
		else return false;
		
		if(possiblePawn != 0 && possiblePawn->id == 'P' && possiblePawn->doubleMove == board->moveCount-1 && board->board[row][col] == 0){
			int oldRow = position.row;
			int oldCol = position.col;
			position.row = row;
			position.col = col;
			board->board[row][col] = this;
			board->board[oldRow][oldCol] = 0;
			board->display->undraw(row-1, col);
			board->removePiece(row-1, col);
			board->board[row-1][col] = 0;
			board->updateValidMoves();

			if(board->isCheck(colour)){
				board->board[row][col] = 0;
				board->board[oldRow][oldCol] = this;
				board->board[row-1][col] = possiblePawn;
				board->white->push_back(possiblePawn);
				board->updateValidMoves();
				board->display->draw(possiblePawn->id, row-1, col);
				return false;
			}
			
			delete possiblePawn;
			board->display->draw(id, row, col);
			
			if(board->isCheck('w')){
				board->display->notifyCheck('w');
			}
			return true;
		}
		return false;
	}
	return false;
}

bool Pawn::updatePosition(int row, int col) { //returns true if the piece was able to move to the position specified from the arguments
	if(isValid(row, col)){ //first it checks whether the piece can move there based on the piece's movement rules
		if(isEnPassant(row, col)){
			return true;
		}
		if(row == position.row + 2 || row == position.row - 2){ //the instance when jumped over a space is noted for use for en passant
			doubleMove = board->moveCount;
		}
		//checks if it puts it in check similar to isLegal
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
		
		//if the move was successful, it sees whether the move put the other king in check
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

bool Pawn::isValid(int row, int col){ //checks if where it wants to move obeys the pawn's movement rules
	if(colour == 'w' && inRange(row, col)){
		if(row == position.row - 1 && col == position.col && board->board[row][col] == 0) return true; //moving one space forward
		else if(position.row == 6 && row == position.row - 2 && col == position.col && board->board[row][col] == 0 && board->board[row+1][col] == 0) return true; //move two space forward
		else if(row == position.row - 1 && col == position.col - 1 && board->board[row][col] != 0 && board->board[row][col]->colour == 'b') return true; //attacking diagonally
		else if(row == position.row - 1 && col == position.col + 1 && board->board[row][col] != 0 && board->board[row][col]->colour == 'b') return true; //attacking diagonally
		else if(row == position.row - 1 && (col == position.col + 1 || col == position.col - 1) && board->board[row][col] == 0){ //en passant
			if((board->board[row+1][col] != 0 && board->board[row+1][col]->id == 'p')){
				if(board->board[row+1][col]->doubleMove == board->moveCount - 1) return true;
			}
		}
	}
	//same as above
	else if(colour == 'b' && inRange(row, col)){
		if(row == position.row + 1 && col == position.col && board->board[row][col] == 0) return true;
		else if(position.row == 1 && row == position.row + 2 && col == position.col && board->board[row][col] == 0 && board->board[row-1][col] == 0) return true;
		else if(row == position.row + 1 && col == position.col - 1 && board->board[row][col] != 0 && board->board[row][col]->colour == 'w') return true;
		else if(row == position.row + 1 && col == position.col + 1 && board->board[row][col] != 0 && board->board[row][col]->colour == 'w') return true; 
		else if(row == position.row + 1 && (col == position.col + 1 || col == position.col - 1) && board->board[row][col] == 0){
			if(board->board[row-1][col] != 0 && board->board[row-1][col]->id == 'P'){
				if(board->board[row-1][col]->doubleMove == board->moveCount-1) return true;
			}
		}
	}
	//if none of the cases were true, it is an invalid move
	return false;
}
