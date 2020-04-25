#include "search_server.h"
#include "iterator_range.h"
#include "profile.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <iostream>
#include <numeric>

vector<string_view> SplitIntoWords(string_view line) {
	vector<string_view> result;
	size_t start;
	size_t end;

	while (!line.empty()) {
		start = line.find_first_not_of(' ', 0);
		end = line.find_first_of(' ', start);

		if (start != line.npos) {
			result.push_back(line.substr(start, end != line.npos ? end - start : end));
		}
		line.remove_prefix(end == line.npos ? line.size() : end);
	}

	return result;
}

SearchServer::SearchServer(istream& document_input) {
  UpdateDocumentBase(document_input);
}


void SearchServer::UpdateDocumentBase(istream& document_input) {
	if (is_first_time) {
		lock_guard<shared_mutex> guard(m);
		InvertedIndex new_index;
		for (string current_document; getline(document_input, current_document);) {
			new_index.Add(move(current_document));
		}
		index.Swap(new_index);
		is_first_time = false;
	}
}


void SearchServer::AddQueriesStreamOneThread(istream &query_input, ostream &search_results_output) {
	shared_lock<shared_mutex> guard(m);
	const size_t SIZE = index.GetDocsCount();
	vector<pair<size_t, size_t>> docid_count(SIZE);

	for (string current_query; getline(query_input, current_query); ) {
		docid_count.assign(SIZE, {0, 0});
			for (auto& word : SplitIntoWords(current_query)) {
				for (const auto&[docid, count] : index.Lookup(word)) {
					docid_count[docid].first = docid;
					docid_count[docid].second += count;
				}
			}
			partial_sort(
					begin(docid_count),
					begin(docid_count) + min(TOP_RESULTS, SIZE),
					end(docid_count),
					[](const pair<size_t, size_t> &lhs, const pair<size_t, size_t> &rhs) {
						int64_t lhs_docid = lhs.first;
						auto lhs_hit_count = lhs.second;
						int64_t rhs_docid = rhs.first;
						auto rhs_hit_count = rhs.second;
						return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
					}
			);
			search_results_output << current_query << ':';
			for (auto it = begin(docid_count);
				 it != end(docid_count) && it->second != 0 &&
				 it - begin(docid_count) != TOP_RESULTS;
				 ++it) {
				search_results_output << " {"
									  << "docid: " << it->first << ", "
									  << "hitcount: " << it->second << '}';
			}
			search_results_output << '\n';
	}
}
void SearchServer::AddQueriesStream(
		istream& query_input, ostream& search_results_output
) {
//	AddQueriesStreamOneThread(query_input, search_results_output);
		queries.push_back(async(
				&SearchServer::AddQueriesStreamOneThread,
				this,
				ref(query_input),
				ref(search_results_output)));
}

void InvertedIndex::Add(string document) {
	docs.push_back(move(document));
	const size_t docid = docs.size() - 1;
	for (auto& word : SplitIntoWords(docs.back())) {
		auto& elem = index[word];
		if (elem.empty() || elem.back().first != docid) {
			elem.push_back({docid, 1});
		} else {
			elem.back().second++;
		}
	}
}

vector<pair<size_t, size_t>> InvertedIndex::Lookup(const string_view word) const {
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	} else {
		return {};
	}
}
