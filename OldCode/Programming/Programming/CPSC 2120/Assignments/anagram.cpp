/*
 * Name: AJ Garner
 * Date Submitted: 3/7/2023
 * Assignment Name: Single-Word Anagram Finder
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

vector<string> loadWordlist(string filename);

/*Implement the following function:
  anagram() takes a word (string) and a wordlist of all words (vector of strings)
  and builds a dictionary/map where the key is a specific number of times each
  letter occurs in a word and the associated value is a vector of strings
  containing all words using those letters (anagrams).
  The value returned is a vector of strings containing the corresponding
  set of anagrams
*/
vector<string> anagram(string word, vector<string> wordlist);

// int main()
// {
//     vector<string> words;
//     vector<string> anagrams;
//     string inputWord;
//     words=loadWordlist("wordlist.txt");
//     cout << "Find single-word anagrams for the following word: ";
//     cin >> inputWord;
//     anagrams = anagram(inputWord, words);
//     for (int i=0; i<anagrams.size(); i++)
//     {
//         cout << anagrams[i] << endl;
//     }
//     return 0;
// }

vector<string> loadWordlist(string filename)
{
    vector<string> words;
    ifstream inFile;
    string word;
    inFile.open(filename);
    if(inFile.is_open())
    {
        while(getline(inFile,word))
        {
            if(word.length() > 0)
            {
                words.push_back(word);
            }
        }
        inFile.close();
    }
    return words;
}

//Implement this function
vector<string> anagram(string word, vector<string> wordlist)
{
    vector<string> temp;
    vector<string> temp2;
    vector<string> anagrams;
    sort(word.begin(), word.end());
    for(int i = 0; i < wordlist.size(); i++){
        if(wordlist[i].size() == word.size()){
            temp.push_back(wordlist[i]);
            temp2.push_back(wordlist[i]);
        }
    }
    for(int i = 0; i < temp.size(); i++){
        sort(temp[i].begin(), temp[i].end());
        if(word == temp[i]){
            anagrams.push_back(temp2[i]);
        }
    }
    return anagrams;
}