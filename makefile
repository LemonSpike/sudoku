sudoku: main.o sudoku.o
	g++ -g main.o sudoku.o -o sudoku

main.o: main.cpp sudoku.h
	g++ -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -c sudoku.cpp

clean:
	rm -f *.o sudoku
