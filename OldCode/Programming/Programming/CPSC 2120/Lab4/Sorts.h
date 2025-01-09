/*
 * Name:AJ Garner
 * Date Submitted:2/20/2023
 * Lab Section: 004
 * Assignment Name:Lab 4: Searching and Sorting
 */

#pragma once

#include <vector>

//prototypes needed 
template <class T>
std::vector<T> mergeSort(std::vector<T> &lst);
template <class T>
std::vector<T> merge(std::vector<T> &lst, const std::vector<T> &left, const std::vector<T> &right);
template <class T>
std::vector<T> quickSort(std::vector<T> lst);
template <class T>
void Quick(std::vector<T> &lst, int low, int high);


/*merge is the helper function for mergeSort. It will
compare values and push them to a tempoary vector. Once
everthing is sorted, it will return the vector back to 
mergeSort.*/
template <class T>
std::vector<T> merge(std::vector<T> &lst, const std::vector<T> &left,
 const std::vector<T> &right){
    //temp vector needed to push sorted values to
    std::vector<T> temp;

    //these have to be unsigned so it will properly compare
    unsigned int i = 0;
    unsigned int j = 0;

    //loop while the sizes of the vectors are less
    while(i < left.size() && j < right.size()){

        //if left vector is less than right vector index,
        //then it will push that value to temp
        if (left[i] < right[j]){
            temp.push_back(left[i]);
            i++;
        }
        //else it will push the other value to temp
        else{
            temp.push_back(right[j]);
            j++;
        }
    }
    //these two while loops are needed for the last
    //few indexes if there are any left
    while(i < left.size()){
        temp.push_back(left[i]);
        i++;
    }

    while(j < right.size()){
        temp.push_back(right[j]);
        j++;
    }

    return temp;
}

/*mergeSort will take in a vector and break the vector up.
It will call itself to do this and at the return, it will
call the helper function and return the value.*/
template <class T>
std::vector<T> mergeSort(std::vector<T> &lst){
    //this is to check that the vector has something in it
    if(lst.size() == 1){
        return lst;
    }

    //this iterator type is needed for the mid point
    typename std::vector<T>::iterator mid = lst.begin() + (lst.size() / 2);

    //these are the left and right vectors needed to break down the vectors
    std::vector<T> left(lst.begin(), mid);
    std::vector<T> right(mid, lst.end());    

    //this is where the recurstion occurs
    left = mergeSort(left);
    right = mergeSort(right);

    //this will return the vector that the helper function
    //will assemble 
    return merge(lst, left, right);
}

template <class T>
void Quick(std::vector<T> &lst, int low, int high){
    //set the iterators for the function to what is passed in
    int i = low;
    int j = high;
    //mid is needed to find the pivot index
    int mid = low + ((high - low) / 2);
    //this will create the pivot 
    T pivot = lst[mid];

    //this will keep looping until either of these are true
    while(i < high || j > low){
        //while the index is less then pivot, no need to swap
        //just keep going
        while(lst[i] < pivot){
            i++;
        }
        //while the index is greater then pivot, no need to swap
        //just keep going
        while(lst[j] > pivot){
            j--;
        }
        //this is used to compare and swap
        if(i <= j){
            //this is a standard library function to swap elements
            std::swap(lst[i], lst[j]);
            i++;
            j--;
        }
        //if it doesnt pass the if, then based on the case
        //it will call itself
        else{
            if(j > low){
                Quick(lst, low, j);
            }
            if(i < high){
                Quick(lst, i, high);
            }
            //when everthing is sorted correctly
            //this will end the helper function
            return;
        }
    } 
}

/*quickSort will take in a vector and create the 
indexes needed to pass to the helper fuction. 
The helper function will do most of the work.*/
template <class T>
std::vector<T> quickSort(std::vector<T> lst){
    //the end of the vector
    int high = lst.size() - 1;
    //used to mark the beginning of the vector
    int low = 0;
    //call to helper function
    Quick(lst, low, high);
    //return the resulting vector
    return lst;
}

/* std::vector<T> leftList = mergesort(std::vector<T>
(lst.begin()), (lst.begin + midpos)); */
