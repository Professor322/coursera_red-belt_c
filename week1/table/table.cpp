#include "../../include/test_runner.h"
#include <vector>

using namespace std;

template <typename T>
class Table {
public:
	Table<T>(const size_t& rows, const size_t& cols) :
	_rows(rows),
	_cols(cols),
	table(rows, vector<T>(cols)) {}

	vector<T>& operator[](size_t i) {
		return table[i];
	}
	const vector<T>& operator[] (size_t i) const{
		return table[i];
	}

	void Resize(const size_t& rows, const size_t& cols) {
		table.resize(rows);
		for (auto& row : table)
			row.resize(cols);
		_rows = rows;
		_cols = cols;
	}

	pair<size_t, size_t> Size() const{
		return {_rows, _cols};
	}

	typename vector<vector<T>>::iterator begin() {
		return table.begin();
	}
	typename vector<vector<T>>::iterator end() {
		return table.end();
	}
private:
	size_t _rows, _cols;
	vector<vector<T>> table;

};

//void TestTable() {
//  Table<int> t(1, 1);
//  ASSERT_EQUAL(t.Size().first, 1u);
//  ASSERT_EQUAL(t.Size().second, 1u);
//  t[0][0] = 42;
//  ASSERT_EQUAL(t[0][0], 42);
//  ASSERT_EQUAL(t.Size().first, 3u);
//  ASSERT_EQUAL(t.Size().second, 4u);
//}
//
//int main() {
//  TestRunner tr;
//	 RUN_TEST(tr, TestTable);
//
//  return 0;
//}
