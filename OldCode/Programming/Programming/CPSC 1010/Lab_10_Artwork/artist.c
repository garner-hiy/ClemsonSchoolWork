#include "artist.h"
#include <stdio.h>
#include <string.h>

Artist InitArtist(){//initializes all information
    Artist artist;
    strcpy(artist.name, "None");
    artist.birthYear = 0;
    artist.deathYear = 0;
    return artist;
}
Artist SetArtist(char* name, int birthYear, int deathYear){
    Artist artist = InitArtist();//initializes the data first
    strcpy(artist.name, name);
    artist.birthYear = birthYear;
    artist.deathYear = deathYear;
    return artist;
}
void GetName(char* name, Artist artist){
    strcpy(name, artist.name);
}
int GetBirthYear(Artist artist){
    return artist.birthYear;
}
int GetDeathYear(Artist artist){
    return artist.deathYear;
}
void PrintArtist(Artist artist){//need if else statement for if they are died or not
    if(artist.deathYear < 0){
        printf("Artist: %s, born %d\n", artist.name, artist.birthYear);
    }
    else{
        printf("Artist: %s (%d-%d)\n", artist.name, artist.birthYear, artist.deathYear);
    }
}