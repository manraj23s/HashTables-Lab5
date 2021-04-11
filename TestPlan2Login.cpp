
//========================================================================
//
//  Laboratory 10 Test Plan 2                                  Login.cpp
//  
//  Name: Lab 10 Ex 1
//  Version #: 1
//  Date Originally Written: 04/08/2021
//  Date Last Modified: 04/10/2021
//  Authors's Names: Manraj Singh (Programming & Documentation) &
//                   Corey Shimshock (Documentation & Programming)
//  Purpose: Class declarations for the implementation of password.dat 
//           to read file, check from user to authenticate logins, 
//           and hold info in a hash table.
//
//========================================================================

#include <iostream>
#include <string>
#include <fstream>
#include "TableHash.cpp"
using namespace std;

//========================================================================
class DataTest {
public:
	//constructor
	DataTest();
	//set key string
	void setKey(const string& newKey);
	//set password string
	void setPassword(const string& newPassword);
	//get key string
	string getKey() const;
	//get password string
	string getPassword() const;
	//hash
	static unsigned int hash(const string& str);

private:
	string loginKey;
	string passwordKey;
	static int count;
};

int DataTest::count = 0;

//=========================================================================

///Preconditions: Program must be valid
///Postconditions: Constructor instantiated with values of 0
///Inputs: None
///Outputs: None, default constructor
DataTest::DataTest()
{
	loginKey = "0";
	passwordKey = "0";
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Login key is instantiated to default 0 until user cmd
///Inputs: None
///Outputs: None
void DataTest::setKey(const string& newKey)
{
	loginKey = newKey;
}

//=========================================================================

///Preconditions: Table must be declared and valid
///Postconditions: Password key is instantiated to default 0 until user cmd
///Inputs: None
///Outputs: None
void DataTest::setPassword(const string& newPassword)
{
	passwordKey = newPassword;
}

//=========================================================================

///Preconditions: Password key must be set
///Postconditions: Password is retrieved
///Inputs: User input of password
///Outputs: Password outputted for table
string DataTest::getPassword() const
{
	return passwordKey;
}

//=========================================================================

///Preconditions: Login key must be set
///Postconditions: Login is retrieved
///Inputs: User input of login
///Outputs: Login outputted for table
string DataTest::getKey() const
{
	return loginKey;
}

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Value is equated to string
///Inputs: User input of key value
///Outputs: Outputted value returned for table
unsigned int DataTest::hash(const string& str)
{
	//value instantiated as 0
	unsigned int val = 0;

	//for every index of string's length, instantiate to val
	for (int i = 0; i < str.length(); ++i)
		val += str[i];

	//return val
	return val;
}

//=========================================================================

int main()
{
	//variables for login and password
	string loginUserName;
    string password;
	//account info
	DataTest fullCredentials;
	//file i/o stuff
	ifstream passwordTextFile;
	//instantiate table with 8 values
	TableHash< DataTest, string> accountTable(8);

	//open file and check if file good
	passwordTextFile.clear();
	passwordTextFile.open("password.dat");
	while (passwordTextFile.good())
	{
		passwordTextFile >> loginUserName;
		passwordTextFile >> password;
		//while file good, set values from text
		if (passwordTextFile.good())
		{
			fullCredentials.setKey(loginUserName);
			fullCredentials.setPassword(password);
			accountTable.addValue(fullCredentials);
		}
	}
	//show table structure
	cout << "Stored login usernames in hash table: " << endl;
	accountTable.showStructure();

	//output user input
	cout << "\n==========================================" 
		<< "\nEnter username and password credentials!" << endl
		<< "==========================================" << endl << endl;
	cout << "Enter Username: ";
	//while on login step, enter password and check if credentials match text
	while (cin >> loginUserName)
	{
		//ask user to enter password
		cout << "Enter Password: ";
		cin >> password;
		//if both are given, check if either are in file
		if (accountTable.fetchValue(loginUserName, fullCredentials))
		{
			//if password is same as text, then success, else failure
			if (fullCredentials.getPassword() == password)
				cout << "Authentication successful!" << endl << endl;
			else
				cout << "Authentication failure!" << endl << endl;
		}
		//else failure if text not equal to user input
		else
			cout << "Authentication failure!" << endl << endl;
		//prompt for username again
		cout << "Enter username: ";
	}
	return 0;
}

//=========================================================================