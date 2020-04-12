#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
  	T *element;

  	if (!deallocated.empty()) {
  		element = deallocated.front();
  		deallocated.pop();
  		allocated.insert(element);
  	} else {
  		element = new T;
  		allocated.insert(element);
  	}
  	return element;
  }
  T* TryAllocate() {
	  T *element = nullptr;

	  if (!deallocated.empty()) {
		  element = deallocated.front();
		  deallocated.pop();
		  allocated.insert(element);
	  }

	  return element;
  }

  void Deallocate(T* object) {
		auto element = allocated.find(object);

		if (element == allocated.end()) {
			throw invalid_argument("no such element");
		}
		deallocated.push(*element);
		allocated.erase(element);
  }

  ~ObjectPool() {
  		for (auto& elem : allocated) {
  			delete elem;
  		}
  		while (!deallocated.empty()) {
  			delete deallocated.front();
  			deallocated.pop();
  		}
  }

private:
	set<T*> allocated;
  	queue<T*> deallocated;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
