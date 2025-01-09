#ifndef ARTWORK_H
#define ARTWORK_H
#include "artist.h"

typedef struct ArtworkStruct_struct{
    char title[20]; 
    int yearCreated;
    Artist artist;
}Artwork;
//below are the prototypes for the fuctions in artwork.c
Artwork InitArtwork();
Artwork SetArtwork(char* title, int yearCreated, Artist artist);
void GetTitle(char* title, Artwork artwork);
int GetYearCreated(Artwork artwork);
Artist GetArtist(Artwork artwork);
void PrintArtwork(Artwork artwork);

#endif