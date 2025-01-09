/*
 * Name: AJ Garner
 * Date Submitted: 3/31/2023
 * Lab Section: 004
 * Assignment Name: Lab 9: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

//This is one of the helper functions that will cheack
//if a queen can be place at a position or not,
//then it will return a true of false
bool checkForPlace(int** board, int n, int col, int row)
{
    //this for loop will be used to check the row
    for(int i = 0; i < n; i++){
        if(board[row][i] == 1){
            return false;
        }
    }
    int j;
    //this loop is used for the diagonal on the upper left side
    //for(int i = row, j = col; j >= 0 && i >= 0; j--, i--){
    for(int i = row-1, j = col-1; j >= 0 && i >= 0; j--, i--){
        if(board[i][j] == 1){
            return false;
        }
    }
    //This loop is used for the diagonal on the lower left side
    //for(int i = row, j = col; i < n && j >= 0; j--, i++){
    for(int i = row+1, j = col-1; i < n && j >= 0; j--, i++){
        if(board[i][j] == 1){
            return false;
        }
    }
    //if all conditions are met return true
    return true;
}

//This is another helper function that will use recursion to
//determine if where the queens are placed will result in a
//solved board.
int solve(int ** board, int n, int col)
{
    //create the row and the count variable used to return to nQueens function
    int row;
    int count = 0;
    
   if(col == n)
    //if(col <= n)
    {
        return 1;
        
    } 
    
    if(col < n)
    {
    //This for loop will do the recursion 
    for(int i = 0; i < n; i++)
        {
            row = i;

            //if a queen can be placed, then execute 
            if(checkForPlace(board, n, col, row) == true)
            {
                board[row][col] = 1; 
                count = count + solve(board, n, col + 1);
                board[row][col] = 0; 
            }
        }
        
        //return count;
    }

     return count;
}

//This is the main function that will handle creating the board
//it will then return the number of possible solutions 
//by calling the helper functions
int nQueens(int n){

    //the board is being created here and in the for loop
    //board is a pointer of pointer, which should be generated like this.
    int ** board = new int*[n];
    for (int i = 0; i < n; ++i)
        board[i] = new int[n];
    
    for(int i = 0; i < n; i++)
    {
        board[i];
        for(int j = 0; j < n; j++)
        {
            board[i][j] = 0;
        }
    }
    //answer is the variable used to store the count returned by the helper
    int answer = solve(board, n, 0);
    //Release the memory after new
    delete[] board;
    //finally return the number of possible solutions 
    return answer;
}

// int main()
// {
//     cout << "1: " << nQueens(1) << endl;
//     cout << "2: " << nQueens(2) << endl;
//     cout << "3: " << nQueens(3) << endl;
//     cout << "4: " << nQueens(4) << endl;
//     cout << "5: " << nQueens(5) << endl;
//     cout << "6: " << nQueens(6) << endl;
//     cout << "7: " << nQueens(7) << endl;
//     cout << "8: " << nQueens(8) << endl;
//     cout << "9: " << nQueens(9) << endl;
//     cout << "10: " << nQueens(10) << endl;
//     cout << "11: " << nQueens(11) << endl;
//     cout << "12: " << nQueens(12) << endl;
//     return 0;
// }