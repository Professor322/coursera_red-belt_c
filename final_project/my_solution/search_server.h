#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <future>
#include <shared_mutex>
#include <thread>
#include <unordered_map>

using namespace std;


class InvertedIndex {
public:
  void Add(string document);
  vector<pair<size_t, size_t>> Lookup(string_view word) const;

  void Swap(InvertedIndex& other) {
  	swap(index, other.index);
  	swap(docs, other.docs);
  }
  size_t GetDocsCount() const { return docs.size(); }
private:
  unordered_map<string_view , vector<pair<size_t, size_t>>> index;
  list<string> docs;
};

class SearchServer {
public:
	SearchServer() = default;
	explicit SearchServer(istream& document_input);
	void UpdateDocumentBase(istream& document_input);
	void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
	void AddQueriesStreamOneThread(istream& query_input, ostream& search_results_output);

	const size_t TOP_RESULTS = 5;

	bool is_first_time = true;
	InvertedIndex index;
	shared_mutex m;
	vector<future<void>> queries;
};
