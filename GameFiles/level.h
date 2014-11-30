#ifndef _LEVEL_H_
#define _LEVEL_H_

class Board;

class Level {
	public:
	//keep a pointer to the board so that the AI can decide where to move
	Board *board;

	//colour of the Level - black or white
	char colour;
	
	//constructor
	Level(Board *board);
	
	//destructor
	virtual ~Level();
	
	//decide the move to take - depends on difficulty level
	virtual void move()=0;
};

#endif
