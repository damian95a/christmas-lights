#include "simplevector.h"

template <typename T>
SimpleVector<T>::SimpleVector(int n){
  // alloc an array
  
  s = n; // set size
  elem = new T[n]; // alloc array
}

template <typename T>
SimpleVector<T>::SimpleVector(int n, T val){
  // alloc an array
  // and init it
  
  s = n; // set size
  elem = new T[n]; // alloc array

  for(auto p=elem; p<elem+s; ++p){
    *p = val;
  }
}


template <typename T>
void SimpleVector<T>::push_back(const T& value){
  // add element at the end

  // alloc temporary array
  T* tmp = new T[s+1];
  // copy vector to the new array
  for(int i=0; i<s; ++i){
    tmp[i] = elem[i];
  }

  // add new element at the end of new array
  tmp[s] = value;
  s+=1;

  // if elem has been empty before
  // remove previous array
  if (s>1)
    delete[] elem;

  // assign temporary array as the vector
  elem = tmp;
  tmp = nullptr;
}

template <typename T>
void SimpleVector<T>::push_back(const T&& value){
  // add element at the end
  // (reference to the temporary value)

  // alloc temporary array
  T* tmp = new T[s+1];
  // copy vector to the new array
  for(int i=0; i<s; ++i){
    tmp[i] = elem[i];
  }

  // add new element at the end of new array
  tmp[s] = value;
  s+=1;

  // if elem has been empty before
  // remove previous array
  if (s>1)
    delete[] elem;

  // assign temporary array as the vector
  elem = tmp;
  tmp = nullptr;
}

template <typename T>
T SimpleVector<T>::pop_back(){
  // remove last element
  // if type of vector is smaller than int it may not work
  // in that case you should use the second version of the function

  // if vector is already empy
  // return ERROR (32202);
  if(s<=0)
    return 32202;

  // alloc temporary array
  T* tmp = new T[s-1];
  // copy vector array to the new array
  // (without the last element)
  for(int i=0; i<s-1; ++i){
    tmp[i] = elem[i];
  }

  // save an element to remove
  T value = elem[s-1];
  // shorten array
  s-=1;

  // remove prevoius array
  delete[] elem;

  // assign temporary array as the vector
  elem = tmp;
  tmp = nullptr;

  // return removed element
  return value;
}


template <typename T>
T SimpleVector<T>::pop_back(T err_val){
  // remove last element
  // in this version you can choose error value to return

  // if vector is already empy
  // return ERROR (err_val);
  if(s<=0)
    return err_val;

  // alloc temporary array
  T* tmp = new T[s-1];
  // copy vector array to the new array
  // (without the last element)
  for(int i=0; i<s-1; ++i){
    tmp[i] = elem[i];
  }

  // save an element to remove
  T value = elem[s-1];
  // shorten array
  s-=1;

  // remove prevoius array
  delete[] elem;

  // assign temporary array as the vector
  elem = tmp;
  tmp = nullptr;

  // return removed element
  return value;
}


template <typename T>
T& SimpleVector<T>::operator[](int ix) const{
  // return elem[ix]
  return *(elem+ix);
}

template <typename T>
int SimpleVector<T>::size() const{
  // return size of the array
  return s;
}

template <typename T>
T * SimpleVector<T>::begin() const{
  // return pointer to the first element
  return elem;
}

template <typename T>
T * SimpleVector<T>::end() const{
  // return pointer to element next to the last
  return elem+s;
}

template <typename T>
bool SimpleVector<T>::is_empty() const{
  // returns true if vector is empty
  
  if(s>0)
    return false;
  else
    return true;
}
