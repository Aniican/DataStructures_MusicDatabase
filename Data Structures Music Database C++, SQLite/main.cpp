// Author: Lane Murray
// Date: 12/13/2021

#include "Album.h"
#include "queue.h"
#include "stack.h"
#include "sqlite3.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <climits>
/*
	Album table layout:
		Album_ID INTEGER,
		Title VARCHAR(255),
		Band_Name VARCHAR(255),
		Genre VARCHAR(255),
		Format VARCHAR(255),
		Num_Tracks INTEGER,
		Release_Year INTEGER,
		Times_Listened INTEGER,
		Have_Listened BOOLEAN;
*/

using namespace std;

void insertAlbum(sqlite3* db, Album newAlbum);
void viewAlbums(sqlite3* db);
void viewArtistsAlbums(sqlite3* db, string artist);
void viewAlbumsFormat(sqlite3* db, string format);
void viewAlbumsForDeletion(sqlite3* db);
void deleteAlbum(sqlite3* db, int albumID);

int main()
{
	sqlite3* Music_DB;

	linkedQueue<Album> newAlbumQueue; // Queue for adding new albums.
	stack<int> deleteAlbumStack; // Stack for deleting albums.

	bool isDone = false, isDoneAdding = false, isDoneDeleting = false, haveListened = false;
	int choice, mainMenuChoice, choiceInternal, numTracks, releaseYear, timesListened;
	string artist, title, genre, format;
	

	int rc = sqlite3_open_v2("Music_DB.db", &Music_DB, SQLITE_OPEN_READWRITE, NULL);
	if (rc != SQLITE_OK)
	{
		//if the database cannot be opened
		cout << "Error in connection: " << sqlite3_errmsg(Music_DB);
		return 1;
	}

	do
	{
		cout << "Welcome to the Music Database." << endl;
		cout << "What would you like to do?\n 1. View Albums\n 2. Add Albums\n 3. Delete Albums\n 4. Exit" << endl;
		cin >> mainMenuChoice;

		while (!cin || mainMenuChoice > 4 || mainMenuChoice < 1)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Error... That is not a valid choice." << endl;
			cout << "What would you like to do?\n 1. View Albums\n 2. Add Albums\n 3. Delete Albums\n 4. Exit" << endl;
			cin >> mainMenuChoice;
		}

		switch (mainMenuChoice)
		{
		case 1: // View Albums
			cout << "View Albums Menu." << endl;
			cout << "What would you like to do?\n 1. View All Albums\n 2. View An Arist/Bands Albums\n 3. View All Album of a Format\n 4. Return to Main Menu" << endl;
			cin >> choice;

			while (!cin || choice > 4 || choice < 1)
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Error... That is not a valid choice." << endl;
				cout << "What would you like to do?\n 1. View All Albums\n 2. View An Arist/Bands Albums\n 3. View All Album of a Format\n 4. Return to Main Menu" << endl;
				cin >> choice;
			}

			cin.clear();
			cin.ignore(INT_MAX, '\n');

			switch (choice)
			{
			case 1: viewAlbums(Music_DB); break; // View All Albums
			case 2: // View An Arist/Bands Albums
				cout << "What Arist/Bands albums would you like to view?" << endl;
				getline(cin, artist);
				viewArtistsAlbums(Music_DB, artist);
				break;
			case 3: // View All Album of a Format
				cout << "What Format would you like to view?\n 1. CD\n 2. Vinyl\n 3. Cassette\n 4. Digital\n 5. Return to Main Menu" << endl;
				cin >> choiceInternal;
				while (!cin || choiceInternal > 5 || choiceInternal < 1)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "What Format would you like to view?\n 1. CD\n 2. Vinyl\n 3. Cassette\n 4. Digital\n 5. Return to Main Menu" << endl;
					cin >> choiceInternal;
				}

				switch (choiceInternal)
				{
				case 1: viewAlbumsFormat(Music_DB, "CD"); break; // View CD
				case 2: viewAlbumsFormat(Music_DB, "Vinyl"); break; // View Vinyl
				case 3: viewAlbumsFormat(Music_DB, "Cassette"); break; // View Cassette
				case 4: viewAlbumsFormat(Music_DB, "Digital"); break; // View Digital
				case 5: break; // Return to Main Menu
				default: cout << "Error... invalid data." << endl; break;
				}

				break;
			case 4: break; // Return to Main Menu
			default: cout << "Error... invalid data." << endl; break;
			}
			break;
		case 2: // Add Albums
			cout << "Add Albums." << endl;
			do
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');

				cout << "Enter the album name: " << endl;
				getline(cin, title);
				cout << "Enter the artist/band name: " << endl;
				getline(cin, artist);
				cout << "Enter the genre: " << endl;
				getline(cin, genre);
				cout << "Enter the Number of Tracks: " << endl;
				cin >> numTracks;
				while (!cin || numTracks < 0)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "Enter the Number of Tracks: " << endl;
					cin >> numTracks;
				}
				cout << "Enter the Release Year: " << endl;
				cin >> releaseYear;
				while (!cin || releaseYear < 0)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "Enter the Release Year: " << endl;
					cin >> releaseYear;
				}
				cout << "Enter the Times You have Listened: " << endl;
				cin >> timesListened;
				while (!cin || timesListened < 0)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "Enter the Times You have Listened: " << endl;
					cin >> timesListened;
				}
				if (timesListened > 0)
					haveListened = true;
				else
					haveListened = false;

				cout << "What Format is this album?\n 1. CD\n 2. Vinyl\n 3. Cassette\n 4. Digital" << endl;
				cin >> choiceInternal;
				while (!cin || choiceInternal > 4 || choiceInternal < 1)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "What Format is this album?\n 1. CD\n 2. Vinyl\n 3. Cassette\n 4. Digital" << endl;
					cin >> choiceInternal;
				}

				switch (choiceInternal) // What Format is this album?
				{
				case 1: format = "CD"; break; // Format CD
				case 2: format = "Vinyl"; break; // Format Vinyl
				case 3: format = "Cassette"; break; // Format Cassette
				case 4: format = "Digital"; break; // Format Digital
				default: cout << "Error... invalid data." << endl; break;
				}

				newAlbumQueue.enqueue(Album(artist, title, genre, format, numTracks, releaseYear, timesListened, haveListened)); // Adds the new album to a queue.

				cout << "Would you like to add another album?\n 1. Yes\n 2. No" << endl;
				cin >> choice;
				while (!cin || choice > 2 || choice < 1)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "Would you like to add another album?\n 1. Yes\n 2. No" << endl;
					cin >> choice;
				}
				
				if (choice == 1)
					isDoneAdding = false;
				else
					isDoneAdding = true;

			} while (!isDoneAdding);

			while (!newAlbumQueue.isEmptyQueue()) // Adds all albums in the queue to the database.
			{
				insertAlbum(Music_DB, newAlbumQueue.front());
				newAlbumQueue.dequeue();
			}

			break;
		case 3: // Delete Albums
			cout << "Delete Albums." << endl;
			do
			{
				viewAlbumsForDeletion(Music_DB); // Outputs all albums in the database.
				cout << "Enter the album ID for an album you want to delete (or -1 to exit): " << endl;
				cin >> choice;
				while (!cin || choice == 0 || choice < -1)
				{
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					cout << "Error... That is not a valid choice." << endl;
					cout << "Enter the Album ID for an album you want to delete (or -1 to exit): " << endl;
					cin >> choice;
				}

				if (choice == -1)
					isDoneDeleting = true;
				else
				{
					isDoneDeleting = false;
					deleteAlbumStack.push(choice); // Adds the ID of an album to the stack.
				}

			} while (!isDoneDeleting);

			while (!deleteAlbumStack.isEmpty()) // Deletes all albums (based on album ID).
			{
				deleteAlbum(Music_DB, deleteAlbumStack.top());
				deleteAlbumStack.pop();
			}
			break;
		case 4: isDone = true; break; // Exit
		default: cout << "Error... Exiting program." << endl; isDone = true; break;
		}

	} while (!isDone);

	sqlite3_close(Music_DB);
	return 0;
}

void insertAlbum(sqlite3* db, Album newAlbum) // Inserts new data into the Album Table.
{
	char* messageError;
	string errStr;
	int rc = sqlite3_exec(db, "begin transaction", NULL, NULL, &messageError); // Start of transaction
	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		cout << "There was an error: " << messageError << endl;
		sqlite3_free(messageError);
		return;
	}

	string sqlQuery = "INSERT INTO ALBUM (Title, Band_Name, Genre, Format, Num_Tracks, Release_Year, Times_Listened, Have_Listened) "; // Query for adding new Albums to the database.
	sqlQuery += "VALUES ('" + newAlbum.getTitle() + "', '" + newAlbum.getBandName() + "', '" + newAlbum.getGenre() + "', '" + newAlbum.getFormat() + "', ";
	sqlQuery += to_string(newAlbum.getNumTracks()) + ", " + to_string(newAlbum.getReleaseYear()) + ", " + to_string(newAlbum.getTimesListened());
	sqlQuery += ", " + to_string(newAlbum.getHaveListened()) + ");";

	int rc2 = sqlite3_exec(db, sqlQuery.c_str(), NULL, NULL, &messageError);

	if (rc2 != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}
	else
		sqlite3_exec(db, "commit", NULL, NULL, NULL); // End of transaction
}

void viewAlbums(sqlite3* db) // Displays all albums in the database.
{
	string errStr;
	sqlite3_stmt* result;

	string sqlQuery = "SELECT * FROM ALBUM;"; // Query for viewing all albums in the database.

	int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &result, NULL);

	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		sqlite3_finalize(result);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}

	while (sqlite3_step(result) == SQLITE_ROW)  
	{
		
		cout << "-------------------------------------" << endl;
		cout << "Album Title: " << sqlite3_column_text(result, 1) << endl;
		cout << "Artist/Band Name: " << sqlite3_column_text(result, 2) << endl;
		cout << "Genre: " << sqlite3_column_text(result, 3) << endl;
		cout << "Format: " << sqlite3_column_text(result, 4) << endl;
		cout << "Number of Tracks: " << sqlite3_column_text(result, 5) << endl;
		cout << "Release Year: " << sqlite3_column_text(result, 6) << endl;
		cout << "Times Listened: " << sqlite3_column_text(result, 7) << endl;
		cout << "Has Listened: " << sqlite3_column_text(result, 8) << endl;
		cout << "-------------------------------------" << endl;
	}
}

void viewArtistsAlbums(sqlite3* db, string artist) // Displays all albums of a specific band in the database.
{
	string errStr;
	sqlite3_stmt* result;

	string sqlQuery = "SELECT * FROM ALBUM WHERE Band_Name = '" + artist + "';"; // Query for all albums of a specific band in the database.

	int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &result, NULL);

	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		sqlite3_finalize(result);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}

	while (sqlite3_step(result) == SQLITE_ROW)
	{

		cout << "-------------------------------------" << endl;
		cout << "Album Title: " << sqlite3_column_text(result, 1) << endl;
		cout << "Artist/Band Name: " << sqlite3_column_text(result, 2) << endl;
		cout << "Genre: " << sqlite3_column_text(result, 3) << endl;
		cout << "Format: " << sqlite3_column_text(result, 4) << endl;
		cout << "Number of Tracks: " << sqlite3_column_text(result, 5) << endl;
		cout << "Release Year: " << sqlite3_column_text(result, 6) << endl;
		cout << "Times Listened: " << sqlite3_column_text(result, 7) << endl;
		cout << "Has Listened: " << sqlite3_column_text(result, 8) << endl;
		cout << "-------------------------------------" << endl;
	}
}

void viewAlbumsFormat(sqlite3* db, string format) // Displays all albums of a specific format in the database.
{
	string errStr;
	sqlite3_stmt* result;

	string sqlQuery = "SELECT * FROM ALBUM WHERE Format = '" + format + "';"; // Query for all albums of a specific format in the database.

	int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &result, NULL);

	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		sqlite3_finalize(result);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}

	while (sqlite3_step(result) == SQLITE_ROW) 
	{
		cout << "-------------------------------------" << endl;
		cout << "Album Title: " << sqlite3_column_text(result, 1) << endl;
		cout << "Artist/Band Name: " << sqlite3_column_text(result, 2) << endl;
		cout << "Genre: " << sqlite3_column_text(result, 3) << endl;
		cout << "Format: " << sqlite3_column_text(result, 4) << endl;
		cout << "Number of Tracks: " << sqlite3_column_text(result, 5) << endl;
		cout << "Release Year: " << sqlite3_column_text(result, 6) << endl;
		cout << "Times Listened: " << sqlite3_column_text(result, 7) << endl;
		cout << "Has Listened: " << sqlite3_column_text(result, 8) << endl;
		cout << "-------------------------------------" << endl;
	}
}

void viewAlbumsForDeletion(sqlite3* db) // The same as viewAlbums(), but the information outputted is reduced.
{
	string errStr;
	sqlite3_stmt* result;

	string sqlQuery = "SELECT * FROM ALBUM;"; // Query for viewing all albums in the database.

	int rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &result, NULL);

	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		sqlite3_finalize(result);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}

	while (sqlite3_step(result) == SQLITE_ROW)
	{
		cout << "-------------------------------------" << endl;
		cout << "Album ID: " << sqlite3_column_text(result, 0) << endl;
		cout << "Album Title: " << sqlite3_column_text(result, 1) << endl;
		cout << "Artist/Band Name: " << sqlite3_column_text(result, 2) << endl;
		cout << "-------------------------------------" << endl;
	}
}

void deleteAlbum(sqlite3* db, int albumID) // Deletes data in the Album Table. Then updates the Album Table to have corrected ID's.
{
	char* messageError;
	string errStr, albumMax;
	sqlite3_stmt* result;
	int AlbumMaxInt = 0, index = 0;

	int rc = sqlite3_exec(db, "begin transaction", NULL, NULL, &messageError); // Start of transaction
	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		cout << "There was an error: " << messageError << endl;
		sqlite3_free(messageError);
		return;
	}

	string sqlQuery = "SELECT * FROM ALBUM;"; // Query to grab all Albums. 
	rc = sqlite3_prepare_v2(db, sqlQuery.c_str(), -1, &result, NULL);
	if (rc != SQLITE_OK) // If the SQLITE isn't okay
	{
		cout << "There was an error: " << messageError << endl;
		sqlite3_free(messageError);
		return;
	}

	while (sqlite3_step(result) == SQLITE_ROW) // Loop determines the size of the Album table.
	{
		albumMax = reinterpret_cast<const char*>(sqlite3_column_text(result, 0));
		int temp = stoi(albumMax, nullptr, 10);

		if (AlbumMaxInt < temp)
			AlbumMaxInt = temp;
	}

	string sqlQuery2 = "DELETE FROM ALBUM WHERE Album_ID = " + to_string(albumID) + ";"; // Query to delete an Album.
	int rc2 = sqlite3_exec(db, sqlQuery2.c_str(), NULL, NULL, &messageError);
	if (rc2 != SQLITE_OK) // If the SQLITE isn't okay
	{
		errStr = sqlite3_errmsg(db);
		sqlite3_finalize(result);
		cout << "There was an error: " << errStr << endl;
		sqlite3_exec(db, "rollback", NULL, NULL, NULL);
		return;
	}
	else
		sqlite3_finalize(result);

	index = albumID;

	while (index <= AlbumMaxInt) // Loop to update Album ID's after and album has been removed.
	{
		string sqlQuery3 = "UPDATE ALBUM SET Album_ID = " + to_string(index) + " WHERE Album_ID = " + to_string(index + 1) + ";"; // Query for updating the Albums ID's.

		int rc3 = sqlite3_exec(db, sqlQuery3.c_str(), NULL, NULL, &messageError);
		if (rc3 != SQLITE_OK) // If the SQLITE isn't okay
		{
			errStr = sqlite3_errmsg(db);
			sqlite3_finalize(result);
			cout << "There was an error: " << errStr << endl;
			sqlite3_exec(db, "rollback", NULL, NULL, NULL);
			return;
		}

		index++;
	}

	sqlite3_exec(db, "commit", NULL, NULL, NULL); // End of transaction
}