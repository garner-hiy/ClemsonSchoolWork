/*
 * Name:AJ Garner
 * Date Submitted:2/20/2023
 * Lab Section: 004
 * Assignment Name:Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>

/*This linear search function will compare each element
one by one and return the index, or -1 if it could not
find the target.*/
template <class T>
int linearSearch(std::vector<T> data, T target){
    //used to base case the for loop
    int comp = data.capacity();
    //loop until the vector lenght is reached
    for(auto i = 0; i < comp; ++i){
        //if found return the index
        if(data[i] == target){
            return i;
        }
    }
    return -1;
}

/*This binary search will split the vector in half and 
will keep doing so until it finds the target index.
It will return that index or -1 if it could not find it.*/
template <class T>
int binarySearch(std::vector<T> data, T target){
    //index for start of the vector
    int lowIndex = 0;
    //lenght of the vector for end index
    int highIndex = data.size() - 1;
    //will hold middle index
    int midIndex;
    //keep looping until base case is reached
    while (highIndex - lowIndex > 1){
        //each loop, midIndex will update
        midIndex = (highIndex + lowIndex) / 2;
        if(data[midIndex] < target)
            lowIndex = midIndex + 1;
        else
            highIndex = midIndex;        
    }
    //the final set of compares
    if(data[lowIndex] == target)
        return lowIndex;
    else if(data[highIndex] == target)
        return highIndex;
    else    
        return -1;    
}
