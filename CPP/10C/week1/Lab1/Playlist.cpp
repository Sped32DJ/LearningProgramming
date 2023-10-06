#include "Playlist.h"
#include <iostream>

Playlist::Playlist() {
  uniqueID = 0;
  songName = "none";
  artistName = "none";
  songLength = 0;
  nextNodePtr = nullptr;
}

Playlist::Playlist(string artistName, string songName)
    : artistName(artistName), songName(songName) {}

// Accessor Functions

Playlist::InsertAfter() {} // TODO
Playlist::SetNext() {}     // TODO
Playlist::GetID() const { return uniqueID; }
Playlist::GetSongName() const { return songName; }
Playlist::GetSongLength() const { return songLength; }
Playlist::GetArtistName() const { return artistName; }

Playlist::GetNext() const { return Playlist->next; } // TODO

Playlist::PrintPlaylistNode() {
  cout << "Unique ID: " << GetID() << endl
       << "Song Name: " << GetSongName << endl
       << "Artist Name: " << GetArtistName() << endl
       << "Song Length (in seconds): " << GetSongLength() << endl;
}
