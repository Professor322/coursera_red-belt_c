#include <string>
#include <vector>
#include <iostream>
using namespace std;
/*
#define f(a,b) a##b
#define g(a)   #a
#define h(a) g(a)

int main()
{
	cout << h(f(1,2)) << endl;
	cout << g(f(1,2)) << endl;
	return 0;
}*/


#define CREATE_ID(num) id_ ## num

#define FIND_UNIQ_NO(num) CREATE_ID(num)

#define UNIQ_ID FIND_UNIQ_NO(__LINE__)
/*
int main() {
	int UNIQ_ID;
//	int UNIQ_ID = 0;
//  	string UNIQ_ID = "hello";
//  	vector<string> UNIQ_ID = {"hello", "world"};
//  	vector<int> UNIQ_ID = {1, 2, 3, 4};
}*/