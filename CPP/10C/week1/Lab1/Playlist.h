#include <iostream>
#include <string>

using namespace std;

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

class PlaylistNode {
public:
  // Parameterized const | provides default vals
  PlaylistNode(string uniqueID = "none", string songName = "none",
               string artistName = "none", int songLength = 0)
      : uniqueID(uniqueID), songName(songName), artistName(artistName),
        songLength(songLength) {}
  PlaylistNode(const PlaylistNode &);
  ~PlaylistNode();

  string GetArtistName() const { return artistName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode *GetNext() const { return nextNodePtr; }
  string GetID() const { return uniqueID; }
  string GetSongName() const { return songName; }
  int GetLength() const { return songLength; }

  void InsertAfter(PlaylistNode *temp);

  PlaylistNode &operator=(const PlaylistNode &cpy);

  void SetNext(PlaylistNode *song) { nextNodePtr = song; }
  void PrintPlaylistNode() const;

private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode *nextNodePtr = nullptr;
};

class Playlist {
public:
  Playlist(string playlistTitle);
  Playlist(string artistName, string songName, string uniqueID,
           string playlistTitle); // Parameterized constructor
  Playlist(const Playlist &);
  ~Playlist();

  void SetNext();
  void InsertSong(int pos, PlaylistNode *song);
  void PrintArtistSongs(string name);

  void RemoveSong(string &songID);

  void ChangePosition(int currPos, int newPos);
  void InsertAfter(PlaylistNode *);

  void PrintPlaylistNode() const;
  string GetID() const;
  bool isEmpty() const;
  string GetSongName() const;
  string GetPlaylistTitle() const;
  string GetArtistName() const;
  int GetSongLength() const;
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
