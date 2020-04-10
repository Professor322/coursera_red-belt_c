//
// Created by professor on 4/10/20.
//

#include <cinttypes>
#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <stack>

//time -10^18 10^18 __int64_t
//hotel name string
//client_id int
//room_count int

using namespace std;

int64_t current_time = 0;
static const int EXPIRE_TIME = 86400;

struct ClientQueries {
	queue<pair<int64_t, int>> queries;
	unordered_map<int, int> unique_clients;
};

class Clients {
public:
	void addClient(const string& hotel_name, int64_t time, int client_id) {
		hotels[hotel_name].queries.push({time, client_id});
		hotels[hotel_name].unique_clients[client_id]++;
	}

	int	uniqueClients(const string& hotel_name) {
		if (!hotels.count(hotel_name)) {
			return 0;
		}
		removeOldClients(hotel_name);
		return hotels[hotel_name].unique_clients.size();
	}

	void removeOldClients(const string& hotel_name) {
		queue<pair<int64_t, int>>& queries = hotels[hotel_name].queries;
		unordered_map<int, int>& uniq_clients = hotels[hotel_name].unique_clients;

		while (!queries.empty() &&
		!(queries.front().first > current_time - EXPIRE_TIME &&
			queries.front().first <= current_time )) {
			int id = queries.front().second;
			uniq_clients[id]--;
			if (uniq_clients[id] == 0)
				uniq_clients.erase(id);
			queries.pop();
		}
	}

private:
	unordered_map<string, ClientQueries > hotels;
};

struct RoomsQueries {
	queue<pair<int64_t, int>> queries;
	int total_rooms_count;
};

class Rooms {
public:
	void  addRooms(const string& hotel_name, int64_t time, int rooms_count) {
		hotels[hotel_name].queries.push({time, rooms_count});
		hotels[hotel_name].total_rooms_count += rooms_count;
	}

	int  roomsCount(const string& hotel_name) {
		if (!hotels.count(hotel_name)) {
			return 0;
		}
		removeOldRooms(hotel_name);
		return hotels[hotel_name].total_rooms_count;
	}

	void removeOldRooms(const string& hotel_name) {
		queue<pair<int64_t, int>>& queries = hotels[hotel_name].queries;
		int& total_rooms_count = hotels[hotel_name].total_rooms_count;

		while (!queries.empty() &&
			   !(queries.front().first > current_time - EXPIRE_TIME &&
				 queries.front().first <= current_time )) {

			total_rooms_count -= queries.front().second;
			queries.pop();
		}
	}
private:
	unordered_map<string, RoomsQueries> hotels;
};


class BookingManager {
public:
	BookingManager() = default;
	void Book(int64_t time, const string& hotel_name, int client_id, int room_count) {
		clients.addClient(hotel_name, time, client_id);
		rooms.addRooms(hotel_name, time, room_count);
		current_time = time;
	}

	int clientsQuery(const string& hotel_name)  {
		return clients.uniqueClients(hotel_name);
	}

	int roomsQuery(const string& hotel_name)  {
		return rooms.roomsCount(hotel_name);
	}


private:
	Clients clients;
	Rooms rooms;
};

int 	main() {
	//fast io
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	BookingManager bm;
	int q;
	cin >> q;

	for (int i = 0; i < q; ++i) {
		string query;
		string hotel_name;

		cin >> query;
		if (query == "BOOK") {
			int64_t time;
			int client_id, room_count;

			cin >> time >> hotel_name >> client_id >> room_count;
			bm.Book(time, hotel_name, client_id, room_count);

		} else if (query == "CLIENTS") {
			cin >> hotel_name;
			cout << bm.clientsQuery(hotel_name) << '\n';;
		} else if (query == "ROOMS") {
			cin >> hotel_name;
			cout << bm.roomsQuery(hotel_name) << '\n';
		}
	}

	return 0;
}
