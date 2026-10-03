//Name: Haydyn
//File Name: project1.cpp
//Date: 11 September, 2026
//Program Description: Explores a maze recursively and counts reachable cells

#include <iostream>
#include <fstream>

const int MAX_ROW = 10;
const int MAX_COLUMN = 10;

using namespace std;
//prototypes
void loadMaze (char maze[MAX_ROW][MAX_COLUMN]);
void printMaze(char maze[MAX_ROW][MAX_COLUMN]);
int exploreMaze(char maze[MAX_ROW][MAX_COLUMN],int row, int column, bool& exitReached);

int main() {
    char maze[MAX_ROW][MAX_COLUMN];
    
    loadMaze(maze);
    cout << "Original Maze:" << endl;
    printMaze(maze);

    int row;
    int column;
    bool check = false;

    cout << "Enter starting position: ";
    cin >> row >> column;

    //since they enter 1-10, makes it 0-9
    row--;
    column--;
    
    //sets starting spot and cannot be changed
    maze[row][column] = 'S';

    //recursive exploring
    int numOfSpots = exploreMaze(maze, row, column, check);

    //Prints maze after exploring
    cout << "Explored Maze:" << endl;
    printMaze(maze);

    //prints # of cells reachable
    cout << "Number of reachable cells :" << numOfSpots << endl;
    //Exit reached
    if (check)
    {
        cout << "Exit reached: Yes" << endl;
    }
    else
    {
        cout << "Exit Reached: No" << endl;
    }
    return 0;

}
void loadMaze (char maze[MAX_ROW][MAX_COLUMN])
{
    //imports file
    ifstream inFile("maze.txt");

    if (!inFile)
    {
        cout << "Could not open maze" << endl;
    }

    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            inFile >> maze[i][j];
        }
    }
    inFile.close();
}
void printMaze(char maze[MAX_ROW][MAX_COLUMN])
{
    //prints maze
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}
int exploreMaze(char maze[MAX_ROW][MAX_COLUMN], int row, int column, bool& exitReached) {
    //base case for out of bounds
    if (row >= MAX_ROW || row < 0 || column >= MAX_COLUMN || column < 0)
    {
        return 0;
    }
    
    //base case for walls, already explored spots and Start
    if (maze[row][column] != '.' && maze[row][column] != 'E' && maze[row][column] != 'S')
    {
        return 0;
    }
    
    //current spot is reachable
    int numOfSpots = 1;
    
    
    //base case for exit
    if (maze[row][column] == 'E')
    {
        exitReached = true;
        return 1;
    }
    //Remebers starting cell so it counts it as explorable and program still runs
    bool startingCell = (maze[row][column] == 'S');
    //sets current spot to explored
     maze[row][column] = '*';
    
     //Recursive calls
   numOfSpots += exploreMaze(maze, row + 1, column, exitReached); //Cell Below
   numOfSpots += exploreMaze(maze, row - 1, column, exitReached); //Cell Above
   numOfSpots += exploreMaze(maze, row, column + 1, exitReached); //Cell Right
   numOfSpots += exploreMaze(maze, row, column - 1, exitReached); //Cell Left

   //After all recusrion puts s back after exploring
   if (startingCell)
   {
       maze[row][column] = 'S';
   }

   //num of explorable spots
    return numOfSpots;

}
