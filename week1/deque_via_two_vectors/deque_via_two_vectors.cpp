//
// Created by professor on 4/8/20.
//
#include <vector>
#include <iostream>
//#include "test_runner.h"

#define ELEMENT_ACCESS(index) 					\
	size_t size = Size(); 						\
	size_t pf_size = pf_values.size();			\
	if (index < pf_size) { 						\
        return pf_values[pf_size - index - 1];	\
    } 											\
	return pb_values[index - pf_size]

#define FRONT 						\
	if (pf_values.empty()) 			\
		return pb_values.front(); 	\
	return pf_values.back()

#define BACK 						\
	if (pb_values.empty()) 			\
		return pf_values.front(); 	\
	return pb_values.back()

using namespace std;

template <typename T>
class Deque {
public:
	Deque<T>() = default;

	bool Empty() const { return pb_values.empty() && pf_values.empty(); }
	size_t Size() const { return pb_values.size() + pf_values.size(); }

	T& operator[](size_t index) {
		ELEMENT_ACCESS(index);
	}
	const T& operator[](size_t index) const {
		ELEMENT_ACCESS(index);
	}

	T& At(size_t index) {
		if (index >= Size()) {
			throw out_of_range("element is out of range");
		}
		ELEMENT_ACCESS(index);
	}

	const T& At(size_t index) const {
		if (index >= Size()) {
			throw out_of_range("element is out of range");
		}
		ELEMENT_ACCESS(index);
	}

	T& Front() { FRONT;}
	const T& Front() const { FRONT; }

	T& Back() { BACK; }
	const T& Back() const { BACK; }

	void PushFront(const T& elem) {
		pf_values.push_back(elem);
	}
	void PushBack(const T& elem) {
		pb_values.push_back(elem);
	}
private:
	vector<T> pb_values;
	vector<T> pf_values;
};


//void testAll() {
//	{
//		auto d = Deque<int>();
//		d.PushBack(1);
//		d.PushBack(2);
//		d.PushBack(3);
//		cout << d[1] << endl;
//	}
//	{
//		Deque<int> d;
//		d.PushFront(1);;
//		d.PushBack(2);
//		ASSERT_EQUAL(d.Back(), 2);
//	}
//	{
//		Deque<int> d;
//		d.PushBack( 1);
//		d.PushFront(2);
//		ASSERT_EQUAL(d.Back(), 1);
//	}
//	{
//		Deque<int> d;
//
//
//		d.PushBack(1);
//		d.PushBack(2);
//		d.PushBack(3);
//		ASSERT_EQUAL(d.Front(), 1);
//		ASSERT_EQUAL(d.Back(), 3);
//		ASSERT_EQUAL(d[1], 2);
//
//		d.PushFront(7);
//		d.PushFront(17);
//		d.PushFront(4);
//
//		ASSERT_EQUAL(d.Front(), 4);
//		ASSERT_EQUAL(d.Back(), 3);
//		ASSERT_EQUAL(d[1], 17);
//
//		vector<int> test;
//		for (int i = 0; i < d.Size(); ++i) {
//			test.push_front(d[i]);
//		}
//		ASSERT_EQUAL(test, (vector{4, 17, 7, 1, 2, 3}));
//	}
//}

//int 	main() {
////	TestRunner t;
////	RUN_TEST(t, testAll);
//	deque<int> d1;
//	Deque<int> d2;
//
////	d1.push_front(1); d1.push_front(2); d1.push_front(3); d1.push_front(4);
////	d1.push_front(2);
////	d2.PushFront(1); d2.PushFront(2); d2.PushFront(3); d2.PushFront(4);
////	d2.PushFront(2);
//
////	for (int i = 0; i < d1.size(); ++i) {
////		cout << d1[i] << " ";
////	}
////	cout << endl;
////	for (int i = 0; i < d2.Size(); ++i) {
////		cout << d2[i] << " ";
////	}
////	cout << endl;
////	cout << d1.front() << " " << d2.Front() << endl;
////
//
//
//	return 0;
//}