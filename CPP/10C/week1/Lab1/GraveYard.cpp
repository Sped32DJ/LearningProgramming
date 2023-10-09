void Playlist::PrintArtistSongs(string name) { // FIXME  EXTRA ENDL
  int pos = 1;
  PlaylistNode *curr = head;

  // I know this increase O(N), jank, ignore this, I slept at 5am
  // Temp solution
  size_t cap = 0;
  size_t artSongs = 0;
  while (curr) {
    if (curr->GetArtistName() == name) {
      ++cap;
    }
    curr = curr->GetNext();
  }

  // Iterate the list, prints artist specific songs
  while (curr) {
    if (curr->GetArtistName() == name) {
      cout << pos << '.' << endl;
      if (artSongs + 1 == cap) {   // Temp solution, of maybe (cap )
        curr->PrintPlaylistNode(); // Only Prints that song node
        cout << "test: " << artSongs << " WITH ENDL";
      } else {
        cout << "Unique ID: " << curr->GetID() << endl
             << "Song Name: " << curr->GetSongName() << endl
             << "Artist Name: " << curr->GetArtistName() << endl
             << "Song Length (in seconds): TESTING NO ENDL"
             << curr->GetSongLength(); // No endl here!!
      }
      ++artSongs;
      ++pos;
      curr = curr->GetNext();
    }
  }
}

