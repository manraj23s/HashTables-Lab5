
//========================================================================
//
//  Laboratory 10 Test Plan 1                                  Test10.cpp
//  
//  Name: Lab 10 test compilation
//  Version #: 1
//  Date Originally Written: 04/08/2021
//  Date Last Modified: 04/10/2021
//  Authors's Names: Manraj Singh (Programming & Documentation) &
//                   Corey Shimshock (Documentation & Programming)
//  Purpose: Class declarations for the implementation of test plan 1 to test 
//           implementation of Hash Table ADT with user commands and display.
//
//=========================================================================

#include <iostream>
#include <string>
#include "TableHash.cpp"
using namespace std;

//=========================================================================
//class for data of test
class DataTest {
public:
	//constructor
	DataTest();
	//set key function setter
	void setKey(const string& newKey);
	//get key function getter
	string getKey() const;
	//get value function getter
	int getValue() const;
	//hash table function
	static unsigned int hash(const string& str);

private:
	//key string
	string loginKey;
	//key value
	int value;
	//key count
	static int count;
};
//count intially 0
int DataTest::count = 0;

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table has value initialized with 0 count
///Inputs: No input
///Outputs: No output
DataTest::DataTest() : value(++count) {
}

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table has key instantiated
///Inputs: User input of key
///Outputs: Key for table to output
void DataTest::setKey(const string& newKey) {
	loginKey = newKey;
}

//=========================================================================

///Preconditions: Table must be valid and declared and key is set
///Postconditions: Get key for table to output and store
///Inputs: User input of key is then received for table in getter
///Outputs: Key returned
string DataTest::getKey() const {
	return loginKey;
}

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Table has key value instantiated
///Inputs: User input of key
///Outputs: Key for table to output
int DataTest::getValue() const {
	return value;
}

//=========================================================================

///Preconditions: Table must be valid and declared
///Postconditions: Value is equated to string
///Inputs: User input of key value
///Outputs: Outputted value returned for table
unsigned int DataTest::hash(const string& str) {
	//value instantiated as 0
	unsigned int val = 0;

	//for every index of string's length, instantiate to val
	for (int i = 0; i < str.length(); ++i) 
		val += str[i];

	//return val
	return val;
}

//=========================================================================

void print_help() {
	cout << endl << "Commands:" << endl;
	cout << "**===================================================**" << endl;
	cout << "*=  H   : Help (displays this message)               =*" << endl;
	cout << "=*  +x  : Insert (or update) data item with key x    *=" << endl;
	cout << "*=  -x  : Remove the data element with the key x     =*" << endl;
	cout << "=*  ?x  : Retrieve the data element with the key x   *=" << endl;
	cout << "*=  E   : Empty table?                               =*" << endl;
	cout << "=*  C   : Clear the table                            *=" << endl;
	cout << "*=  Q   : Quit the test program                      =*" << endl;
	cout << "**===================================================**" << endl;
}

//=========================================================================

int main(int argc, char** argv) {
	//table has length of 7
	TableHash<DataTest, string> table(7);

	print_help();

	//while user does not exit
	do {
		//ask for user command
		cout << endl << "Command: ";
		char cmd;
		cin >> cmd;

		//if command is + or ? or -, use string for key
		DataTest item;
		if (cmd == '+' || cmd == '?' || cmd == '-') {
			string key;
			cin >> key;
			item.setKey(key);
		}

		//switch for commands
		switch (cmd) {
		//output structure
		case 'H':
		case 'h':
			print_help();
			break;

			//+ = insert
		case '+':
			table.addValue(item);
			cout << "Inserted data item with key ("
				<< item.getKey() << ") and value ("
				<< item.getValue() << ")" << endl;
			break;

			//- = remove
		case '-':
			if (table.deleteValue(item.getKey())) {
				cout << "Removed data item with key ("
					<< item.getKey() << ")" << endl;
			}
			else {
				cout << "Could not remove data item with key ("
					<< item.getKey() << ")" << endl;
			}
			break;

			//? = retrieve
		case '?':
			if (table.fetchValue(item.getKey(), item)) {
				cout << "Retrieved data item with key ("
					<< item.getKey() << ") and value ("
					<< item.getValue() << ")" << endl;
			}
			else {
				cout << "Could not retrieve data item with key ("
					<< item.getKey() << ")" << endl;
			}
			break;

			//c = clear table
		case 'C':
		case 'c':
			cout << "Clear the hash table" << endl;
			table.wipeClear();
			break;

			//e = empty table bool ask
		case 'E':
		case 'e':
			cout << "Hash table is "
				<< (table.isTableEmpty() ? "" : "NOT")
				<< " empty" << endl;
			break;

			//q = exit program
		case 'Q':
		case 'q':
			return 0;

		default:
			cout << "Invalid command!" << endl;
		}
	} while (1);

	return 0;
}

//=========================================================================