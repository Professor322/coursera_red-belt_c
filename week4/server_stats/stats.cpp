//
// Created by professor on 4/15/20.
//
#include "stats.h"

Stats::Stats() :
method_stats({
	{"GET", 0},
	{"POST", 0},
	{"PUT", 0},
	{"DELETE", 0},
	{"UNKNOWN", 0}
	}),
uri_stats({
	{"/", 0},
	{"/order", 0},
	{"/product", 0},
	{"/basket", 0},
	{"/help", 0},
	{"unknown", 0}
})
{}

void Stats::AddMethod(string_view method) {
	auto it = method_stats.find(method);
	it == method_stats.end() ?
	++method_stats.at("UNKNOWN") :
	++it->second;
}

void Stats::AddUri(string_view uri) {
	auto it = uri_stats.find(uri);
	it == uri_stats.end() ?
	++uri_stats.at("unknown") :
	++it->second;

}

const map<string_view, int>& Stats::GetMethodStats() const {
	return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uri_stats;
}

string_view GetRequestPart(string_view& line) {
	line.remove_prefix(line.find_first_not_of(' '));

	size_t space = line.find(' ');
	string_view result = line.substr(0, space);

	line.remove_prefix(space + 1);
	return result;
}

HttpRequest ParseRequest(string_view line) {
	HttpRequest request;

	request.method = GetRequestPart(line);
	request.uri = GetRequestPart(line);
	request.protocol = GetRequestPart(line);

	return request;
}