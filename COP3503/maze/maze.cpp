/*
 * @Name:			Mohammad Qureshi
 * @Project:		Maze Generator & Solver
 * @Objective:		Generate a random maze and calculate a solution.
 * @Time:			03:00 PM - April 19th, 2015
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <time.h>
#include <unistd.h>
#include <vector>

#include "maze.h"

using namespace std;

vector<Maze*> mazes;
const string NOCOLOR = "\033[0m";
const string RED = "\033[0;31m";
const string GREEN = "\033[0;32m";
const string CORN = "+";
const string hWALL = "---";
const string vWALL = "|";
const string hSPACE = "   ";
const string vSPACE = " ";
const string iPATH = RED + " * " + NOCOLOR;
const string cPATH[] = { " ← ", " ↑ ", " → ", " ↓ " };

/*
 * grid[i][j] = 0; //Unvisited Cell
 * grid[i][j] = 1; //Visited Cell
 * grid[i][j] = 2; //Incorrect Path
 * grid[i][j] = 3; //West Path
 * grid[i][j] = 4; //North Path
 * grid[i][j] = 5; //East Path
 * grid[i][j] = 6; //South Path
 */

 
int main() //Theoretically, a maze of any combination of columns and rows may be generated.
{
	srand( time(0) );
	int choice = 0;
	
	cout << NOCOLOR;
	cout << "\nThis program will generate a maze and calculate its solution.\n\n";
	
	while( (choice = procChoice()) != 6 )
	{
		switch( choice )
		{
			case -1: cout << "Error: No maze has been generated yet. Please start with Option 1.\n\n"; break;
			case 3: mazes[0]->solveMaze( false ); break;
			case 4: mazes[0]->solveMaze( true ); break;
			case 5: mazes[0]->printMaze( false, false ); break;
		}
	}
	
	cout << "\n";
	return 0;
}


int procChoice() //Process constant choice selection from menu.
{
	string input = "";
	int choice = 0;
	int MAZE_H = 0;
	int MAZE_W = 0;
	
	cout << "\t1. Generate New Maze\n";
	cout << "\t2. Generate New Maze (Real Time)\n";
	cout << "\t3. Solve Maze\n";
	cout << "\t4. Solve Maze (Real Time)\n";
	cout << "\t5. Print Maze\n";
	cout << "\t6. Exit\n\n";
	cout << "Choice: ";
	
	while( true )
	{
		getline( cin, input );
		stringstream convert( input );
		if( convert >> choice && choice >= 1 && choice <= 6 ) break;
		else cout << "Please enter your choice as an integer between 1 and 6: ";
	}
	
	if( choice == 1 || choice == 2 )
	{
		cout << "Enter a number for the maze's height (5-25): ";
		while( true )
		{
			getline( cin, input );
			stringstream STREAM( input );
			if( STREAM >> MAZE_H && MAZE_H >= 5 && MAZE_H <= 25 ) break;
			cout << "Please enter a number between 5 and 25: ";
		}
		
		cout << "Enter a number for the maze's width (5-25): ";
		while( true )
		{
			getline( cin, input );
			stringstream STREAM( input );
			if( STREAM >> MAZE_W && MAZE_W >= 5 && MAZE_W <= 25 ) break;
			cout << "Please enter a number between 5 and 25: ";
		}
		
		if( !mazes.empty() ) mazes.pop_back();
		mazes.push_back( new Maze(MAZE_H, MAZE_W) );
		
		if( choice == 1 ) mazes[0]->generateMaze( false );
		else mazes[0]->generateMaze( true );
	}
	else if( choice != 6 && mazes.empty() ) choice = -1;
	
	return choice;
}


Maze::Maze( int height, int width ):height( height ), width( width ) //Constant height and width are initialized without "this".
{
	grid = new int *[height];
	hWalls = new int *[height+1];
	vWalls = new int *[height];
	
	int i;
	
	for( i = 0; i < height; i++ )
	{
		grid[i] = new int[width];
		hWalls[i] = new int[width];
		vWalls[i] = new int[width+1];
	}
	hWalls[i] = new int[width];
}


int Maze::getUnvisitedNeighbor( int i, int j, bool solve ) //Non-diagonal neighbors only.
{
	vector<int> cells;
	
	if( solve == false )									//For maze generation, checks for visited cells.
	{
		if( j >= 1 && grid[i][j-1] == 0 )					//Left
		{
			cells.push_back( (i * width) + (j - 1) );
		}
		if( i >= 1 && grid[i-1][j] == 0 )					//Up
		{
			cells.push_back( ((i - 1) * width) + j );
		}
		if( j < width - 1 && grid[i][j+1] == 0 )			//Right
		{
			cells.push_back( (i * width) + (j + 1) );
		}
		if( i < height - 1 && grid[i+1][j] == 0 )			//Down
		{
			cells.push_back( ((i + 1) * width) + j );
		}
		
		if( !cells.empty() )
		{
			random_shuffle( cells.begin(), cells.end() );
			return cells.front();
		}
		else return -1;
	}
	else																//For maze solving, checks for walls.
	{
		if( j >= 1 && grid[i][j-1] < 2 && vWalls[i][j] == 0 )			//Left
		{
			cells.push_back( (i * width) + (j - 1) );
		}
		if( i >= 1 && grid[i-1][j] < 2 && hWalls[i][j] == 0 )			//Up
		{
			cells.push_back( ((i - 1) * width) + j );
		}
		if( j < width - 1 && grid[i][j+1] < 2 && vWalls[i][j+1] == 0 )	//Right
		{
			cells.push_back( (i * width) + (j + 1) );
		}
		if( i < height - 1 && grid[i+1][j] < 2 && hWalls[i+1][j] == 0)	//Down
		{
			cells.push_back( ((i + 1) * width) + j );
		}
		
		if( !cells.empty() )
		{
			random_shuffle( cells.begin(), cells.end() );
			return cells.front();
		}
		else return -1;
	}
}


void Maze::generateMaze( bool REAL_TIME_FLAG ) //Maze is generated using the DFS (Depth-First Search) algorithm.
{
	int i, j, k, cell, newI, newJ;
	int usec = 50000;
	
	for( i = 0; i < height; i++ )
	{
		for( j = 0; j < width; j++ )
		{
			grid[i][j] = 0;
			hWalls[i][j] = 1;
			hWalls[i+1][j] = 1;
			vWalls[i][j] = 1;
			vWalls[i][j+1] = 1;
		}
	}
	
	vWalls[0][0] = 0;	//Entrance
	vWalls[i-1][j] = 0;	//Exit
	
	k = 0;
	cell = 0;
	newI = 0;
	newJ = 0;
	
	while( k < height * width - 1 )					//While there are still unvisited cells, 
	{
		i = cell / width;
		j = cell % width;
		grid[i][j] = 1;								//mark the current cell as visited 
		cell = getUnvisitedNeighbor( i, j, false );	//and find a non-diagonal, unvisited neighbor at random.
		
		if( cell > 0 )								//If an appropriate neighbor is found, remove the wall 
		{
			newI = cell / width;
			newJ = cell % width;
			
			if( newI == i )
			{
				if( newJ < j )
				{
					vWalls[i][j] = 0;
				}
				else
				{
					vWalls[i][j+1] = 0;
				}
			}
			else
			{
				if( newI < i )
				{
					hWalls[i][j] = 0;
				}
				else
				{
					hWalls[i+1][j] = 0;
				}
			}
			
			path.push( cell );						//and add the new cell to our path.
			k++;
			usec = 50000;
		}
		else										//Otherwise, backtrack and try again.
		{
			path.pop();
			cell = path.top();
			usec = 10000;
		}
		
		if( REAL_TIME_FLAG == true )
		{
			printMaze( false, false );
			usleep( usec );
		}
	}
	
	if( REAL_TIME_FLAG == false ) printMaze( false, false );
	cout << "A new maze has been randomly generated.\n\n";
}


void Maze::solveMaze( bool REAL_TIME_FLAG ) //Solve maze using the the DFS (Depth-First Search) algorithm.
{
	for( int i = 0; i < height; i++ )					//First, the grid must be emptied.
	{
		for( int j = 0; j < width; j++ )
		{
			grid[i][j] = 0;
		}
	}
	
	while( !path.empty() )								//The path too.
	{
		path.pop();
	}
	
	int i = 0;
	int j = 0;
	int cell = 0;
	int prevCell = 0;
	int changeInCell = 0;
	int arrow = 5;										//Required to draw wrong path directional on the ends of incorrect paths.
	int usec = 50000;
	
	while( grid[height-1][width-1] < 3 )				//While we still haven't reached the exit, 
	{
		i = cell / width;
		j = cell % width;
		changeInCell = cell - prevCell;
		prevCell = cell;
		
		if( grid[i][j] >= 3 ) grid[i][j] = 2;			//mark the current cell as wrong path if already visited and the correct directional otherwise.
		grid[i][j] = arrow;
		
		if		( changeInCell == -1		&& grid[i][j+1] != 2 )	grid[i][j+1] = 3;	//Left
		else if	( changeInCell == -width	&& grid[i+1][j] != 2 )	grid[i+1][j] = 4;	//Up
		else if	( changeInCell == 1			&& grid[i][j-1] != 2 )	grid[i][j-1] = 5;	//Right
		else if	( changeInCell == width		&& grid[i-1][j] != 2 )	grid[i-1][j] = 6;	//Down
		
		if( i == height - 1 && j == width - 1 )
		{
			grid[i][j] = arrow;
			break;
		}
		
		cell = getUnvisitedNeighbor( i, j, true );		//Then find a non-diagonal, unvisited neighbor at random.
		
		if( cell > 0 )									//If an appropriate neighbor is found, move to it, 
		{
			if( grid[i][j] == 2 ) grid[i][j] = arrow;
			path.push( cell );							//and add the new cell to our path.
			usec = 50000;
		}
		else											//Otherwise, backtrack and try again.
		{
			if( grid[i][j] >= 3 ) grid[i][j] = 2;
			path.pop();
			cell = path.top();
			usec = 10000;
		}
		
		if( REAL_TIME_FLAG == true )
		{
			cout << "\n";
			printMaze( true, false );
			usleep( usec );
		}
	}
	
	if( REAL_TIME_FLAG == true )
	{
		cout << "\n";
		printMaze( false, true );
	}
	else printMaze( false, false );
}


void Maze::printMaze( bool REAL_TIME_FLAG, bool LAST_FLAG ) //Print out the maze with the correct and incorrect path.
{
	int i;
	cout << "\n";
	
	for( i = 0; i < height + 1; i++ )
	{
		for( int j = 0; j < width; j++ )
		{
			if( hWalls[i][j] == 1 ) cout << CORN << hWALL;
			else cout << CORN << hSPACE;
		}
		cout << CORN << "\n";
		
		if( i < height )
		{
			for( int j = 0; j < width + 1; j++ )
			{
				if( j < width )
				{
					if( vWalls[i][j] == 0 ) cout << vSPACE;
					else cout << vWALL;
					
					if( grid[i][j] == 2 ) cout << iPATH;
					else if( grid[i][j] >= 3 ) cout << GREEN << cPATH[ grid[i][j] - 3 ] << NOCOLOR;
					else cout << hSPACE;
				}
				else if( vWalls[i][j] == 1 ) cout << vWALL;
			}
			cout << "\n";
		}
	}
	
	cout << NOCOLOR;
	
	if( grid[height-1][width-1] >= 3 )
	{
		if( REAL_TIME_FLAG == true ) cout << "\n\n";
		else cout << "\n";
		if( LAST_FLAG == true ) cout << "\n";
		cout << "Solution complete. \"" << iPATH << "\" = Incorrect Path\n\n";
	}
	else if( REAL_TIME_FLAG == false ) cout << "\n";
}