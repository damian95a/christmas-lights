#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

template <typename T>
class SimpleVector{
  protected:
  int s;  // Size of array
  T * elem; // Array

  public:
  // Empy vector
  SimpleVector(): s(0), elem(nullptr){}
  // n-element vector
  SimpleVector(int n);
  // fill n-element vector
  SimpleVector(int n, T var);

  // Add element at the end
  void push_back(const T& value);
  void push_back(T&& value);
  
  // Remove the last element
  // and return its value
  T pop_back();
  // here you can set error value to return
  T pop_back(T err_val);

  // Array operator
  T& operator[](int ix) const;

  int size() const; // return array size
  T * begin() const; // return pointer to the first element
  T * end() const;  // return pointer to the last element
  // ask if vector is empty
  bool is_empty() const;
  
  // free the memory
  ~SimpleVector(){s = 0; free(elem);}
};

#endif
