#include "airline_ticket.h"
#include "../../include/test_runner.h"
#include <tuple>
#include <string>

using namespace std;

bool operator==(const Date& lhs, const Date& rhs) {
	return tie(lhs.year, lhs.month, lhs.day) == tie(rhs.year, rhs.month, rhs.day);
}

#define READ_DATE(is, buff, date, field) \
getline(is, buff, '-'); \
date.field = stoi(buff);

istream& operator>>(istream& is, Date& date) {
	string buff;

	READ_DATE(is, buff, date, year);
	READ_DATE(is, buff, date, month);
	READ_DATE(is, buff, date, day);
	return is;
}

ostream& operator<<(ostream& os, const Date& date) {
	os << date.year << " " << date.month << " " <<date.day;
	return os;
}

ostream& operator<<(ostream& os, const Time& time) {
	os << time.hours << " " << time.minutes;
	return os;
}

bool operator==(const Time& lhs, const Time& rhs) {
	return tie(lhs.hours, lhs.minutes) == tie(rhs.hours, rhs.minutes);
}

#define READ_TIME(is, buff, time, field) \
getline(is, buff, ':'); \
time.field = stoi(buff);

istream& operator>>(istream& is, Time& time) {
	string buff;

	READ_TIME(is, buff, time, hours);
	READ_TIME(is, buff, time, minutes);
	return is;
}

#define UPDATE_FIELD(ticket, field, values)  \
if (values.count(#field)) {					 \
	istringstream is(values.at(#field));	 \
	is >> ticket.field;						 \
}


//void TestUpdate() {
//  AirlineTicket t;
//  t.price = 0;
//
//  const map<string, string> updates1 = {
//    {"departure_date", "2018-2-28"},
//    {"departure_time", "17:40"},
//  };
//  UPDATE_FIELD(t, departure_date, updates1);
//  UPDATE_FIELD(t, departure_time, updates1);
//  UPDATE_FIELD(t, price, updates1);
//
//  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//  ASSERT_EQUAL(t.price, 0);
//
//  const map<string, string> updates2 = {
//    {"price", "12550"},
//    {"arrival_time", "20:33"},
//  };
//  UPDATE_FIELD(t, departure_date, updates2);
//  UPDATE_FIELD(t, departure_time, updates2);
//  UPDATE_FIELD(t, arrival_time, updates2);
//  UPDATE_FIELD(t, price, updates2);
//
//  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
//  // значения этих полей не должны измениться
//  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
//  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
//  ASSERT_EQUAL(t.price, 12550);
//  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
//}
//
//int main() {
//  TestRunner tr;
//  RUN_TEST(tr, TestUpdate);
//}
