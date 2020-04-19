#include "test_runner.h"
#include "profile.h"
#include <vector>
#include <future>
#include <numeric>
using namespace std;

template <typename Iterator>
class IteratorRange {
public:
	IteratorRange<Iterator>(Iterator begin, Iterator end, size_t size) :
			first(begin),
			last(end),
			range_size(size)
	{}
	Iterator begin() const { return first; }
	Iterator end() const {return last; }

	size_t size() const { return range_size; }

private:
	Iterator first, last;
	size_t range_size;
};


template <typename Iterator>
class Paginator {
public:
	Paginator<Iterator>(Iterator begin, Iterator end, size_t page_size) :
			range_begin(begin),
			range_end(end) {
		if (page_size == 0) {
			page_size = 1;
		}
		size_t container_size = distance(begin, end);
		for (Iterator it = begin; it != end; ) {
			size_t actual_page_size = min(container_size, page_size);
			container_size -= actual_page_size;

			Iterator page_end = next(it, actual_page_size);
			pages.push_back({it, page_end, actual_page_size});
			_page_num++;
			it = page_end;
		}
	}

	typename vector<IteratorRange<Iterator>>::const_iterator	begin() const { return pages.begin(); }
	typename vector<IteratorRange<Iterator>>::const_iterator	end() const { return pages.end(); }


	typename vector<IteratorRange<Iterator>>::iterator	begin() { return pages.begin(); }
	typename vector<IteratorRange<Iterator>>::iterator	end() { return pages.end(); }

	size_t 		size() const {return _page_num; }

private:
	Iterator range_begin, range_end;
	vector<IteratorRange<Iterator>> pages;
	size_t _page_num = 0;
};


template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator{c.begin(), c.end(), page_size};
}

vector<vector<int>> GenerateMatrixOneThread(size_t size) {
	vector<vector<int>> result(size, vector<int>(size));
	static int64_t to_fill = 0;

	for (auto& row : result) {
		for (auto& elem : row) {
			elem = 1;
		}
	}
	return result;
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	const size_t page_size = matrix.size() / 4;
	int64_t total_sum = 0;
	auto pages = Paginate(matrix, page_size);
	vector<future<int64_t>> sums;
	for (auto& page : pages) {
		sums.push_back(async([&page] {
			int64_t sum = 0;
			for (auto& item : page) {
				sum += accumulate(item.begin(), item.end(), 0);
			}
			return sum;
		}));
	}
	for (auto& sum : sums) {
		total_sum += sum.get();
	}
	return total_sum;
}



void TestCalculateMatrixSum() {
  const vector<vector<int>> matrix = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
  };
  ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int64_t FindSum(const vector<vector<int>>& matrix) {
	int64_t sum = 0;

	for (const auto& row : matrix) {
		for (const auto& elem : row) {
			sum += elem;
		}
	}
	return sum;
}

void TestHeavyMatrix() {
	const int SIZE = 10000;
	vector<vector<int>> matrix = GenerateMatrixOneThread(SIZE);
	int64_t result1;
	int64_t result2;
	{
		LOG_DURATION("multithread sum")
		result1 = CalculateMatrixSum(matrix);
	}
	{
		LOG_DURATION("Single thread sum");
		result2 = FindSum(matrix);
	}
	ASSERT_EQUAL(result1, result2)
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestHeavyMatrix);

}
