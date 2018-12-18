

#ifndef VECTOR_H
#define VECTOR_H


#include <memory>
#include <stdexcept>


/****
* THINGS TO REMEMBER:
*
*                       RAII
*   Resource aquisition (or allocation) is intailization
*
*  std::unique_ptr -> https://en.cppreference.com/w/cpp/memory/unique_ptr
*
****/

/****
*          To Optimize/Refactor
* TODO: change all loop copys to std::copy()
* TODO: Add iterators
* TODO: add move constructor
* TODO:  ...
*
****/


template <typename T>
class Vector {
public:
  Vector();
  Vector(int capacity);
  Vector(const Vector<T> &rightSide);

  Vector& operator =(const Vector<T> &rightSide);
  bool operator ==(const Vector<T> &rightSide) const;
  T& operator [](int index);
  const T& operator [](int index) const;

  int size() const;
  int capacity() const;
  void clear();
  void reserve(int new_cap);
  void shrink_to_fit();
  void push_back(const T &value);

private:
  std::unique_ptr<T[]> arr;
  int mCapacity;
  int mSize;
  bool isFull() const;
};


template <typename T>
Vector<T>::Vector() : mCapacity(0), mSize(0) {
  arr.reset(new T[mCapacity]);
}

template <typename T>
Vector<T>::Vector(int capacity) : mCapacity(capacity), mSize(capacity) {
  arr.reset(new T[mCapacity]);
}

template <typename T>
Vector<T>::Vector(const Vector<T> &rightSide) {

  mCapacity = rightSide.mCapacity;
  mSize = rightSide.mSize;
  arr.reset(new T[mCapacity]());
  // copy over
  for (unsigned int i = 0; i < mSize; i++) {
    arr[i] = rightSide.arr[i];
  }
}


template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T> &rightSide) {
  if (this != &rightSide) {
    if (mCapacity != rightSide.mCapacity || mSize != rightSide.mSize) {
      mCapacity = rightSide.mCapacity;
      mSize = rightSide.mSize;
    }
    arr.reset(new T[mCapacity]);
    for (unsigned int i = 0; i < mSize; i++) {
      arr[i] = rightSide.arr[i];
    }
  }
  return( *this );
}

template <typename T>
bool Vector<T>::operator ==(const Vector<T> &rightSide) const {
  if (this != &rightSide) {
    if (mSize != rightSide.mSize || mCapacity != rightSide.mCapacity) {
      return( false );
    }
    for (unsigned int i = 0; i < mSize; i++) {//  Compare all elements
      if (arr[i] != rightSide.arr[i]) {
        return( false );//          Not equal if not same element in same Order
      }
    }//                          If it makes it to hear the Vector's are equal
  }
  return( true );
}

template <typename T>
T& Vector<T>::operator [](int index) {
  if (index > mSize-1 || index < 0) {
    throw std::out_of_range("Bad index");
  }
  return arr[index];
}

template <typename T>
const T& Vector<T>::operator [](int index) const {
  if (index > mSize-1 || index < 0) {
    throw std::out_of_range("Bad index");
  }
  return arr[index];
}

template <typename T>
int Vector<T>::size() const { return mSize; }

template <typename T>
int Vector<T>::capacity() const { return mCapacity; }

template <typename T>
void Vector<T>::clear() {
  arr.reset(new T[mCapacity]);
}

template <typename T>
void Vector<T>::reserve(int new_cap) {
  if (new_cap > mCapacity) {
    Vector<T> temp(*this);
    mCapacity = new_cap;
    arr.reset(new T[mCapacity]);
    for (unsigned int i = 0; i < mSize; i++) {
      arr[i] = temp[i];
    }
  }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
  if (mSize != mCapacity) {
    Vector<T> temp(*this);
    mCapacity = mSize;
    arr.reset(new T[mCapacity]);
    for (unsigned int i = 0; i < mSize; i++) {
      arr[i] = temp[i];
    }
  }
}

template <typename T>
void Vector<T>::push_back(const T &value) {
  if (mCapacity == 0) mCapacity++;
  if (isFull()) reserve(mCapacity * 2);

  arr[mSize] = value;
  mSize++;
}

template <typename T>
bool Vector<T>::isFull() const {
  return( mSize >= mCapacity );
}


#endif //VECTOR_H
