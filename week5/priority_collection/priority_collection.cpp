#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <map>

using namespace std;

template <typename T>
class PriorityCollection {
public:
	using Id = size_t;
	using Priority = int;


  // Добавить объект с нулевым приоритетом
  // с помощью перемещения и вернуть его идентификатор
  Id Add(T object) {
  		values.push_back({0, move(object)});
  		priorities.insert({0, values.size() - 1});
  		return values.size() - 1;
  }


  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
  template <typename ObjInputIt, typename IdOutputIt>
  void Add(ObjInputIt range_begin, ObjInputIt range_end,
           IdOutputIt ids_begin) {
  		for (auto it = range_begin; it != range_end; ++it) {
  			*(ids_begin++) = Add(move(*it));
  		}
  }

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const {
  		return values[id].first != -1;
  }

  // Получить объект по идентификатору
  const T& Get(Id id) const {
  		return values[id].second;
  }

  // Увеличить приоритет объекта на 1
  void Promote(Id id) {
  	priorities.erase({values[id].first, id});
  	priorities.insert({++values[id].first, id});
  }

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const {
  		auto it = priorities.begin();
  		return {values[it->second].second, it->first};
  }

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax() {
  	auto it = priorities.begin();
  	pair<T, int> result{move(values[it->second].second), it->first};

  	priorities.erase(it);
  	values[it->second].first = -1;
  	return result;

  }

private:
	set<pair<Priority, Id>, greater<>> priorities;
	vector<pair<Priority, T>> values;
  // Приватные поля и методы
};


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

//bool operator==(const pair<int, int>& lhs, const pair<int, int>& rhs) {
//	return lhs.second == rhs.second;
//}
//
//template <typename T>
//class Test {
//public:
//	using Id = int;
//
//	void Add(int k, T obj) {
//		vals.push_back(move(obj));
//		s.insert({k, vals.size() - 1});
//	}
//
//	void Find(Id id) {
//		auto it = s.find({0, id});
//		if (it != s.end()) {
//			cout << vals[it->second];
//		}
//	}
//
//	void Print() {
//		for (const auto& [x, y] : s) {
//			cout << x << " " << vals[y] << "   ";
//		}
//	}
//private:
//	set<pair<int, Id>, greater<>> s;
//	vector<T> vals;
//};
//
int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
