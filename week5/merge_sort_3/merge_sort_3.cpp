#include "test_runner.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <iterator>

using namespace std;
template<typename RandomIt>
using Value = typename RandomIt::value_type;


template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
  // Напишите реализацию функции,
  // не копируя сортируемые элементы
  if (range_end - range_begin < 2) {
	  return;
  }
  vector<Value<RandomIt>> nums{make_move_iterator(range_begin),
							   make_move_iterator(range_end)};
  size_t part = nums.size() / 3;
  auto part_1 = nums.begin() + part;
  auto part_2 = nums.begin() + part * 2;

  MergeSort(nums.begin(), part_1);
  MergeSort(part_1, part_2);
  MergeSort(part_2, nums.end());

  vector<Value<RandomIt>> temp;
  merge(make_move_iterator(nums.begin()), make_move_iterator(part_1),
  		make_move_iterator(part_1), make_move_iterator(part_2),
  		back_inserter(temp));

  merge(make_move_iterator(temp.begin()), make_move_iterator(temp.end()),
  		make_move_iterator(part_2), make_move_iterator(nums.end()),
  		range_begin);
}

void TestIntVector() {
  vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
  MergeSort(begin(numbers), end(numbers));
  ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  return 0;
}
