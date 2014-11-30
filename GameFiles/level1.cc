#include "level.h"
#include "level1.h"
#include "board.h"
#include "posn.h"
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
using namespace std;

Level1::Level1(Board *board): Level(board) {}

void Level1::move() {
	int piece;
	int moveRand;
	Posn *move;
	
	board->updateValidMoves();
	board->updateLegalMoves();
	srand(time(0));
	if(colour == 'w'){
		piece = rand() % board->white->size();
		while((*(board->white))[piece]->legalMoves.size() == 0){
			piece = rand() % board->white->size();
		}
		moveRand = rand() % ((*(board->white))[piece]->legalMoves.size());
		move = (*(board->white))[piece]->legalMoves[moveRand];
		board->movePiece((*(board->white))[piece]->position.row, (*(board->white))[piece]->position.col, move->row, move->col);
	}
	else if(colour == 'b'){
		piece = rand() % board->black->size();
		while((*(board->black))[piece]->legalMoves.size() == 0){
			piece = rand() % board->black->size();
		}
		moveRand = rand() % ((*(board->black))[piece]->legalMoves.size());
		move = (*(board->black))[piece]->legalMoves[moveRand];
		board->movePiece((*(board->black))[piece]->position.row, (*(board->black))[piece]->position.col, move->row, move->col);
	}
}
