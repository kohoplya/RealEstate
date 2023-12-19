#pragma once
#include "User.h"
#include "Address.h"
#include <string>

class Property
{
	Address* address;
	User* user;
	string type; // 1 - standard apartment, 2 - penthouse, 3 - private house
	int roomsCount, price, house, floor;
	bool forRent;

public:
	Property(Address* address, User* user, string type, int roomsCount, int price, bool forRent, int house, int floor)
		: address(address), user(user), type(type), roomsCount(roomsCount), price(price), forRent(forRent),
		house(house), floor(floor) {
	};
	~Property() {
	};

	void setRoomsCount(int c) { roomsCount = c; }
	void setPrice(int c) { price = c; }
	void setType(string c) { type = c; }
	void setForRent(bool c) { forRent = c; }
	void setHouse(int c) { house = c; }
	void setFloor(int c) { floor = c; }

	Address getAddress() { return *address; }
	int getRoomsCount() { return roomsCount; }
	int getPrice() { return price; }
	string& getType() { return type; }
	bool getForRent() { return forRent; }
	int getHouse() { return house; }
	int getFloor() { return floor; }
	User* getUser() { return user; }

	bool operator==(Property& other) {
		return (this->address == other.address) &&
			(this->user == other.user) &&
			(this->type == other.type) &&
			(this->roomsCount == other.roomsCount) &&
			(this->price == other.price) &&
			(this->house == other.house) &&
			(this->floor == other.floor) &&
			(this->forRent == other.forRent);
	}

	Property& operator=(const Property& other) {
		if (this != &other) {
			this->address = other.address;
			this->user = other.user;
			this->type = other.type;
			this->roomsCount = other.roomsCount;
			this->price = other.price;
			this->house = other.house;
			this->floor = other.floor;
			this->forRent = other.forRent;
		}
		return *this;
	}

};

