#pragma once
#include <string>
#include <vector>

using namespace std;

class User {
protected:
	string login, password, number;
	bool isBroker = false;
public:
	int countOfProp = 0;

	User(string login, string password, string number, bool isBroker) : login(login), password(password), number(number), isBroker(isBroker) {
	};
	~User() {};

	string getLogin() { return login; };
	string& getPassword() { return password; };
	string& getNumber() { return number; };
	bool getIsBroker() { return isBroker; };
	int getCountOfProp() { return countOfProp; };

	void setLogin(string login) { this->login = login; };
	void setPassword(string password) { this->password = password; };
	void increaseCountOfProp() { this->countOfProp ++; };

	bool operator==(User& other) {
		return this->getLogin() == other.getLogin() && this->getPassword() == other.getPassword() /*... и так далее для других полей*/;
	}
};