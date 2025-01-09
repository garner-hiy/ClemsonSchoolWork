/*
 * Name: AJ Garner
 * Date Submitted: 3/11/23
 * Lab Section: 004
 * Assignment Name: Lab 6: Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/


//This function will calculate the distance between two points
double calcDist(point a, point b){
  double x1 = a.x;
  double y1 = a.y;
  double x2 = b.x;
  double y2 = b.y;

  //this is the formula for the distance
  return sqrt(pow((x1 - x2), 2.0) + pow((y1 - y2), 2.0));
}

//This function will iterate through the grid and find the
//closest distance between two points and does so by
//comparing one grid to all the grids around it.
double minDistance(vector<vector<vector<point>>> cellPoints, int gridSize){
  //this is the variable that will update with the min distance
  double min = 10.0;

//these for loops are used to iterate through the gird
  for(int xpos = 0; xpos < cellPoints.size(); xpos++){
    for(int ypos = 0; ypos < cellPoints.size(); ypos++){
      
      //these two vectors are used to store data
      vector <point> a = cellPoints[xpos][ypos];

      //this is the vector named neighbor of A and is used to compare 
      vector <point> nebOfA;

      //these three for loops are used to iterate through the grid squares around A
      //and they will store the date around A
      for(int i = -1; xpos + i >= 0 && xpos + i < gridSize && i <= 1; i++){
        for(int j = -1; ypos + j >= 0 && ypos + j < gridSize && j <= 1; j++){
          for(int l = 0; l < cellPoints[xpos+i][ypos+j].size(); l++){
            nebOfA.push_back(cellPoints[xpos+i][ypos+j][l]);
          }
        }
      }
      
      //these two for loops will iterate through the grid and elements for comparision 
      for(int i = 0; i < a.size(); i ++){
        for(int j = 0; j < nebOfA.size(); j++){

          //this if statement is used for the comparision
          if(a[i].x != nebOfA[j].x || a[i].y != nebOfA[j].y){

            //variable used for updating min
            double tempDis = calcDist(a[i], nebOfA[j]);
            if(tempDis < min){
              min = tempDis;
            }
          }
          
        }
  
      }
    }
  }
  return min;
}

//This function will take in a filename and open that file.
//It will then take everything from the file and store it 
//so that it can pass the information to minDistance to
//calculate the min distance between points and return that distance.
double closestPair(string filename){

  //used to open file
  ifstream input;
  input.open(filename);

  //checks that the file is open
  if(!input.is_open()){
    return -1;
  }
  string temp;
  getline(input, temp);

  //needed to get the size of the vector
  int gridSize = sqrt(stoi(temp));
  //rows//col//vector of structs
  vector<vector<vector<point>>> cellPoints(gridSize, vector<vector<point>>(gridSize));

  //this while loop is storing the data into the cellpoints vector
  while(!input.eof()){
    point tempPoint;
    input >> tempPoint.x;
    input >> tempPoint.y;
    int xpos = tempPoint.x * gridSize;
    int ypos = tempPoint.y * gridSize;
    cellPoints[xpos][ypos].push_back(tempPoint);
  }

  //close the file
  input.close();

  //call the function
  double mindis = minDistance(cellPoints, gridSize);
  return mindis;
}
