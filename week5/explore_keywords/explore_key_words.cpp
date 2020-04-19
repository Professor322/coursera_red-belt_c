#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <future>
using namespace std;

class IteratorRange {
public:
	using Iterator = vector<string>::const_iterator;
	IteratorRange(Iterator begin, Iterator end, size_t size) :
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


class Paginator {
public:
	using Iterator = vector<string>::const_iterator;
	Paginator(Iterator begin,
			Iterator end,
			size_t page_size) :
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

	typename vector<IteratorRange>::const_iterator	begin() const { return pages.begin(); }
	typename vector<IteratorRange>::const_iterator	end() const { return pages.end(); }


	typename vector<IteratorRange>::iterator	begin() { return pages.begin(); }
	typename vector<IteratorRange>::iterator	end() { return pages.end(); }

	size_t 		size() const {return _page_num; }

private:
	Iterator range_begin, range_end;
	vector<IteratorRange> pages;
	size_t _page_num = 0;
};

Paginator Paginate(const vector<string>& c, size_t page_size) {
	return Paginator{c.begin(), c.end(), page_size};
}

struct Stats {
  map<string, int> word_frequences;

  void operator += (const Stats& other) {
  	for (const auto& [key_word, count] : other.word_frequences) {
  		word_frequences[key_word] += count;
  	}
  }
};

vector<string> StashLines(istream& input) {
	vector<string> result;
	string line;
	while (getline(input, line)) {
		result.push_back(move(line));
	}
	return result;
}
Stats ExploreLine(const set<string>& key_words, const string& line) {
	Stats line_result;
	stringstream ss(line);
	string token;

	while (ss >> token) {
		auto it = key_words.find(token);
		if (it != key_words.end()) {
			++line_result.word_frequences[*it];
		}
	}
	return line_result;
}

Stats CountKeyWords(const set<string>& key_words,
			const IteratorRange& range) {
	Stats range_result;
	for (auto& elem : range) {
		range_result += ExploreLine(key_words, elem);
	}
	return range_result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
  	Stats result;

  	 vector<string> lines;
	{
		LOG_DURATION("seq creation");
		lines = StashLines(input);
	}
  	const size_t page_size = lines.size() / 4;
  	Paginator pages = Paginate(lines, page_size);

  	vector<future<Stats>> stats;

  	for (auto& page : pages) {
  		stats.push_back(async(CountKeyWords, ref(key_words), ref(page)));
  	}
  	for (auto& stat : stats) {
  		result += stat.get();
  	}
	return result;
}

//stringstream createHeavyStream() {
//	stringstream is;
//	const size_t WORDS_IN_LINE_MAX = 20;
//	const size_t LINE_MAX = 50000;
//	const string token = "yangle";
//
//	for (size_t i = 0; i < LINE_MAX; ++i) {
//		for (size_t j = 0; j < WORDS_IN_LINE_MAX; ++j) {
//			is << token << ' ';
//		}
//		is << '\n';
//	}
//	return is;
//}
//
//void TestBasic() {
//  const set<string> key_words = {"yangle", "rocks", "sucks", "all"};
//
//  stringstream ss;
//  ss << "this new yangle service really rocks\n";
//  ss << "It sucks when yangle isn't available\n";
//  ss << "10 reasons why yangle is the best IT company\n";
//  ss << "yangle rocks others suck\n";
//  ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
//
//  const auto stats = ExploreKeyWords(key_words, ss);
//  const map<string, int> expected = {
//    {"yangle", 6},
//    {"rocks", 2},
//    {"sucks", 1}
//  };
//  ASSERT_EQUAL(stats.word_frequences, expected);
//}
//
//void TestHeavyStream() {
//	stringstream ss =createHeavyStream();
//	const set<string> key_words{"yangle"};
//
//	const map<string, int> expected = {
//			{"yangle", 50000 * 20}
//	};
//	Stats stats;
//	{
//		LOG_DURATION("multi thread computing");
//		stats = ExploreKeyWords(key_words, ss);
//	}
//	ASSERT_EQUAL(stats.word_frequences, expected);
//}
//
//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestBasic);
//  RUN_TEST(tr, TestHeavyStream);
//}
