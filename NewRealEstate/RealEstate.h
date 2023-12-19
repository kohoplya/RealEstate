#pragma once

#include <vector>
#include "Address.h"
#include "User.h"
#include "Input.h"
#include "Window.h"
#include "Property.h"
#include "Menu.h"

class RealEstate : Window {
	vector<User> users;
	vector<Property> properties;
	vector<Address> addresses;
public:
	RealEstate();
	~RealEstate() {};

	void printMenu();
	void printUserMenu(User* user);

	void createUser();
	User* loginUser();

	bool checkUsername(Input& inp);
	bool checkPassword(Input& inp);
	bool checkNumber(Input& inp);
	bool checkBroker(Input& inp);
	bool checkType(Input& inp);
	bool checkFloor(Input& inp);
	bool checkRent(Input& inp);

	bool postNewProperty(User& user);
	void printAllCities(Menu& menu, User& user);
	void printStreetsForCity(string& cityName, User& user);
	void printProperty(Property* prop, int x, int y);

	Property& chooseProperty(User& user, string& cityName, string& streetName);
	void removeProperty(User& user);
	void printAllProperties(User* user = NULL);
	void searchProperties();
};