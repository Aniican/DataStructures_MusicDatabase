// Author: Lane Murray
// Date: 12/13/2021
#include <string>
#include "Album.h"

using namespace std;
// Constructors
Album::Album()
{
	this->bandName = " ";
	this->title = " ";
	this->genre = " ";
	this->format = " ";
	this->numTracks = 0;
	this->releaseYear = 0;
	this->timesListened = 0;
	this->haveListened = false;
}

Album::Album(string bandName, string title, string genre, string format, int numTracks, int releaseYear, int timesListened, bool haveListened)
{
	this->bandName = bandName;
	this->title = title;
	this->genre = genre;
	this->format = format;
	this->numTracks = numTracks;
	this->releaseYear = releaseYear;
	this->haveListened = haveListened;

	if (haveListened)
		this->timesListened = timesListened;
	else
		this->timesListened = 0;
}

// Desutructos
Album::~Album() {}

// Getters
string Album::getBandName() { return this->bandName; }
string Album::getTitle() { return this->title; }
string Album::getGenre() { return this->genre; }
string Album::getFormat() { return this->format; }
int Album::getNumTracks() { return this->numTracks; }
int Album::getReleaseYear() { return this->releaseYear; }
int Album::getTimesListened() { return this->timesListened; }
bool Album::getHaveListened() { return this->haveListened; }

// Setters
void Album::updateTimesListened(int num) { this->timesListened = num; }