/*
 * Name: AJ Garner
 * Date Submitted: 2/12/2023
 * Lab Section: 004
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below
Grouping::Grouping(string fileName){
    //these two lines will declare the file variable and open the file
    ifstream input;
    input.open(fileName);
    
    //needed to compare the grid postions 
    char a;

    //nested for loop to go through the grid
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            input >> a;
            //
            //if it is a period, then switch to a one
            if(a == '.'){
                grid[i][j] = 0;
            }

            //account for newline just in case
            else if(a == '\n'){
                continue;
            }

            //else everthing else is a 1
            else{
                grid[i][j] = 1;
            }

        }
    }

    //delcare the vector to be pushed to the vector of vector
    vector<GridSquare> group;

    //nested for loops to cycle through the grid and push to the vector
    for(int i = 0; i < 10; ++i){
        for(int j = 0; j < 10; ++j){
            if(grid[i][j] == 1){
                groups.push_back(group);
                findGroup(i, j);
            }
        }
    }
}

//This funtion will take the row and colum postion and find the other
//postions that are apart of the group.
void Grouping::findGroup(int r, int c){

    //if the postion is 0 then exit the function
    if(grid[r][c] == 0){
        return;
    }

    //else preform the steps here
    else{
        //set to 0 to ensure proper poistion 
        grid[r][c] = 0;
        //push back to the vector
        groups.back().push_back(GridSquare(r, c));
        
        if(r + 1 < 10){
            findGroup((r + 1), c);
        }
        if (c + 1 < 10){
            findGroup(r, (c + 1));
        }
        if (r - 1 >= 0){
            findGroup((r - 1), c);
        }
        if (c - 1 >= 0){
            findGroup(r, (c - 1));
        }
    }
    


}



//Simple main function to test Grouping
//Be sure to comment out main() before submitting
// int main()
// {
//     Grouping input1("input1.txt");
//     input1.printGroups();
    
//     return 0;
// }

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}