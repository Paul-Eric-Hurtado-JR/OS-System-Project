//cpp file that containts the authenticateuser function
#include <iostream>

using namespace std;

//Function that gets the username and password and checks it with a hardcoed username and password
void authenticateUser() {
	string userName = "Paul";	//hardcoded username and password
	string passWord = "eaglesWin";
	string enteredName;			//entered username and password from user
	string enteredPassWord;

	while (true) {	//runs to see if the inputed username and password match the hardcoded username and password
		cout << "Username: " << endl;
		cin >> enteredName;
		cout << "Password: " << endl;
		cin >> enteredPassWord;

		if ((enteredName == userName) && (enteredPassWord == passWord)) {	//if this statment is entered it exits the loop
			cout << "Login was successful" << endl;
			return;
		}
		else {	//if enters statment error message is printed and runs through the loop again
			cout << "Login failed reenter username and password" << endl;;
		}
	}
}

