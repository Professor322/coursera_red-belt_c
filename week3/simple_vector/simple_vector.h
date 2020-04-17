#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() :
		  	capacity(0),
		  	_size(0),
			data(nullptr),
			first(nullptr),
			last(nullptr)
  			{}

  explicit SimpleVector(size_t size) :
  capacity(size),
  _size(size) {
  	data = new T[capacity];

  	first = data;
  	last = data + _size;
  }

  ~SimpleVector() {
  	delete [] data;
  }

  T& operator[](size_t index) {
  	return data[index];
  }

  T* begin() {
  	return first;
  }
  T* end() {
  	return last;
  }
  const T* begin() const {
  	return first;
  }
  const T* end() const {
  	return last;
  }

  size_t Size() const {
  	return _size;
  }
  size_t Capacity() const {
  	return capacity;
  }

  void PushBack(const T& value) {
  	check_reallocation();
  	data[_size++] = value;
  	last++;
  }

private:
	void check_reallocation() {
  		if (capacity == 0) {
  			capacity = 1;

  			delete [] data;
  			data = new T[capacity];
  			first = data;
  			last = first + 1;
  		} else if (_size == capacity) {
  			capacity *= 2;

  			T* temp_data = new T[capacity];
  			std::copy(first, last, temp_data);
  			delete []data;


  			data = first = temp_data;
  			last = first + _size;
  		}
  	}

  size_t capacity, _size;
  T* data;
  T* first, *last;
};
