#include "Playlist.h"
#include <iostream>
#include <string>

using namespace std;

void DisplayMenu(string playlistTitle);

int main() {
  string playlistTitle;
  char option;

  cout << "Enter playlist's title:" << endl;
  getline(cin, playlistTitle);
  if (cin.fail()) {
    throw runtime_error("Not a string");
  }

  Playlist Songs(playlistTitle);

  cin >> option;
  if (cin.fail()) {
    throw runtime_error("option input failed");
  }

  if (option == 'q') {
    DisplayMenu(playlistTitle);
  }

  while (option != 'q') { // q for quit
    if (option == 'a') {  // Add song
      cout << "ADD SONG" << endl;
      Songs.SetNext();

    } else if (option == 'd') { // remove song
      string songID;
      cout << "REMOVE SONG" << endl << "Enter song's unique ID:" << endl;
      cin >> songID;
      if (cin.fail()) {
        throw runtime_error("Not a songID");
      }

      Songs.RemoveSong(songID);

    } else if (option == 'c') { // Change position of song
      int currPos, newPos;
      cout << "CHANGE POSITION OF SONG" << endl;
      cout << "Enter song's current position:" << endl;
      cin >> currPos;
      if (cin.fail()) {
        throw runtime_error("Bad current position input");
      }

      cout << "Enter new position for song:" << endl;
      cin >> newPos;
      if (cin.fail()) {
        throw runtime_error("Bad new position input");
      }

      Songs.ChangePosition(currPos, newPos);

    } else if (option == 's') { // Print Artist Song Names
      string artist;

      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      cout << "Enter artist's name:" << endl;
      getline(cin >> ws, artist); // >> ws fixed bug
      if (cin.fail()) {
        throw runtime_error("bad artist name input");
      }
      cout << endl;

      Songs.PrintArtistSongs(artist);

    } else if (option == 't') { // Output total time of playlist
      size_t length = 0;
      cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl
           << "Total time: ";

      PlaylistNode *curr = Songs.GetHead();
      while (curr) {
        length += curr->GetLength();
        curr = curr->GetNext();
      }

      cout << length << " seconds" << endl;

    } else if (option == 'o') { // Output full playlist
      Songs.PrintPlaylistNode();
    } else {
      cout << "Invalid option" << endl;
      cout << "Try again: " << endl;
    }

    // Shows menu and prompts -> while()
    DisplayMenu(playlistTitle);
    cin >> option;
    if (cin.fail()) {
      throw runtime_error("Invalid option");
    }
  }

  return 0;
}

void DisplayMenu(string playlistTitle) {
  cout << endl
       << playlistTitle << " PLAYLIST MENU" << endl
       << "a - Add song" << endl
       << "d - Remove song" << endl
       << "c - Change position of song" << endl
       << "s - Output songs by specific artist" << endl
       << "t - Output total time of playlist (in seconds)" << endl
       << "o - Output full playlist" << endl
       << "q - Quit" << endl
       << endl
       << "Choose an option:" << endl;
}
