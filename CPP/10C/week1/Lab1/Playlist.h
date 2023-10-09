#include <iostream>
#include <string>

using namespace std;

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

struct PlaylistNode {
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode *nextNodePtr;

  // Constructor
  PlaylistNode(string uniqueID, string songName, string artistName,
               int songLength, PlaylistNode *nextNodePtr)
      : uniqueID(uniqueID), songName(songName), artistName(artistName),
        songLength(songLength), nextNodePtr(nextNodePtr) {}

  string GetArtistName() const { return artistName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode *GetNext() const { return nextNodePtr; }
  string GetID() const { return uniqueID; }
  string GetSongName() const { return songName; }
  int GetLength() const { return songLength; }
};

class Playlist {
public:
  Playlist(string playlistTitle);
  Playlist(string artistName, string songName, string uniqueID,
           string playlistTitle); // Parameterized constructor

  void SetNext();

  void PrintPlaylistNode();
  void InsertSong(int pos, PlaylistNode *song);
  bool isEmpty();

  string GetID() const;
  void RemoveSong(string songID);
  void ChangePosition(int currPos, int newPos);
  void InsertAfter(string uniqueID, string songName, string artistName,
                   int songLength); // TODO
  string GetSongName() const;
  string GetPlaylistTitle() const;
  string GetArtistName() const;
  int GetSongLength() const;
  /* int GetSongPos() const; */
  PlaylistNode *GetNext() const;
  PlaylistNode *GetHead() const;

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;

  string playlistTitle;

  PlaylistNode *nextNodePtr;
  PlaylistNode *head;
  PlaylistNode *tail;
};

#endif
