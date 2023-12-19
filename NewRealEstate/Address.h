#pragma once
#include <string>
#include <iostream>


using namespace std;


class Address
{
	string city, street;

public:
	Address(string city = "", string street = "") : city(city), street(street) {};
	~Address() {};

	string getCity() {  return city; }
	string getStreet() { return street; }

    bool operator==(Address& other) {
		return (this->city == other.city) && (this->street == other.street);
    }

};
