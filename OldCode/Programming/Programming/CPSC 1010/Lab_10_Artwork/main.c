#include <stdio.h>
#include <string.h>

#include "artist.h"
#include "artwork.h"

int main(void) {
	char title[20];
	char name[20];
	int birthYear;
	int deathYear;
	int yearCreated;

	fgets(name, 20, stdin);
	scanf("%d\n", &birthYear);
	scanf("%d\n", &deathYear);
	fgets(title, 20, stdin);
	scanf("%d", &yearCreated);

	//remove newline character after name and title
	strtok(name, "\n");
	strtok(title, "\n");

	Artist artist = SetArtist(name, birthYear, deathYear);
	Artwork artwork = SetArtwork(title, yearCreated, artist);

	PrintArtwork(artwork);

	return 0;
}