#ifndef ARTIST_H
#define ARTIST_H

typedef struct ArtistStuct_struct{//struct for artist information
    char name[20];//artist name
    int birthYear;//year born
    int deathYear;//year of death
}Artist;
//below are the prototypes for the fuctions in artist.c
Artist InitArtist();
Artist SetArtist(char* name, int birthYear, int deathYear);
void GetName(char* name, Artist artist);
int GetBirthYear(Artist artist);
int GetDeathYear(Artist artist);
void PrintArtist(Artist artist);

#endif