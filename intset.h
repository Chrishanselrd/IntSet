#ifndef INTSET_H
#define INTSET_H
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------
// IntSet:  One IntSet object represents one mathematical set of non-negative
// integers (includes zero). One set keeps track of unique integers, whether
// integers are in the set or not.  Implement the internal representation as
// follows.
//
// Implementation and assumptions:
//   -- Represented as a bool array internally
//   -- When a unique number is inserted then the array with its index
//      becomes true
//   -- the size of the array should be bigger or the same as the number
//      inserted
//   -- assignment operators will only affect lhs

class IntSet
{
  // overloaded <<: prints the unique numbers
  friend ostream &operator<<(ostream &out, const IntSet &intset);

  // overloaded >>: takes ints as input and inserts them to the IntSet
  friend istream &operator>>(istream &in, IntSet &intset);

private:
  bool *arrayPtr; // array of unique numbers
  int size;       // size of array

public:
  // Constructors
  IntSet();                                                 // default
  IntSet(int num);                                          // 1 unique number
  IntSet(int num1, int num2);                               // 2 unique number
  IntSet(int num1, int num2, int num3);                     // 3 unique number
  IntSet(int num1, int num2, int num3, int num4);           // 4 unique number
  IntSet(int num1, int num2, int num3, int num4, int num5); // 5 unique number

  // Copy constructor
  IntSet(const IntSet &other);

  // Helper function
  void copy(const IntSet &other);

  // Destructor
  ~IntSet();

  // arithmetic operators
  IntSet operator+(const IntSet &other) const; // Union of two IntSet
  IntSet operator-(const IntSet &other) const; // Difference of two IntSet
  IntSet operator*(const IntSet &other) const; // Intersection of two IntSet

  // boolean comparison operators
  bool operator==(const IntSet &other) const; // Equality of two IntSet
  bool operator!=(const IntSet &other) const; // Inequality of two IntSet

  // assignment operator
  IntSet &operator=(const IntSet &other);  // Assignment
  IntSet &operator+=(const IntSet &other); // Union assignment
  IntSet &operator*=(const IntSet &other); // Intersection assignment
  IntSet &operator-=(const IntSet &other); // Difference assignment

  // inserts a unique value to the array at index num,
  // return whether successfully inserted
  bool insert(int num);

  // removes a unique value in the array at index num,
  // return whether successfully removed
  bool remove(int num);

  // checks if the array is empty,
  // return whether the array is empty or not
  bool isEmpty() const;

  // checks if the unique number is already in the set,
  // return whether the number is unique or not
  bool isInSet(int num) const;
};

#endif