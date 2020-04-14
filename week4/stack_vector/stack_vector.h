
#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:

//  StackVector<T, N>() : _size(0) {}

  explicit StackVector(size_t a_size = 0) {
  	if (a_size > N) {
  		throw invalid_argument("size is bigger than capacity");
  	}
  	_size = a_size;
  }

  T& operator[](size_t index) {
  	return data[index];
  }
  const T& operator[](size_t index) const {
  	return data[index];
  }

  typename array<T,N>::iterator begin() {
  	return data.begin();
  }
  typename array<T, N>::iterator end() {
  	return data.begin() + _size;
  }
  typename array<T, N>::const_iterator  begin() const {
  	return data.begin();
  }
  typename array<T, N>::const_iterator end() const {
  	return data.begin() + _size;
  }

  size_t Size() const {
  	return _size;
  }
  size_t Capacity() const {
  	return data.max_size();
  }


  void PushBack(const T& value) {
  	if (_size == Capacity()) {
  		throw overflow_error("buffer overflow");
  	}
  	data[_size++] = value;
  }
  T PopBack() {
  	if (_size == 0) {
  		throw underflow_error("buffer underflow");
  	}
  	return data[_size-- - 1];
  }

private:
	array<T, N> data;
	size_t _size;
};

