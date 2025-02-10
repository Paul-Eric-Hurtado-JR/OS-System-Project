#include <iostream>

using namespace std;

string authenticateUser(string uName, string pWord) {
	string userName = "Paul";
	string passWord = "eaglesWin";

	if ((uName == userName) && (pWord == passWord)) {
		return "Login was successful";
	}
	else {
		return "Login failed check username or password";
	}
}