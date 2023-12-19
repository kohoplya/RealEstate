#include "RealEstate.h"
#include "Menu.h"
#include "Input.h"
#include "Address.h"
#include "Property.h"
#include <iostream>
#include <conio.h>
#include "Window.h"
#include <vector>
#include <string>

using namespace std;

RealEstate::RealEstate() {
	addresses.push_back(Address("Kyyiv", "Lavrska Street"));
	addresses.push_back(Address("Kyyiv", "Sports Square"));
	addresses.push_back(Address("Kherson", "Ushakova avenue"));
	addresses.push_back(Address("Kherson", "Perekopska street"));
	addresses.push_back(Address("Kherson", "Polkovnyka Kedrovsky Street"));
	addresses.push_back(Address("Kryvyy Rih", "Heroiv ATO street"));
	addresses.push_back(Address("Mykolayiv", "Gagarina avenue"));
	addresses.push_back(Address("Mykolayiv", "Lermontova street"));
	addresses.push_back(Address("Poltava", "Stanislavskyi street"));
	addresses.push_back(Address("Donets'k", "Prospekt Myru"));
}

void RealEstate::printMenu()
{
	Menu menu;
	menu.SetWidth(24);
	menu.SetHeight(4);

	menu.AddElement("Create an account").AddElement("Sign in").AddElement("Exit");

	while (1) {
		int choice = menu.Select();

		if (choice == 0) {
			createUser();
			clear();
		}
		else if (choice == 1) {
			User* user = loginUser();
			clear();
			if (user != nullptr) printUserMenu(user);
			clear();
		}
		else if (choice == 2) {
			GotoXY(0, 25);
			break;
		}
	}
}


void RealEstate::createUser()
{
	Window* win = createWindow(44, 5);
	char space = ' ';
	string cleaner(win->GetWidth() - 1, space);

	Input inp(win->GetWidth());
	string username, password, number;
	bool isBroker = false;

	do {
		inp.customInput(*win, "Enter username: ");

	} while (!checkUsername(inp));
	username = inp.getInput();
	do {
		inp.customInput(*win, "Enter password: ");
		if (!checkPassword(inp)) { win->writeText(win->GetY() + 2, "The password is not reliable, must contain a number and one of the following symbols: $,% or _."); }

	} while (!checkPassword(inp));
	password = inp.getInput();
	win->Show();
	do {
		inp.customInput(*win, "Enter number: ");
		if (!checkNumber(inp)) { win->writeText(win->GetY() + 2, "Bad phone number (should be 12 and start with 380)"); }

	} while (!checkNumber(inp));
	number = inp.getInput();
	do {
		inp.customInput(*win, "Broker - 1, else - 0: ");

	} while (!checkBroker(inp));
	if (inp.getInput()[0] = '1') isBroker = true;

	User user(username, password, number, isBroker);
	users.push_back(user);
}

bool RealEstate::checkUsername(Input& inp)
{
	if (inp.getInput()[0] == 0) return false;
	for (User user : users)
		if (user.getLogin() == inp.getInput())
			return false;

	return true;
}

bool RealEstate::checkPassword(Input& inp) {
	if (inp.getInput()[0] == 0) return false;
	bool isNum = false, isSym = false;

	for (int i = 0; inp.getInput()[i] != 0; i++) {
		char c = inp.getInput()[i];
		if (isdigit(c)) isNum = true;
		else if (c == '$' || c == '%' || c == '_') isSym = true;
	}
	if (isNum && isSym) {
		clear();
		return true;
	}
	return false;
}

bool RealEstate::checkNumber(Input& inp) {
	string phone = inp.getInput();

	if (phone.length() < 12)return false;
	for (int i = 0; i < phone.length(); i++) {
		if (!(phone[i] >= '0' && phone[i] <= '9')) return false;
	}
	if (phone[0] == '3' && phone[1] == '8' && phone[2] == '0' && phone.length() == 12) return true;
}

bool RealEstate::checkBroker(Input& inp) {
	string input = inp.getInput();

	if (inp.getInput()[0] == 0) return false;
	if (input.length() == 1 && (input == "0" || input == "1"))return true;
	return false;
}

User* RealEstate::loginUser(){
	Window* win = createWindow(44, 5);
	char space = ' ';
	string cleaner(win->GetWidth() - 1, space);
	string username, password;

	Input inp(win->GetWidth());
	inp.customInput(*win, "Enter username: ");
	username = inp.getInput();
	inp.customInput(*win, "Enter password: ");
	password = inp.getInput();

	for (User& user : users) {
		if (user.getLogin() == username && user.getPassword() == password) {
			return &user;
		}
	}

	inp.customInput(*win, "User not found, type anythng to return: ");
	return nullptr;
}

void RealEstate::printUserMenu(User* user)
{
	Menu menu;
	menu.SetWidth(35);
	menu.SetHeight(8);

	menu.AddElement("Publish new property").AddElement("Remove property").AddElement("Show all properties").AddElement("Show all your properties").AddElement("Search property by parameters").AddElement("Log out");

	while (1) {
		int choice = menu.Select();

		if (choice == 0) {
			postNewProperty(*user);
			clear();
		}
		else if (choice == 1) {
			removeProperty(*user);
			clear();
		}
		else if (choice == 2) {
			printAllProperties();
			clear();
		}
		else if (choice == 3) {
			printAllProperties(user);
			clear();
		}
		else if (choice == 4) {
			searchProperties();
			clear();
		}
		else if (choice == 5) {
			break;
			clear();
		}
	}
}

bool RealEstate::postNewProperty(User& user) {
	clear();
	Menu menu;
	menu.SetWidth(44);
	menu.SetHeight(8);

	char space = ' ';
	string cleaner(menu.GetWidth() - 1, space);

	Input inp(menu.GetWidth());

	if (user.getIsBroker() && user.getCountOfProp() >= 10){
		inp.customInput(menu, "Limit is exhausted, type anythng: ");
		return false;
	}
	else if (user.getCountOfProp() >= 3) {
		inp.customInput(menu, "Limit is exhausted, type anythng: ");
		return false;
	}

	printAllCities(menu, user);
	return true;
}

void RealEstate::printAllCities(Menu& menu, User& user) {
	vector<string> printedCities;

	for (Address& address : addresses) {

		bool alreadyPrinted = false;
		for (string& city : printedCities) {
			if (address.getCity() == city) {
				alreadyPrinted = true;
				break;
			}
		}

		if (!alreadyPrinted) {
			printedCities.push_back(address.getCity());
		}
	}

	for (string& city : printedCities) {
		menu.AddElement(city.c_str());
	}

	while (1) {
		int choice = menu.Select();

		if (choice >= 0) {
			string currentCity = printedCities[choice];
			printStreetsForCity(currentCity, user);
			break;
		}
	}
}

void RealEstate::printStreetsForCity(string& cityName, User& user) {
	clear();
	Menu menu;
	menu.SetWidth(44);
	menu.SetHeight(8);

	vector<string> printedStreets;

	for (int i = 0; i < addresses.size(); i++) {
		if (addresses[i].getCity() == cityName) {
			printedStreets.push_back(addresses[i].getStreet());
		}
	}

	for (string& street : printedStreets) {
		menu.AddElement(street.c_str());
	}
	
	while (1) {
		int choice = menu.Select();

		if (choice >= 0) {
			Property property = chooseProperty(user, cityName, printedStreets[choice]);
			properties.push_back(property);
			user.countOfProp++;
			GotoXY(0, 2); cout << user.countOfProp;
			break;
		}
	}
}

Property& RealEstate::chooseProperty(User& user, string& cityName, string& streetName) {
	Window* win = createWindow(44, 15);
	char space = ' ';
	string cleaner(win->GetWidth() - 1, space);

	Input inp(win->GetWidth());
	bool isRent = false;
	string type = "private house";
	int floor, newrooms, newhouse, newprice;
	floor = newhouse = newprice = newrooms = 0;

	do {
		inp.customInput(*win, "Enter type (1, 2, 3): ");
		if (!checkType(inp)) { win->writeText(win->GetY() + 2, "Enter correct type"); }

	} while (!checkType(inp));

	if (inp.getInput()[0] == '1') type = "standard apartment";
	if (inp.getInput()[0] == '2') type = "penthouse";
	win->Show();

	if (type == "standard apartment") {
		do {
			inp.customInput(*win, "Enter floor: ");
			if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Floor must be able and positive "); }

		} while (!checkFloor(inp));
		floor = stoi(inp.getInput());
	}

	win->Show();
	do {
		inp.customInput(*win, "Enter rooms: ");
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Rooms must be able and positive "); }

	} while (!checkFloor(inp));
	newrooms = stoi(inp.getInput());

	do {
		inp.customInput(*win, "Enter house number: ");
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "House number must be able and positive "); }

	} while (!checkFloor(inp));
	newhouse = stoi(inp.getInput());

	win->Show();
	do {
		inp.customInput(*win, "Is rent? (1 - Yes, 2 - No): ");
		if (!checkRent(inp)) { win->writeText(win->GetY() + 2, "Enter correct num"); }

	} while (!checkRent(inp));
	if (inp.getInput() == "1") isRent = true;

	win->Show();
	do {
		inp.customInput(*win, "Enter price: ");
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Price must be whole and positive "); }

	} while (!checkFloor(inp));
	newprice = stoi(inp.getInput());

	GotoXY(0, 0); cout << floor << " " << newhouse << " " << newrooms << " " << newprice;
	Address* address = new Address(cityName, streetName);
	User* usr = new User(user);

	Property* property = new Property(address, usr, type, newrooms, newprice, isRent, newhouse, floor);
	return *property;
}

bool RealEstate::checkType(Input& inp) {
	string input = inp.getInput();

	if (inp.getInput()[0] == 0) return false;
	if (input.length() == 1 && (input == "1" || input == "2" || input == "3"))return true;
	return false;
}

bool RealEstate::checkFloor(Input& inp) {
	string input = inp.getInput();

	for (char c : input) {
		if (isdigit(c)) {

		}
		else return false;
	}

	int floor = stoi(input);
	if (floor <= 0) return false;
	return true;
}

bool RealEstate::checkRent(Input& inp) {
	string input = inp.getInput();

	if (inp.getInput()[0] == 0) return false;
	if (input.length() == 1 && (input == "1" || input == "2" || input == "3"))return true;
	return false;
}

void RealEstate::removeProperty(User& user) {
	clear();
	Menu menu;
	menu.SetWidth(44);
	menu.SetHeight(8);
	menu.Show();

	char space = ' ';
	string cleaner(menu.GetWidth() - 1, space);

	Input inp(menu.GetWidth());

	if (user.getCountOfProp() == 0) {
		inp.customInput(menu, "No properties published: ");
		return;
	}

	vector<Property> publishedProperties;
	vector<string> str;

	for (Property& property : properties) {
		if (*property.getUser() == user) {
			publishedProperties.push_back(property);
		}
	}

	for (int i = 0; i < publishedProperties.size(); i++) {
		str.push_back(to_string(i + 1));
	}

	for (string& s : str) {
		menu.AddElement(s.c_str());
	}

	while (1) {
		int choice = menu.Select();

		if (choice >= 0) {

			for (auto it = properties.begin(); it != properties.end(); ++it) {
				if (*it->getUser() == user && *it == publishedProperties[choice]) {
					properties.erase(it);
				}
			}

			clear();
			Window* win = createWindow(44, 15);
			inp.customInput(menu, "Property was removed, type anythng: ");
			break;
		}
	}
}

void RealEstate::printProperty(Property* prop, int x, int y) {
	GotoXY(x, y); cout << "Address: " << prop->getAddress().getCity() << ", " << prop->getAddress().getStreet();
	GotoXY(x, y + 1); cout << "Type: " << prop->getType();
	GotoXY(x, y + 2); cout << "Floor: " << to_string(prop->getFloor());
	GotoXY(x, y + 3); cout << "House: " << to_string(prop->getHouse());
	GotoXY(x, y + 4); cout << "Price: " << to_string(prop->getPrice());
	GotoXY(x, y + 5); cout << "Rooms: " << to_string(prop->getRoomsCount());
	GotoXY(x, y + 6); cout << "User: " << (prop->getUser()->getLogin()) << ", " << (prop->getUser()->getNumber());

}


void RealEstate::printAllProperties(User* user) {
	int printedCount = 0;

	for (int i = 0; i < properties.size(); i++)
		if (!user || user->getLogin() == properties[i].getUser()->getLogin())
			printedCount++;

	Window* win = createWindow(44, 5);
	Input inp(win->GetWidth());

	if (printedCount == 0) {
		inp.customInput(*win, "No properties published: ");
		return;
	}

	clear();
	win = createWindow(44, (printedCount * 9));
	
	int y = win->GetY() + 1;
	printedCount = 0;
	for (int i = 0; i < properties.size(); i++) {
		int _y = y + (printedCount * 8);
		if (!user || user->getLogin() == properties[i].getUser()->getLogin()) {
			printedCount++;
			printProperty(&properties[i], win->GetX(), _y);
		}
	}
	inp.customInput(*win, "Type anythng to exit: ", win->GetHeight() - 1);
}

void RealEstate::searchProperties() {
	int checks = 0, checksNeeded = 0, min = 0, max = INT32_MAX, choice;
	int statuscheck = 0, roomcheck = 0, pricecheck = 0;
	string typecheck;

	Menu menu1;
	menu1.AddElement("For sale").AddElement("For rent").AddElement("Doesnt matter");
	while (true) {
		choice = menu1.Select();
		if (choice < 2) {
			statuscheck = choice;
			checksNeeded++;
			break;
		}
		break;
	}

	Menu menu2;
	menu2.AddElement("standard apartment").AddElement("penthouse").AddElement("private house").AddElement("Doesnt matter");
	while (true) {
		choice = menu2.Select();
		if (choice < 3) {
			if (choice == 0) typecheck = "standard apartment";
			if (choice == 1) typecheck = "penthouse";
			if (choice == 2) typecheck = "private house";
			checksNeeded++;
			break;
		}
		break;
	}

	Window* win = createWindow(50, 8);
	Input inp(win->GetWidth());

	do {
		inp.customInput(*win, "Enter room count (999 if doesnt matter): ");

		if (stoi(inp.getInput()) != 999) {
			roomcheck = stoi(inp.getInput());
			checksNeeded++;
			break;
		}
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Rooms must be able and positive "); }
	} while (!checkFloor(inp));
	win->Show();
	do {
		inp.customInput(*win, "Enter min. price (999 if doesnt matter): ");

		if (stoi(inp.getInput()) != 999) {
			min = stoi(inp.getInput());
			pricecheck = 1;
			break;
		}
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Price must be able and positive "); }
	} while (!checkFloor(inp));
	win->Show();
	do {
		inp.customInput(*win, "Enter max.price (999 if doesnt matter): ");

		if (stoi(inp.getInput()) != 999) {
			max = stoi(inp.getInput());
			pricecheck = 1;
			break;
		}
		if (!checkFloor(inp)) { win->writeText(win->GetY() + 2, "Price must be able and positive "); }
	} while (!checkFloor(inp));
	win->Show();

	checksNeeded += pricecheck;
	vector<int> props;

	for (int i = 0; i < properties.size(); i++) {
		checks = 0;
		Property& prop = properties[i];
		if (statuscheck) if (prop.getForRent() == statuscheck) {
			checks++;
		}
		if (!typecheck.empty()) if (typecheck == prop.getType()) checks++;
		if (roomcheck) if (roomcheck == prop.getRoomsCount()) checks++;
		if (pricecheck) {
			if (prop.getPrice() >= min && prop.getPrice() <= max) checks++;
		}
		if (checks == checksNeeded) props.push_back(i);
	}

	if (props.size() == 0) win->writeText(win->GetY() + 1, "No property found");

	win->SetHeight(props.size() * 7 + props.size());
	win->Show();

	for (int i = 0; i < props.size(); i++) {
		int _y = win->GetY() + 1 + (i * 8);
		printProperty(&properties[i], win->GetX(), _y);
	}
	inp.customInput(*win, "Type anythng to exit: ", win->GetHeight() - 1);
}