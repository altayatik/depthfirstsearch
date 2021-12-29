#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"

char * solveMaze(Maze * m) {
    //An obvious upper bound on the size of the solution path is the number
    //of squares in the maze + 1 (to account for the '\0'). You could make
    //this a tighter bound by accounting for how many walls there are, but
    //this approach is good enough!
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {
	int XP = curpos.xpos;
	int YP = curpos.ypos;
	
	//check height and width
	if((XP >= m -> width) || (YP >= m -> height)){
		return 0;
	} 
	//check x and y positions
	if((XP < 0) || (YP < 0)){
		return 0;
	}
	//check for hashtag
	if(m->maze[YP][XP].type == '#'){
		return 0;
	}
	//cheeck if visited
	if(m->maze[YP][XP].visited != 0){
		return 0;
	}
	//check if end
	if(m->maze[YP][XP].type == END){
		path[step] = '\0';
		return 1;	
	}
	//set maze
	m->maze[YP][XP].visited = 1;

	int newstep = step + 1;

	//north position check
	MazePos nor = {nor.xpos = XP, nor.ypos = (YP) - 1};
	if(depthFirstSolve(m, nor, path, newstep) == 1){
		path[step] = NORTH;
		return true;
	}
	
	//south position check
	MazePos sou = {sou.xpos = XP, sou.ypos = (YP) + 1};
	if((depthFirstSolve(m, sou, path, newstep)) == 1){
		path[step] = SOUTH;
		return true;
	}

	//west position check
	MazePos wes = {wes.xpos = (XP) - 1, wes.ypos = YP};
	if((depthFirstSolve(m, wes, path, newstep)) == 1){
		path[step] = WEST;
		return true;
	}

	//east position check
	MazePos eas = {eas.xpos = (XP) + 1, eas.ypos = YP};
	if((depthFirstSolve(m, eas, path, newstep)) == 1){
		path[step] = EAST;
		return 1;
	}

	return 0;
}
