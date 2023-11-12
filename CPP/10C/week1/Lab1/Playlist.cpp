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

// copy constructor
Playlist::Playlist(const Playlist &cpy) : head(nullptr), tail(nullptr) {
  PlaylistNode *cpyNode = cpy.head;

  while (cpyNode) {
    PlaylistNode *newNode = new PlaylistNode(*cpyNode);

    if (!head) {
      head = newNode;
      tail = newNode;
    } else {
      tail->SetNext(newNode);
      tail = newNode;
    }

    cpyNode = cpyNode->GetNext();
  }
}

PlaylistNode::PlaylistNode(const PlaylistNode &cpy)
    : uniqueID(cpy.GetID()), songName(cpy.GetSongName()),
      artistName(cpy.GetArtistName()), songLength(cpy.GetSongLength()),
      nextNodePtr(nullptr) {}

PlaylistNode::~PlaylistNode() {}

Playlist::~Playlist() {
  PlaylistNode *curr = head;
  PlaylistNode *nextNode;

  while (curr) {
    nextNode = curr->GetNext();
    delete curr;
    curr = nextNode;
  }
  head = nullptr;
  tail = nullptr;
}

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

PlaylistNode &PlaylistNode::operator=(const PlaylistNode &cpy) {
  if (this != &cpy) {
    // Clear the current linked list
    PlaylistNode *curr = nextNodePtr;
    PlaylistNode *nextNode;
    while (curr) {
      nextNode = curr->GetNext();
      delete curr;
      curr = nextNode;
    }

    // Copy the linked list from cpy
    PlaylistNode *cpycurr = cpy.GetNext();
    PlaylistNode *currHead = nullptr;
    PlaylistNode *currTail = nullptr;

    // While copy still has nodes
    // it will keep copying
    while (cpycurr) {
      PlaylistNode *newNode = new PlaylistNode(*cpycurr);
      if (!currHead) {
        currHead = newNode;
        currTail = newNode;
      } else { // Once it reaches the tail, it sets a tail
        currTail->SetNext(newNode);
        currTail = newNode;
      }
      cpycurr = cpycurr->GetNext();
    }

    // Update the nextNodePtr for the current object
    nextNodePtr = currHead;
  }
  return *this;
}

void Playlist::PrintPlaylistNode() const {
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

  while (curr) { // prings one song at a time
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

bool Playlist::isEmpty() const { return !head; }

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

void Playlist::RemoveSong(string &targetID) {
  PlaylistNode *curr = head;
  PlaylistNode *prev = nullptr;
  string removedSong;

  while (curr) {
    if (curr->GetID() == targetID) { // Once targetID is found
      if (prev) {
        prev->SetNext(curr->GetNext()); // Links prev with curr->next

      } else {
        head = curr->GetNext(); // If curr was head
      }
      removedSong = curr->GetSongName();
      delete curr; // deletes curr (turns into null, while ends)
    }

    // Makes sure prev is follow curr
    prev = curr;
    curr = curr->GetNext();
  }

  // Prints out song just removed
  cout << '"' << removedSong << '"' << " removed." << endl;
}

void Playlist::SetNext() {
  string uniqueID, songName, artistName;
  int songLength;

  cin.ignore(); // fixes cin error

  cout << "Enter song's unique ID:" << endl;
  getline(cin, uniqueID);
  if (cin.bad()) {
    throw runtime_error("Bad input");
  }

  cout << "Enter song's name:" << endl;
  getline(cin, songName);
  if (cin.bad()) {
    throw runtime_error("Bad input");
  }

  cout << "Enter artist's name:" << endl;
  getline(cin, artistName);
  if (cin.bad()) {
    throw runtime_error("Bad input");
  }

  cout << "Enter song's length (in seconds):" << endl;
  cin >> songLength;
  if (cin.bad()) {
    throw runtime_error("Bad input");
  }

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

  // Keeps iterating until tail
  while (curr) {
    curr = curr->GetNext();
    ++songCap; // Checks how many songs are in the list
  }
  curr = head;

  if (pos == 1) {
    song->SetNext(head);
    head = song;
    if (!tail) { // If there is no tail, newnode is tail
      tail = song;
    }
  } else if (pos >= songCap) { // If pos is greater than amount of songs
    tail->SetNext(song);       // Just gets put into the tail
    tail = song;
  } else {
    while (songPos < pos) { // If pos is within the limits of playlist

      // song getting inserted
      prev = curr;
      curr = curr->GetNext();
      ++songPos;
    }
    // linking
    prev->SetNext(song);
    song->SetNext(curr);
  }
}
