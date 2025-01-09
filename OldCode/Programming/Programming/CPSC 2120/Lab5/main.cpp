/*
* Name:AJ Garner
* Date Submitted:2/20/2023
* Lab Section: 004
* Assignment Name:Lab 4: Searching and Sorting
*/

#include "stringset.h"
#include <iostream>
#include <fstream>

void testStringset(Stringset& words);
void loadStringset(Stringset& words, string filename);
vector<string> spellcheck(const Stringset& words, string word);


void testStringset(Stringset& words)
{
    string choice;
    string word;
    do
    {
        cout << "I: insert word" << endl;
        cout << "F: find word" << endl;
        cout << "R: remove word" << endl;
        cout << "P: print words in stringset" << endl;
        cout << "Q: quit" << endl;
        cin >> choice;
        switch (choice[0])
        {
            case 'I':
            case 'i':
              cout << "Enter word to insert: ";
              cin >> word;
              words.insert(word);
              break;
            case 'F':
            case 'f':
              cout << "Enter word to find: ";
              cin >> word;
              if (words.find(word))
              {
                  cout << word << " in stringset" << endl;
              }
              else
              {
                  cout << word << " not in stringset" << endl;
              }
              break;
            case 'R':
            case 'r':
              cout << "Enter word to remove: ";
              cin >> word;
              words.remove(word);
              break;
            case 'P':
            case 'p':
              vector<list<string>> t = words.getTable();
              int numWords = words.getNumElems();
              int tSize = words.getSize();
              for(int i=0; i<tSize; ++i)
              {
                  list<string>::iterator pos;
                  for (pos = t[i].begin(); pos != t[i].end(); ++pos)
                  {
                      cout << *pos << endl;
                  }
              }
              cout << "Words: " << numWords << endl;
        }
    } while (choice[0] != 'Q' && choice[0] != 'q');
}

//This will load the string into the class object of Stringset.
//It reads in a file and uses getline to read into the hash table.
void loadStringset(Stringset& words, string filename){

  ifstream input(filename);
  string word;

  while(getline(input, word)) {
    words.insert(word);
  }
}

//This function will take the given word and return a 
//vector of all the words in the stringset that are one 
//letter away from the word.
//A word is considered one letter away if you can 
//change one letter at any position within the word to 
//create another word.
vector<string> spellcheck(const Stringset& words, string word){
  vector<string> altWords;

  for (int i = 0; i < word.length(); i++) {
    for (char c = 'a'; c < 'z' + 1; c++) {
      string tempWord = word;
      // all alternatives of word, which is one position different from word
      // check letter c is not word[i]
      if (c != word[i]){
        tempWord[i] = c;
        // check if tempWord is in words or not 
        if (words.find(tempWord)){
          altWords.push_back(tempWord);
        }
      }
    }
  }
  return altWords;
}