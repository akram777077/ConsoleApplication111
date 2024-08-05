// ConsoleApplication111.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;
const string myfiles = "1bank1.txt";
struct stclient {
	string accountnumber;
	string pincode;
	string name;
	string phone;
	double accountbalance;
	bool markdelete = false;
};
stclient readbank() {
	stclient client;
	cout << "enter accountnumber:";
	getline(cin >> ws, client.accountnumber);
	cout << "enter pincode:";
	getline(cin, client.pincode);
	cout << "enter name:";
	getline(cin, client.name);
	cout << "enter phone\n";
	getline(cin, client.phone);
	cout << "enter accountbalance: ";
	cin >> client.accountbalance;
	return client;
}
string convertrecordtoline(stclient client, string seperator = "#//#") {
	string stconvert = " ";
	stconvert = client.accountnumber + seperator;
	stconvert += client.pincode + seperator;
	stconvert += client.name + seperator;
	stconvert += client.phone + seperator;
	stconvert += to_string(client.accountbalance);
	return stconvert;
}
void organisefile(string file, string outputfile) {
	fstream myfileD;
	myfileD.open(file, ios::out | ios::app);
	if (myfileD.is_open())
	{
		myfileD << outputfile << endl;

		myfileD.close();
	}

}
void addnewclient() {
	stclient client;
	client = readbank();
	organisefile(myfiles, convertrecordtoline(client));
}
void addclient() {
	char addMORE = 'Y';
	do {
		system("cls");
		cout << " add new client:";
		addnewclient();
		cout << "do you want to add more client\n";
		cin >> addMORE;
	} while (toupper(addMORE) == 'Y');
}
vector<string>spstring(string s1, string delim) {
	vector<string>vstring;
	string sword;
	short pos = 0;
	while ((pos = s1.find(delim)) != std::string::npos) {
		sword = s1.substr(0, pos);
		if (sword != "") {
			vstring.push_back(sword);

		}
		s1.erase(0, pos + delim.length());
	}
	if (s1 != " ") {
		vstring.push_back(s1);
	}
	return vstring;
}
stclient convertrecord(string line, string seperator = "#//#") {
	stclient client;
	vector<string>vclientdata;
	vclientdata = spstring(line, seperator);
	client.accountnumber = vclientdata[0];
	client.pincode = vclientdata[1];
	client.name = vclientdata[2];
	client.phone = vclientdata[3];
	client.accountbalance = stod(vclientdata[4]);
	return client;
}
vector<stclient>loadfile(string filename) {
	vector<stclient>vclient;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open()) {
		string line;
		stclient client;
		while (getline(myfile, line)) {
			client = convertrecord(line);
			vclient.push_back(client);
		}
	}
	return vclient;

}
void printclientrecord(stclient client) {
	cout << "|" << setw(20) << left << client.accountnumber;
	cout << "|" << setw(20) << left << client.pincode;
	cout << "|" << setw(20) << left << client.name;
	cout << "|" << setw(20) << left << client.phone;
	cout << "|" << setw(20) << left << client.accountbalance;

}
void seperator() {
	cout << "\n---------------------------------------------------";
	cout << "---------------------------------------------------\n";

}
void printallclientdata(vector<stclient>vclient) {
	cout << "\n\t\t client list(" << vclient.size() << ")clients(s)";
	seperator();
	cout << "|" << left << setw(20) << "accountnumber";
	cout << "|" << left << setw(20) << "pincode";
	cout << "|" << left << setw(20) << "client name";
	cout << "|" << left << setw(20) << "phone";
	cout << "|" << left << setw(20) << "accountbalance";
	seperator();
	for (stclient client : vclient) {
		printclientrecord(client);

		seperator();


	}
}
void cleanscreen() {
	system("cls");
}
void preeKeyToContinue() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << " press any key to continue...";
	getchar();


}
void printmenue() {
	cout << "***************************************\n";
	cout << "\t \t MAIN MENUE SCREEN\t\t\n ";
	cout << "***************************************\n";
	cout << " \t [1] ADD New CLIENTS\n";
	cout << " \t [2] show client list\n";
	cout << "\t[3] delete client\n";
	cout << "\t[4] update client info\n";
	cout << "\t[5] find client\n";
	cout << "\t [6] exit\n";
	cout << "*****************************************\n";
}
void showborder(string text) {
	cout << "******************************************\n";
	cout << "\t\tt" << text << "\t\t\n";
	cout << "**********************************************\n";

}
void showclient() {
	vector<stclient>vclient = loadfile(myfiles);
	printallclientdata(vclient);
	preeKeyToContinue();
}
void printinfoclient(stclient client) {
	cout << "account number:" << client.accountnumber << endl;
	cout << "pincode:" << client.pincode << endl;
	cout << "name:" << client.name << endl;
	cout << "phone:" << client.phone << endl;
	cout << "account balance:" << client.accountbalance << endl;

}
bool findbyaccountnumber(string accountnumber, vector<stclient>vclient, stclient& client) {
	for (stclient c : vclient) {
		if (c.accountnumber == accountnumber) {
			client = c;
			return true;

		}
	}
	return false;
}
bool markclientbydelete(string accountnumber, vector<stclient>vclient, stclient& client) {
	for (stclient& c : vclient) {
		if (c.accountnumber == accountnumber) {
			c.markdelete = true;
			return true;
		}
	}
	return false;
}
vector<stclient>savemyfile(string filename, vector<stclient>vclient) {
	fstream myfile;
	myfile.open(filename, ios::out);
	string datafile;
	if (myfile.is_open()) {
		for (stclient c : vclient) {
			if (c.markdelete == false) {
				datafile = convertrecordtoline(c);
				myfile << datafile << endl;
			}
		}
		myfile.close();
	}
	return vclient;
}
//**bool deleteclient(string accountnumber, vector<stclient>vclient) {
	//stclient client;
	//char result = 'y';
	//if (findbyaccountnumber(accountnumber, vclient, client)) {
		//if (result == 'y' || result == 'Y') {
			//printinfoclient(client);
			//cout << "do you want to delete this ckient\n";
			//cin >> result;
			//markclientbydelete(accountnumber, vclient);
			//savemyfile(myfiles, vclient);
			//vclient = loadfile(myfiles);
			//cout << " delete successful\n";
			//return true;
		//}
		//else{
			//cout << "the account number (" << accountnumber << ") isn't found" << endl;
			//return false;
		//}
	//}

//}
string paccountnumber() {
	string accountnumber = "";
	cout << " eneter accountnumber\n";
	cin >> accountnumber;
	return accountnumber;
}
void deleteacount() {
	vector<stclient>vclient = loadfile(myfiles);
	string accountnumber = paccountnumber();
	//deleteclient(accountnumber, vclient);
}
void addnewclientScreen() {
	cleanscreen();
	showborder("add client");
	addclient();
}
void showallclient() {
	cleanscreen();
	showborder("show client");
	showclient();
}
void choose() {

	int number;
	do {fdf
		do {
			cleanscreen();
			printmenue();
			cout << " choose what do you want?[1 to 6]\n";
			cin >> number;

		} while (number < 1 || number >6);

		switch (number) {
		case 1:
			addnewclient();
			break;
		case 2:
			showallclient();
			break;
		case 3:

			break;
		default:

			showborder("exit");
			break;


		}
	} while (1);
}


int main() {
	choose();
}