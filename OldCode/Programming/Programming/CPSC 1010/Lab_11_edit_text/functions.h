#ifndef FUNCTIONS_H
#define FUNCTIONS_H
 //only need the prototypes of the functions
void PrintMenu();
void ExecuteMenu(char userChar, char* ptrstring);
int GetChars(char* ptrstring);
int GetWords(char* ptrstring);
void FixCapitals(char* ptrstring);
void ReplaceExclamation(char* ptrstring);
void ShortenSpaces(char* ptrstring);

#endif