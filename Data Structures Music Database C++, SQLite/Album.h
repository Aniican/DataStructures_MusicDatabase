// Author: Lane Murray
// Date: 12/13/2021
#pragma once
#include <string>
using namespace std;

class Album
{
private:
	string bandName;
	string title;
	string genre;
	string format;
	int numTracks;
	int releaseYear;
	int timesListened;
	bool haveListened;
public:
	// Constructors
	Album();
	Album(string bandName, string title, string genre, string format, int numTracks, int releaseYear, int timesListened, bool haveListened);
	// Desutructos
	~Album();
	
	// Getters
	string getBandName();
	string getTitle();
	string getGenre();
	string getFormat();
	int getNumTracks();
	int getReleaseYear();
	int getTimesListened();
	bool getHaveListened();

	// Setters
	void updateTimesListened(int num);
};

