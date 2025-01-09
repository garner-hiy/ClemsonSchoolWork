#include "artwork.h"
#include "artist.h"
#include <stdio.h>
#include <string.h>

Artwork InitArtwork(){//initializes all information
    Artwork artwork;
    strcpy(artwork.title, "None");
    artwork.yearCreated = 0;
    artwork.artist = InitArtist();
    return artwork;
}
Artwork SetArtwork(char* title, int yearCreated, Artist artist){
    Artwork artwork = InitArtwork();//initializes information
    strcpy(artwork.title, title);
    artwork.yearCreated = yearCreated;
    artwork.artist = artist;
    return artwork;
}
void GetTitle(char* title, Artwork artwork){
    strcpy(title, artwork.title);
}
int GetYearCreated(Artwork artwork){
    return artwork.yearCreated;
}
Artist GetArtist(Artwork artwork){
    return artwork.artist;
}
void PrintArtwork(Artwork artwork){
    PrintArtist(artwork.artist);
    printf("Title: %s, %d\n",artwork.title, artwork.yearCreated);
}