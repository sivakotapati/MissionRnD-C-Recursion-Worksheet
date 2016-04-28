/*
Find if there is a connecting path between two given points in the maze.
The maze is a matrix of order MxN, check if there exists a path between (x1,y1) and (x2,y2).
Two points are said to connected if there is a series of 1's non-diagonally.
Example:
Maze of order 4x4:

1	0	1	0
1	1	0	0
0	1	0	1
0	1	1	1

(x1,y1):(0,0)
(x2,y2):(2,3)

In this case, there exists a connected path:
1
1	1
	1		1
	1	1	1

Since there is a connected path, your function has to return 1.
If a path doesn't exist between two co-ordinates then return 0.
If the co-ordinates are invalid or size of the matrix is invalid then return 0.

Function Prototype :path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2) ;
Maze: Pointer to first element of an array .
rows : No of rows
columns : Columns
x1,x2,y1,y2: Co-ordinates

Hint : You can use path_exists as a wrapper function for your original recursive function which might take
more parameters .
*/

#include<stdlib.h>
int find_path(int *, int, int, int, int, int, int);
int is_safe(int*, int, int, int, int);
int wasHere[10][10] = { 0 };
int present = 0;

int path_exists(int *maze, int rows, int columns, int x1, int y1, int x2, int y2)
{
	if (maze == NULL || rows <= 0 || columns <= 0 || x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0)
		return 0;
	
	if (find_path(maze, rows, columns, x1, y1, x2, y2) && present){
		present = 0;
		return 1;
	}
	return 0;
}
int find_path(int *maze, int rows, int columns, int x1, int y1, int x2, int y2){
	int safe = is_safe(maze, rows, columns, x1, y1);
	if (safe && (x1 == x2&&y1 == y2)){
		present = 1;
		return 1;
	}
	else if (!safe && (x1 == x2&&y1 == y2))
	{
		present = 0;
		return 1;
	}
	else if (!safe){
		return 0;
	}

	//move up
	if (find_path(maze, rows, columns, x1 - 1, y1, x2, y2) == 1) return 1;

	//move forward
	if (find_path(maze, rows, columns, x1, y1 + 1, x2, y2) == 1) return 1;

	//move downward
	if (find_path(maze, rows, columns, x1 + 1, y1, x2, y2) == 1) return 1;

	//move backward
	if (find_path(maze, rows, columns, x1, y1 - 1, x2, y2) == 1) return 1;

	return 0;
}
int is_safe(int *maze, int rows, int columns, int x, int y){
	//if x,y are outside maze
	if (x < 0 || x >= rows || y < 0 || y >= columns)
		return 0;
	//if x1,y1 is not open or visited
	if ((*(maze + columns * x + y)) == 0 || wasHere[x][y] == 1)
		return 0;
	wasHere[x][y] = 1;
	return 1;
}