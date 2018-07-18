/*
 * @Name:			Mohammad Qureshi
 * @Project:		Maze Generator & Solver
 * @Objective:		Generate a random maze and calculate a solution.
 * @Time:			03:00 PM - April 19th, 2015
 */

#include <stack>

int procChoice();

class Maze
{
	public:
		Maze( int height, int width );
		int getUnvisitedNeighbor( int i, int j, bool solve );
		void generateMaze( bool REAL_TIME_FLAG );
		void solveMaze( bool REAL_TIME_FLAG );
		void printMaze( bool REAL_TIME_FLAG, bool LAST_FLAG );
		
	private:
		const int height;
		const int width;
		int **grid;
		int **hWalls;
		int **vWalls;
		std::stack<int> path;
};