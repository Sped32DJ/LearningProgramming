#include "Playlist.h"
#include <iostream>
using namespace std;

// Constructors
Playlist::Playlist(string artistName, string songName, string uniqueID,
                   string playlistTitle)
    : uniqueID(uniqueID), songName(songName), artistName(artistName),
      songLength(0), playlistTitle(playlistTitle), nextNodePtr(nullptr),
      head(nullptr), tail(nullptr) {}

Playlist::Playlist(string playlistTitle)
    : uniqueID("none"), songName("none"), artistName("none"), songLength(0),
      playlistTitle(playlistTitle), nextNodePtr(nullptr), head(nullptr),
      tail(nullptr) {}

// Write a copy constructor
// TODO  Use delete in the code, somewhere
Playlist::Playlist(const Playlist &title) {}

Playlist::~Playlist() {}

// Accessor Functions
string Playlist::GetID() const { return uniqueID; }
string Playlist::GetSongName() const { return songName; }
string Playlist::GetArtistName() const { return artistName; }
string Playlist::GetPlaylistTitle() const { return playlistTitle; }
int Playlist::GetSongLength() const { return songLength; }
PlaylistNode *Playlist::GetNext() const { return nextNodePtr; }
PlaylistNode *Playlist::GetHead() const { return head; }

// Visual Functions
void PlaylistNode::PrintPlaylistNode() const {
  cout << "Unique ID: " << GetID() << endl
       << "Song Name: " << GetSongName() << endl
       << "Artist Name: " << GetArtistName() << endl
       << "Song Length (in seconds): " << GetSongLength() << endl;
}

void Playlist::PrintPlaylistNode() {
  cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;

  if (isEmpty()) {
    cout << "Playlist is empty" << endl;
    return;

  } else {
    PlaylistNode *curr = head;
    size_t songPos = 1;

    while (curr) {
      cout << songPos << '.' << endl;
      curr->PrintPlaylistNode();
      if (curr->GetNext()) // All but last get an endl
        cout << endl;

      curr = curr->GetNext();
      ++songPos;
    }
  }
}

void Playlist::PrintArtistSongs(string name) {
  int pos = 1;
  int nodeCount = 0;
  int CurrCount = 1;
  PlaylistNode *curr = head;

  // Iterate the list, prints artist specific songs
  while (curr) {
    if (curr->GetArtistName() == name) {
      ++nodeCount;
    }
    curr = curr->GetNext();
  }

  // Reinitialize
  curr = head;

  while (curr) {
    if (curr->GetArtistName() == name) {
      cout << pos << '.' << endl;
      curr->PrintPlaylistNode();
      if (nodeCount > CurrCount) {
        cout << endl;
      }
      ++CurrCount;
    }
    ++pos;
    curr = curr->GetNext();
  }
}

bool Playlist::isEmpty() { return !head; }

// Functions that modify linked list
void PlaylistNode::InsertAfter(PlaylistNode *song) {
  PlaylistNode *temp = nextNodePtr;
  nextNodePtr = song;
  nextNodePtr->SetNext(temp);
}

void Playlist::ChangePosition(int currPos, int newPos) {
  if (currPos == newPos || currPos < 1 || newPos < 1) {
    return;
  }
  int initIndex = 1;

  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;

  // Points the pointers
  while (initIndex < currPos) {
    if (curr) {
      prev = curr;
      curr = curr->GetNext();
      ++initIndex;
      if (!curr) {
        return;
      }
    } else {
      return;
    }
  }

  // NOTE  Logic begins to start shifting nodes
  string songName = curr->GetSongName();

  if (!prev) { // If curr is head
    head = curr->GetNext();
  } else {
    prev->SetNext(curr->GetNext());
  }

  if (!curr->GetNext()) { // If curr is tail
    tail = prev;
  }

  // If moved to head
  if (newPos <= 1) {
    if (isEmpty()) {
      tail = curr;
    }
    curr->SetNext(head);
    head = curr;
    cout << '"' << songName << '"' << " moved to position 1" << endl;
  } else { // Any shifting that does not include head or tail
    initIndex = 2;

    // Used to stich curr between prev1 and post
    PlaylistNode *prev1;
    PlaylistNode *post;
    prev1 = head;
    post = head->GetNext();

    // Iterates until it reaches target position
    while (post && initIndex < newPos) {
      prev1 = post;
      post = post->GetNext();
      ++initIndex;
    }

    // Curr inserted between two nodes
    prev1->SetNext(curr);
    curr->SetNext(post);

    // If while loop exited in the while(post)
    if (!post) {
      tail = curr;
    }

    cout << '"' << songName << '"' << " moved to position " << initIndex
         << endl;
  }
}

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

void Playlist::SetNext() {
  string uniqueID, songName, artistName;
  int songLength;

  cin.ignore();

  cout << "Enter song's unique ID:" << endl;
  getline(cin, uniqueID);

  cout << "Enter song's name:" << endl;
  getline(cin, songName);

  cout << "Enter artist's name:" << endl;
  getline(cin, artistName);

  cout << "Enter song's length (in seconds):" << endl;
  cin >> songLength;

  PlaylistNode *newSong =
      new PlaylistNode(uniqueID, songName, artistName, songLength);

  if (tail != nullptr) {
    tail->SetNext(newSong);
  }
  if (head == nullptr) {
    head = newSong;
  }

  tail = newSong;
}

void Playlist::InsertSong(int pos, PlaylistNode *song) {
  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;
  int songPos = 1;
  int songCap = 1;

  while (curr) {
    curr = curr->GetNext();
    ++songCap;
  }
  curr = head;

  if (pos == 1) {
    song->SetNext(head);
    head = song;
    if (!tail) {
      tail = song;
    }
  } else if (pos >= songCap) {
    tail->SetNext(song);
    tail = song;
  } else {
    while (songPos < pos) {
      prev = curr;
      curr = curr->GetNext();
      ++songPos;
    }
    prev->SetNext(song);
    song->SetNext(curr);
  }
}
