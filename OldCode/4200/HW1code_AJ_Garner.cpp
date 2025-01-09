#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

// Function to convert a string to lowercase
string toLower(const string &str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Comparator function for sorting by frequency
bool compare(const pair<string, int> &a, const pair<string, int> &b) {
    return a.second > b.second;
}

int main(void) {
    string inputFileName;
    cout << "Enter the input file name: ";
    cin >> inputFileName;

    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error opening file: " << inputFileName << endl;
        return 1;
    }

    string outputFileName = inputFileName.substr(0, inputFileName.find_last_of('.')) + "_output_results.txt";
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cerr << "Error creating output file: " << outputFileName << endl;
        return 1;
    }

    string text, line;

    while (getline(inputFile, line)) 
        text += toLower(line);
    

    map<string, int> singleCounts, bigramCounts, trigramCounts;

    for (size_t i = 0; i < text.size(); ++i) {
        if (isalpha(text[i])) {
            singleCounts[string(1, text[i])]++;

            if (i + 1 < text.size() && isalpha(text[i + 1])) {
                string bigram = text.substr(i, 2);

                if (bigram.find(' ') == string::npos) 
                    bigramCounts[bigram]++;
                
            }

            if (i + 2 < text.size() && isalpha(text[i + 2])) {
                string trigram = text.substr(i, 3);

                if (trigram.find(' ') == string::npos) 
                    trigramCounts[trigram]++;
                
            }
        }
    }

    // Function to sort and print counts
    auto printCounts = [&outputFile](const map<string, int> &counts, int limit) {
        vector<pair<string, int>> sortedCounts(counts.begin(), counts.end());
        sort(sortedCounts.begin(), sortedCounts.end(), compare);

        int count = 0;
        for (const auto &pair : sortedCounts) {

            if (count >= limit) break;
            outputFile << pair.first << ": " << pair.second << endl;
            count++;
        }
        
    };

    outputFile << "Single Letters Frequency:" << endl;
    printCounts(singleCounts, singleCounts.size());

    outputFile << "\nBigrams Frequency (Top 30):" << endl;
    printCounts(bigramCounts, 30);

    outputFile << "\nTrigrams Frequency (Top 30):" << endl;
    printCounts(trigramCounts, 30);

    inputFile.close();
    outputFile.close();

    cout << "Output written to " << outputFileName << endl;

    return 0;
}