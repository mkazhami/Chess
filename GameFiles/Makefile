CXX = g++
CXXFLAGS = -Wall -MMD 
EXEC = chess
OBJECTS = main.o board.o display.o textdisplay.o graphicdisplay.o window.o posn.o piece.o pawn.o bishop.o rook.o knight.o queen.o king.o level.o level1.o level2.o level3.o level4.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
