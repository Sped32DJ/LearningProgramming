#include <iostream>
using namespace std;

class Movie {
private:
  string rating; // no one can directly touch rating

public:
  string title;
  string director;
  /* string rating; */
  Movie(string aTitle, string aDirector, string aRating) {
    title = aTitle;
    director = aDirector;
    setRating(aRating);
  }

  void setRating(string aRating) { // to access rating, you must go through
                                   // setRating function :)
    if (aRating == "G" || aRating == "PG" || aRating == "PG-13" ||
        aRating == "R" || aRating == "NR") {
      rating = aRating;
    } else {
      rating = "NR";
    }
    /* string getRating() { return rating; } */
  }
  string getRating() { return rating; }
};

int main() {

  string ratings[]{"G", "PG", "PG-13", "R", "NR"}; // figure out how to use this

  Movie avengers("The Avengers", "Joss Whedon", ratings[2]);

  avengers.setRating("Dog");
  cout << avengers.getRating() << endl;

  return 0;
}
