/*
 * Name:AJ Garner
 * Date Submitted:2/20/2023
 * Lab Section: 004
 * Assignment Name:Lab 4: Searching and Sorting
 */

#include "stringset.h"

Stringset::Stringset() : table(4), num_elems(0), size(4) {}

//Used in test cases and testStringset() in main.cpp, do not modify
vector<list<string>> Stringset::getTable() const
{
    return table;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getNumElems() const
{
    return num_elems;
}

//Used in test cases and testStringset() in main.cpp, do not modify
int Stringset::getSize() const
{
    return size;
}

//This function will take in a string and add it 
//to the hash table. It will first check that the word
//doesn't already exsist by using the find member function.
//Next it will iterate through the table and find the index
//that has already been hashed at the beginning.
void Stringset::insert(string word){
    unsigned int j = 0;
    string tempWord;

    //this is used to find the hash vlaue
    std::hash<string> stringHash;

    //this will stop the function and not add the word 
    //if it returns true
    if (find(word)) {return;}

    //this will double the size of the table if the 
    //number of elements equal the size of the table.
    //It will also rehash all the words to a new place.
    if (num_elems == size) {
        size *= 2;
        std::vector<list<string>> tempTable(size);
        for (int i = 0; i < size / 2; i++) {
            for (list<string>::const_iterator iter = table[i].begin(); iter != table[i].end(); iter++) {
                tempWord = *iter;
                j = stringHash(tempWord) % size;
                tempTable[j].push_back(tempWord);
                table[i].remove(word);
            }
        }

    table = tempTable;
    }

    //this will has the word and push it to the proper place
    //it then iterates the number of elements
    j = stringHash(word) % size;
    table[j].push_back(word);
    num_elems++;
}

//This function will search the table and return true if the word
//already exsists. It will return false if the word is not found.
bool Stringset::find(string word) const{

    //need to hash the word before searching 
    hash<string> stringHash;
    unsigned int i = stringHash(word) % size;

    for (auto iter : table[i]) {
        if (iter == word) {return true;}
    }
    return false;
}

//This will remove the word from the table if the find function
//returns true. It will also count the number of elements down by one.
void Stringset::remove(string word){
    //if the word is not found, then we don't need to remove it
    if (!find(word)) {return;}
    
    hash<string> stringHash;
    unsigned int i = stringHash(word) % size;
    
    //word is removed from stringset
    table[i].remove(word); 
    num_elems--;
}