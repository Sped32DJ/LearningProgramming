#include "HashTable.h"
#include "WordEntry.h"
#include <cstdlib>
#include <fstream>
#include <iostream>

/* HashTable constructor
 *  input s is the size of the array
 *  set s to be size
 *  initialize array of lists of WordEntry
 */

HashTable::HashTable(int s) {
  size = s;
  hashTable = new list<WordEntry>[size]; // Array of linked lists
}

HashTable::HashTable(const HashTable &cpy) {
  size = cpy.size;
  hashTable = new list<WordEntry>[size];

  for (int i = 0; i < size; ++i) {
    hashTable[i] = cpy.hashTable[i];
  }
}

HashTable::~HashTable() {
  delete[] hashTable;
  hashTable = nullptr;
}

/* computeHash
 *  return an integer based on the input string
 *  used for index into the array in hash table
 *  be sure to use the size of the array to
 *  ensure array index doesn't go out of bounds
 */
int HashTable::computeHash(const string &s) {
  int val = 0;
  for (size_t i = 0; i < s.size(); ++i) {
    val += s.at(i); // EZ hash
  }
  return val % size; // module hashtable size
}

/* put
 *  input: string word and int score to be inserted
 *  First, look to see if word already exists in hash table
 *   if so, addNewAppearence with the score to the WordEntry
 *   if not, create a new Entry and push it on the list at the
 *   appropriate array index
 */
void HashTable::put(const string &s, int score) {
  int hashVal = computeHash(s);
  if (hashVal < size) {
    auto &bucket = hashTable[hashVal]; // Jumps into the bucket

    // Loops until bucket ends
    for (auto i = bucket.begin(); i != bucket.end(); ++i) {
      if (i->getWord() == s) {
        i->addNewAppearance(score); // Adds ++dupes & += score
        return;
      }
    }

    WordEntry newWord = WordEntry(s, score); // Declaring new Word Object
    bucket.push_front(newWord); // Inserts newWord object into bucket
  }
}

/* getAverage
 *  input: string word
 *  output: the result of a call to getAverage()
 *          from the WordEntry
 *  Must first find the WordEntry in the hash table
 *  then return the average
 *  If not found, return the value 2.0 (neutral result)
 */

double HashTable::getAverage(const string &s) {
  int hashVal = computeHash(s);
  if (hashVal < size) {
    /* throw runtime_error("Out of bounds"); */
  }

  auto &bucket = hashTable[hashVal];
  for (auto i = bucket.begin(); i != bucket.end(); ++i) {
    if (i->getWord() == s) {
      return i->getAverage(); // Calls the object's getAverage()
    }
  }

  return 2.0; // Couldn't find word, neutral result
}

/* contains
 * input: string word
 * output: true if word is in the hash table
 *         false if word is not in the hash table
 */
bool HashTable::contains(const string &s) {
  int hashVal = computeHash(s);
  if (hashVal < size) {
    /* throw runtime_error("Out of bounds"); */
  }

  auto &bucket = hashTable[hashVal];

  for (auto i = bucket.begin(); i != bucket.end(); ++i) {
    if (i->getWord() == s) {
      return true; // True if word is found
    }
  }

  return false; // iterated through whole list, couldn't find
}
void HashTable::resize(int newSize) {
  // Creates array with new size
  list<WordEntry> *newTable = new list<WordEntry>[newSize];

  // Rehash all existing vals
  for (int i = 0; i < size; ++i) {
    for (auto j = hashTable[i].begin(); j != hashTable[i].end(); ++j) {
      int hashVal = computeHash(j->getWord());
      newTable[hashVal].push_front(*j);
    }
  }

  // Delete old array
  delete[] hashTable;

  // Update size and table pointer to new
  hashTable = newTable;
  size = newSize;
}

int main() {
  // declare a few needed variables for inputing the data
  string line;
  int score;
  string message = " ";

  // open input file
  ifstream myfile("movieReviews.txt");
  if (myfile.fail()) {
    cout << "could not open file" << endl;
    exit(1);
  }

  // create hash table
  HashTable table(20071);

  while (!myfile.eof()) {
    myfile >> score; // get score
    myfile.get();    // get blank space
    getline(myfile, line);
    int len = line.size();
    while (len > 0) { // identify all individual strings
      string sub;
      len = line.find(" ");
      if (len > 0) {
        sub = line.substr(0, len);
        line = line.substr(len + 1, line.size());
      } else {
        sub = line.substr(0, line.size() - 1);
      }
      table.put(sub, score); // insert string with the score
    }
  }

  // after data is entered in hash function
  // prompt user for a new movie review
  while (message.length() > 0) {
    cout << "enter a review -- Press return to exit: " << endl;
    getline(cin, message);

    // used for calculating the average
    double sum = 0;
    int count = 0;

    double sentiment = 0.0;

    size_t len = message.size();
    // get each individual word from the input
    while (len != string::npos) {
      string sub;
      len = message.find(" ");
      if (len != string::npos) {
        sub = message.substr(0, len);
        message = message.substr(len + 1, message.size());
      } else {
        sub = message;
      }
      // calculate the score of each word
      sum += table.getAverage(sub);
      ++count;
    }

    if (message.size() > 0) {
      sentiment = sum / count;
      cout << "The review has an average value of " << sentiment << endl;
      if (sentiment >= 3.0) {
        cout << "Positive Sentiment" << endl;
      } else if (sentiment >= 2.0) {
        cout << "Somewhat Positive Sentiment" << endl;
      } else if (sentiment >= 1.0) {
        cout << "Somewhat Negative Sentiment" << endl;
      } else {
        cout << "Negative Sentiment" << endl;
      }
      cout << endl;
    }
  }

  return 0;
}
