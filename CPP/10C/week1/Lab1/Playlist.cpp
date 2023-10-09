#include "Playlist.h"
#include <iostream>
using namespace std;

Playlist::Playlist(string artistName, string songName, string uniqueID,
                   string playlistTitle)
    : uniqueID(uniqueID), songName(songName), artistName(artistName),
      songLength(0), playlistTitle(playlistTitle), nextNodePtr(nullptr),
      head(nullptr), tail(nullptr) {}

Playlist::Playlist(string playlistTitle)
    : uniqueID("none"), songName("none"), artistName("none"), songLength(0),
      playlistTitle(playlistTitle), nextNodePtr(nullptr), head(nullptr),
      tail(nullptr) {}

// Accessor Functions

string Playlist::GetID() const { return uniqueID; }
string Playlist::GetSongName() const { return songName; }
string Playlist::GetArtistName() const { return artistName; }
string Playlist::GetPlaylistTitle() const { return playlistTitle; }
int Playlist::GetSongLength() const { return songLength; }
/* Playlist *Playlist::GetNext() const { return head; } */

/* int Playlist::GetSongPos() const {
  int songPos;
  while (GetNext()) {
  }
} */

void Playlist::ChangePosition(int currPos, int newPos) {
  if (currPos == newPos || currPos < 1 || newPos < 1) {
    return;
  }

  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;
  PlaylistNode *target = nullptr;

  int songPos = 1;

  // Find currPos
  // no way this is efficient :sob:
  while (curr && songPos != currPos) {
    prev = curr;
    curr = curr->nextNodePtr;
    ++songPos;
  }

  if (curr && songPos == currPos) {
    target = curr;
    if (prev) {
      prev->nextNodePtr = curr->nextNodePtr;
    } else {
      head = curr->nextNodePtr;
    }
  } else {
    cout << "Failed pos" << endl;
    return;
  }

  // Find new pos
  curr = head;
  prev = nullptr;
  while (curr && songPos != newPos) {
    prev = curr;
    curr = curr->nextNodePtr;
    ++songPos;
  }

  // Insert node to new pos
  if (curr) {
    target->nextNodePtr = curr;
    if (prev) {
      prev->nextNodePtr = target;
    } else {
      head = target;
    }
  } else {
    tail->nextNodePtr = target;
    tail = target;
  }
  cout << '"' << target->GetSongName() << '"' << " moved to position " << newPos
       << endl;
}

void Playlist::RemoveSong(string songID) {
  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;
  string removedSong;

  while (curr) {
    if (curr->uniqueID == songID) {
      if (prev) {
        prev->nextNodePtr = curr->nextNodePtr;
      } else {
        head = curr->nextNodePtr;
      }
      removedSong = curr->songName;
      delete curr;
    }

    prev = curr;
    curr = curr->nextNodePtr;
  }
  cout << '"' << removedSong << '"' << " removed" << endl;
}

void Playlist::SetNext() {
  string uniqueID, songName, artistName;
  int songLength;

  cout << "Enter song's unique ID:" << endl;
  cin >> uniqueID;
  cin.ignore();

  cout << "Enter song's name:" << endl;
  cin.ignore();
  getline(cin, songName);

  cout << "Enter Artist's name:" << endl;
  getline(cin, artistName);

  cout << "Enter song's length (in seconds):" << endl;
  cin >> songLength;

  PlaylistNode *newSong =
      new PlaylistNode(uniqueID, songName, artistName, songLength, nullptr);

  if (tail) {
    tail->nextNodePtr = newSong;
  }

  tail = newSong;
}

void Playlist::InsertSong(int pos, PlaylistNode *song) {
  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;
  int songPos = 1;
  int songCap = 1;

  while (curr) {
    curr = curr->nextNodePtr;
    ++songCap;
  }
  curr = head;

  if (pos == 1) {
    song->nextNodePtr = head;
    head = song;
    if (!tail) {
      tail = song;
    }
  } else if (pos >= songCap) {
    tail->nextNodePtr = song;
    tail = song;
  } else {
    while (songPos < pos) {
      prev = curr;
      curr = curr->nextNodePtr;
      ++songPos;
    }
    prev->nextNodePtr = song;
    song->nextNodePtr = curr;
  }
}

PlaylistNode *Playlist::GetNext() const { return nextNodePtr; }
PlaylistNode *Playlist::GetHead() const { return head; }

void Playlist::PrintPlaylistNode() {
  cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;

  if (!isEmpty()) {
    cout << "Playlist is empty" << endl;
  } else if (head == nullptr) {
    cout << "Playlist is empty" << endl;
  } else {
    PlaylistNode *curr = head;
    size_t songPos = 0;

    while (curr != nullptr) {
      ++songPos;
      cout << songPos << '.' << endl;
      cout << "Unique ID: " << curr->uniqueID << endl
           << "Song Name: " << curr->songName << endl
           << "Artist Name: " << curr->artistName << endl
           << "Song Length (in seconds): " << curr->songLength << endl
           << endl;
      curr = curr->nextNodePtr;
    }
  }
}

bool Playlist::isEmpty() { return head == nullptr; }
