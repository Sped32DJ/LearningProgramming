#include <iostream>
#include <string>

using namespace std;

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

class Playlist {
public:
  Playlist();
  Playlist(string SongName); // Parameterized constructor
  InsertAfter();
  SetNext();
  GetID() const;
  GetSongName() const;
  GetSongLength() const;
  GetArtistName() const;
  GetNext() const;
  PrintPlaylistNode();

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode *nextNodePtr;
}

#endif
