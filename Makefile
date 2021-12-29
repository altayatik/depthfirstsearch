CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
TESTS = -DTEST_NEWSHUFFLE -DTEST_SHUFFLE -DTEST_INTERLEAVE -DTEST_DIVIDE
GCC = gcc $(CFLAGS) $(TESTS)
EXEC = hw9
OBJS = hw9.o solver.o path.o maze.o mazehelper.o

VALGRIND = valgrind --tool=memcheck --leak-check=yes --verbose



$(EXEC): $(OBJS) path.h solver.h mazehelper.h
	$(GCC) $(TESTS) $(OBJS) -o $(EXEC)

all: test

test: $(EXEC)
	./$(EXEC) inputs/maze1 output1
	./$(EXEC) inputs/maze2 output2
	./$(EXEC) inputs/maze3 output3
	./$(EXEC) inputs/maze4 output4
	./$(EXEC) inputs/maze5 output5

memory: $(EXEC)
	$(VALGRIND) --log-file=log1.txt ./$(EXEC) inputs/maze1 output1
	$(VALGRIND) --log-file=log2.txt ./$(EXEC) inputs/maze2 output2
	$(VALGRIND) --log-file=log3.txt ./$(EXEC) inputs/maze3 output3
	$(VALGRIND) --log-file=log4.txt ./$(EXEC) inputs/maze4 output4
	$(VALGRIND) --log-file=log5.txt ./$(EXEC) inputs/maze5 output5

%.o : %.c
	$(GCC) -c $<

clean:
	/bin/rm -f *.o
	/bin/rm -f $(EXEC)
	/bin/rm -f output?
	/bin/rm -f *.txt