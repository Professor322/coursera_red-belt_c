#include "test_runner.h"
#include <string>
#include <map>

using namespace std;

class Translator {
public:
	Translator() = default;

	void Add(string_view source, string_view target) {
		auto it_source = words.insert(string(source));
		auto it_target = words.insert(string(target));

  		_source[*it_source.first] = *it_target.first;
  		_target[*it_target.first] = *it_source.first;
  	}

  	string_view TranslateForward(string_view source) const {
		auto it = _source.find(source);
		return it == _source.end() ? "" : it->second;
	}
  	string_view TranslateBackward(string_view target) const {
		auto it = _target.find(target);
		return it == _target.end() ? "" : it->second;
	}

private:
	set<string> words;
	map<string_view , string_view> _source;
	map<string_view , string_view> _target;
};


void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
