#include "simple_vector.h"
#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void TestConstruction() {
  SimpleVector<int> empty;
	ASSERT(empty.begin() == empty.end());
  ASSERT_EQUAL(empty.Size(), 0u);
  ASSERT_EQUAL(empty.Capacity(), 0u);


  SimpleVector<string> five_strings(5);
  ASSERT_EQUAL(five_strings.Size(), 5u);
  ASSERT(five_strings.Size() <= five_strings.Capacity());
  for (auto& item : five_strings) {
    ASSERT(item.empty());
  }
  five_strings[2] = "Hello";
  ASSERT_EQUAL(five_strings[2], "Hello");

  SimpleVector<int> empty2(0);
	ASSERT(empty2.begin() == empty2.end());
}

void TestPushBack() {
  SimpleVector<int> v;
  for (int i = 10; i >= 1; --i) {
    v.PushBack(i);
    ASSERT(v.Size() <= v.Capacity());
  }
  sort(begin(v), end(v));

  const vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  ASSERT_EQUAL(v.Size(), expected.size());
  ASSERT(equal(begin(v), end(v), begin(expected)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestConstruction);
  RUN_TEST(tr, TestPushBack);
  return 0;
}
