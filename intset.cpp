#include "intset.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

//----------------------------------------------------------------------------
// operator<<
// overloaded <<: prints a set of unique numbers
ostream &operator<<(ostream &out, const IntSet &intset)
{
  if (!intset.arrayPtr || intset.size < 0)
  {
    out << "{}";
    return out;
  }

  out << "{";
  for (int i = 0; i < intset.size; i++)
  {
    if (intset.arrayPtr[i])
    {
      out << " " << i;
    }
  }
  out << "}";
  return out;
}

//----------------------------------------------------------------------------
// operator>>
// overloaded >>: takes in a set of unique numbers
istream &operator>>(istream &in, IntSet &set)
{
  int num;
  in >> num;
  while (num >= 0)
  {
    set.insert(num);
    in >> num;
  }
  return in;
}

//----------------------------------------------------------------------------
// copy
// makes an exact copy of the parameter
void IntSet::copy(const IntSet &other)
{
  size = other.size;
  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = other.arrayPtr[i];
  }
}

//----------------------------------------------------------------------------
// copy constructor
// constructs a copy of the object
IntSet::IntSet(const IntSet &other)
{
  copy(other);
}

//----------------------------------------------------------------------------
// insert
// insert a unique number
bool IntSet::insert(int num)
{
  if (num > size)
  {
    IntSet tmp(*this);
    delete[] arrayPtr;
    size = num + 1;
    arrayPtr = new bool[size]();
    for (int i = 0; i < tmp.size; i++)
    {
      arrayPtr[i] = tmp.arrayPtr[i];
    }
  }

  arrayPtr[num] = true;
  return true;
}

//----------------------------------------------------------------------------
// remove
// removes a unique number
bool IntSet::remove(int num)
{
  if (num > size)
  {
    return false;
  }
  arrayPtr[num] = false;
  return true;
}

//----------------------------------------------------------------------------
// isEmpty
// checks if the set is empty
bool IntSet::isEmpty() const
{
  if (size == 0 && arrayPtr[0] == false)
  {
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------
// isInSet
// checks if unique number is in set
bool IntSet::isInSet(int num) const
{
  if (num > size || num < size)
  {
    return false;
  }
  if (arrayPtr[num])
  {
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------
// deafult constructor
// make a set with size 1 and has the value of false
IntSet::IntSet()
{
  this->arrayPtr = new bool[1]();
  this->arrayPtr[0] = false;
  size = 0;
}

//----------------------------------------------------------------------------
// constructor with 1 variable
// make a set with size of the parameter and has the value of true
IntSet::IntSet(int num)
{
  size = num + 1;
  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = false;
  }
  this->insert(num);
}

//----------------------------------------------------------------------------
// constructor with 2 variable
// make a set with biggest size of the parameter
IntSet::IntSet(int num1, int num2)
{
  size = max(num1, num2) + 1;
  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = false;
  }

  this->insert(num1);
  this->insert(num2);
}

//----------------------------------------------------------------------------
// constructor with 3 variable
// make a set with biggest size of the parameter
IntSet::IntSet(int num1, int num2, int num3)
{
  size = num1;
  if (num2 > size)
  {
    size = num2;
  }
  if (num3 > size)
  {
    size = num3;
  }
  size++;

  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = false;
  }

  this->insert(num1);
  this->insert(num2);
  this->insert(num3);
}

//----------------------------------------------------------------------------
// constructor with 4 variable
// make a set with biggest size of the parameter
IntSet::IntSet(int num1, int num2, int num3, int num4)
{
  size = num1;
  if (num2 > size)
  {
    size = num2;
  }
  if (num3 > size)
  {
    size = num3;
  }
  if (num4 > size)
  {
    size = num4;
  }
  size++;

  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = false;
  }

  this->insert(num1);
  this->insert(num2);
  this->insert(num3);
  this->insert(num4);
}

//----------------------------------------------------------------------------
// constructor with 5 variable
// make a set with biggest size of the parameter
IntSet::IntSet(int num1, int num2, int num3, int num4, int num5)
{
  size = num1;
  if (num2 > size)
  {
    size = num2;
  }
  if (num3 > size)
  {
    size = num3;
  }
  if (num4 > size)
  {
    size = num4;
  }
  if (num5 > size)
  {
    size = num5;
  }
  size++;

  arrayPtr = new bool[size];

  for (int i = 0; i < size; i++)
  {
    arrayPtr[i] = false;
  }

  this->insert(num1);
  this->insert(num2);
  this->insert(num3);
  this->insert(num4);
  this->insert(num5);
}

//----------------------------------------------------------------------------
// destructor
// deletes the array and sets the pointer to nullptr
IntSet::~IntSet()
{
  delete[] arrayPtr;
  arrayPtr = nullptr;
}

//----------------------------------------------------------------------------
// operator=
// overloaded =: assigns an object
IntSet &IntSet::operator=(const IntSet &other)
{
  if (&other != this)
  {
    delete[] arrayPtr;
    copy(other);
  }
  return *this;
}

//----------------------------------------------------------------------------
// operator+
// overloaded +: Union of 2 sets, current object and parameter
IntSet IntSet::operator+(const IntSet &other) const
{
  int largest = max(size, other.size);

  IntSet finalSet(largest - 1);

  // loops through this set
  for (int i = 0; i < this->size; i++)
  {
    if (arrayPtr[i] == true)
    {
      finalSet.arrayPtr[i] = true;
    }
  }

  // loops through other set
  for (int i = 0; i < other.size; i++)
  {
    if (other.arrayPtr[i] == true)
    {
      finalSet.arrayPtr[i] = true;
    }
  }

  return finalSet;
}

//----------------------------------------------------------------------------
// operator*
// overloaded -: Intersection of 2 Sets, current object and parameter
IntSet IntSet::operator*(const IntSet &other) const
{
  int smallest = min(size, other.size);

  IntSet finalSet(smallest - 1);

  for (int i = 0; i < size; i++)
  {
    if (arrayPtr[i] == true && other.arrayPtr[i] == true)
    {
      finalSet.arrayPtr[i] = true;
    }
    else
    {
      finalSet.arrayPtr[i] = false;
    }
  }

  return finalSet;
}

//----------------------------------------------------------------------------
// operator-
// overloaded -: Difference of 2 Sets, current object and parameter
IntSet IntSet::operator-(const IntSet &other) const
{
  IntSet finalAns(size - 1);

  for (int i = 0; i < size; i++)
  {
    finalAns.arrayPtr[i] = arrayPtr[i];
  }

  int minSize = min(size, other.size);
  for (int i = 0; i < minSize; i++)
  {
    if (finalAns.arrayPtr[i] == true && other.arrayPtr[i] == true)
    {
      finalAns.arrayPtr[i] = false;
    }
    else if (finalAns.arrayPtr[i] == true && other.arrayPtr[i] == false)
    {
      finalAns.arrayPtr[i] = true;
    }
  }

  return finalAns;
}

//----------------------------------------------------------------------------
// operator+=
// overloaded +=: current object = current object + parameter
IntSet &IntSet::operator+=(const IntSet &other)
{
  for (int i = 0; i < other.size; i++)
  {
    if (other.arrayPtr[i] == true)
    {
      this->insert(i);
    }
  }
  return *this;
}

//----------------------------------------------------------------------------
// operator*=
// overloaded *=: current object = current object * parameter
IntSet &IntSet::operator*=(const IntSet &other)
{
  int smallest = min(size, other.size);

  for (int i = 0; i < smallest; i++)
  {
    if (arrayPtr[i] == true && other.arrayPtr[i] == true)
    {
      arrayPtr[i] = true;
    }
    else
    {
      arrayPtr[i] = false;
    }
  }

  return *this;
}

//----------------------------------------------------------------------------
// operator-=
// overloaded -=: current object = current object - parameter
IntSet &IntSet::operator-=(const IntSet &other)
{
  for (int i = 0; i < size; i++)
  {
    if (arrayPtr[i] == true && other.arrayPtr[i] == true)
    {
      arrayPtr[i] = false;
    }
    else if (arrayPtr[i] == true && other.arrayPtr[i] == false)
    {
      arrayPtr[i] = true;
    }
    else
    {
      arrayPtr[i] = false;
    }
  }
  return *this;
}

//----------------------------------------------------------------------------
// operator==
// overloaded ==: current object = parameter
bool IntSet::operator==(const IntSet &other) const
{
  if (size != other.size)
  {
    return false;
  }

  for (int i = 0; i < size; i++)
    if (arrayPtr[i] != other.arrayPtr[i])
    {
      return false;
    }
  return true;
}

//----------------------------------------------------------------------------
// operator!=
// overloaded !=: current object != parameter
bool IntSet::operator!=(const IntSet &other) const
{
  return !(*this == other);
}
