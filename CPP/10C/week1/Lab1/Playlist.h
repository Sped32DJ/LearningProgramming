#include <iostream>
#include <string>

using namespace std;

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

class PlaylistNode {
public:
  // Parameterized const | provides default vals
  // NOTE  This shouldn't be inline
  PlaylistNode(string uniqueID = "none", string songName = "none",
               string artistName = "none", int songLength = 0)
      : uniqueID(uniqueID), songName(songName), artistName(artistName),
        songLength(songLength) {}
  ~PlaylistNode();                                // TODO
  Playlist(const Playlist &title) = delete;       // TODO
  Playlist &operator=(const Playlist &) = delete; // TODO

  string GetArtistName() const { return artistName; }
  int GetSongLength() const { return songLength; }
  PlaylistNode *GetNext() const { return nextNodePtr; }
  string GetID() const { return uniqueID; }
  string GetSongName() const { return songName; }
  int GetLength() const { return songLength; }

  void InsertAfter(PlaylistNode *temp);

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

  void SetNext();

  void PrintPlaylistNode();
  void InsertSong(int pos, PlaylistNode *song);
  bool isEmpty();
  void PrintArtistSongs(string name);

  string GetID() const;
  void RemoveSong(string songID);
  void Playlist::RemoveSong(string songID) {
    PlaylistNode *curr = head;
    PlaylistNode *prev = nullptr;
    string removedSong;

    while (curr) {
      if (curr->GetID() == songID) {
        if (prev) {
          prev->SetNext(curr->GetNext());

        } else {
          head = curr->GetNext();
        }
        removedSong = curr->GetSongName();
        delete curr;
      }

      prev = curr;
      curr = curr->GetNext();
    }
    cout << '"' << removedSong << '"' << " removed." << endl;
  }

  void ChangePosition(int currPos, int newPos);
  void InsertAfter(PlaylistNode *);
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
