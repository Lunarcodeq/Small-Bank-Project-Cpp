#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
string fileName = "Clients.txt";

enum enMenues { Show = 1, Add = 2, Del = 3, Edit = 4, Find = 5, Exit = 6 };

struct stClientRecord {

	string AccountNumber;
	string Pincode;
	string FullName;
	string PhoneNumber;
	double Balance;
	bool MarkToDelete = false;
	bool MarkToEdit = false;

};

vector <stClientRecord> ClientsRecord();

stClientRecord AddClient() {

	vector <stClientRecord> records = ClientsRecord();

	stClientRecord Client;

	bool isExist = false;

	do {

		cout << "\nEnter Account Number: \n";
		getline(cin >> ws, Client.AccountNumber);

		for (stClientRecord& record : records) {

			if (record.AccountNumber == Client.AccountNumber) {

				cout << "Sorry, the client with the number [" << Client.AccountNumber << "] Already Exists. \n";
				isExist = true;
				break;
			}
			else {
				isExist = false;
				break;
			}

		}
	} while (isExist);

	if (!isExist) {

		cout << "Enter Pincode: \n";
		getline(cin, Client.Pincode);

		cout << "Enter Name: \n";
		getline(cin, Client.FullName);

		cout << "Enter Phone Number: \n";
		getline(cin, Client.PhoneNumber);

		cout << "Enter Balance: \n";
		cin >> Client.Balance;

	}


	return Client;
}

vector <stClientRecord> AddMoreClients() {

	char answer = 'n';
	stClientRecord ClientInfo;

	vector <stClientRecord> vClientsInfo;

	do {

		ClientInfo = AddClient();

		vClientsInfo.push_back(ClientInfo);

		cout << "Do you want to add more clients? [Y/N]\n";
		cin >> answer;

	} while (toupper(answer) == 'Y');

	return vClientsInfo;

}

string ConvertInfosToRecord(stClientRecord ClientInfo, string delim = "#//#") {

	string Record = "";

	Record += ClientInfo.AccountNumber + delim;
	Record += ClientInfo.Pincode + delim;
	Record += ClientInfo.FullName + delim;
	Record += ClientInfo.PhoneNumber + delim;
	Record += to_string(ClientInfo.Balance);

	return Record;
}

void UploadClientsRecord(vector <stClientRecord> ClientsInfo) {

	stClientRecord Records;
	
	fstream file;

	file.open(fileName, ios::out | ios::app);

	if (file.is_open()) {

		string line = "";

		for (stClientRecord& info : ClientsInfo) {

			line = ConvertInfosToRecord(info);
			file << line << endl;

		}

		file.close();
	}


}

void UploadClientsRecordWithoutDeleted(vector <stClientRecord> ClientsInfo) {

	stClientRecord Records;

	fstream file;

	file.open(fileName, ios::out);

	if (file.is_open()) {

		string line = "";

		for (stClientRecord& info : ClientsInfo) {

			if (info.MarkToDelete == false) {

				line = ConvertInfosToRecord(info);
				file << line << endl;

			}

		}

		file.close();
	}

}

vector <string> SplitRecordWord(string line, string delim = "#//#") {

	vector <string> vStringRecords;
	short pos = 0;

	string word = "";

	while ((pos = line.find(delim)) != std::string::npos) {

		word = line.substr(0, pos);
		vStringRecords.push_back(word);

		line.erase(0, pos + delim.length());
	}


	if (line != "") {
		vStringRecords.push_back(line);
	}

	return vStringRecords;
}

stClientRecord LoadLinesToRecord(vector <string> splittedLine) {

	stClientRecord Client;

	Client.AccountNumber = splittedLine[0];
	Client.Pincode = splittedLine[1];
	Client.FullName = splittedLine[2];
	Client.PhoneNumber = splittedLine[3];
	Client.Balance = stod(splittedLine[4]);
	
	return Client;

}

vector <stClientRecord> ClientsRecord() {

	vector <stClientRecord> Clients;
	vector <string> ClientsString;

	fstream file;

	file.open(fileName, ios::in);

	if (file.is_open()) {

		string line = "";
		stClientRecord record;

		while (getline(file, line)) {

			ClientsString = SplitRecordWord(line);
			record = LoadLinesToRecord(ClientsString);

			Clients.push_back(record);

		}
		

		file.close();
	}

	return Clients;

}

void PrintRecord(stClientRecord Record) {

	cout << "| " << setw(19) << left << Record.AccountNumber;
	cout << "| " << setw(16) << left << Record.Pincode;
	cout << "| " << setw(36) << left << Record.FullName;
	cout << "| " << setw(19) << left << Record.PhoneNumber;
	cout << "| " << setw(15) << left << Record.Balance;

}

void PrintDeleteClientRecord(stClientRecord record) {

	cout << "\nThe following are the client details: \n";

	cout << "-------------------------------------------------\n";

	cout << "Account Number          :" << record.AccountNumber << endl;
	cout << "Pincode          :" << record.Pincode << endl;
	cout << "Name          :" << record.FullName << endl;
	cout << "Phone        :" << record.PhoneNumber << endl;
	cout << "Account Balance         :" << record.Balance<< endl;

	cout << "-------------------------------------------------\n";

}

void DeleteClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "---------------------------------------\n";

}

vector <stClientRecord> ChooseClientToDelete() {

	DeleteClientScreen();

	vector <stClientRecord> AllClients = ClientsRecord();
	stClientRecord client;

	bool isExist = false;

	do {

		cout << "\n Enter Client Account Number: \n";
		getline(cin >> ws, client.AccountNumber);

		for (stClientRecord& record : AllClients) {

			if (client.AccountNumber == record.AccountNumber) {

				isExist = true;
				PrintDeleteClientRecord(record);

				char answer = 'n';

				cout << "\nAre you sure you want to delete this client ? [Y/N]\n";
				cin >> answer;

				if (toupper(answer) == 'Y') {

					record.MarkToDelete = true;

					cout << "\nClient Deleted Successfully. \n\n";

				}

				break;
			}

		}
	} while (!isExist);


	if (!isExist) {
		cout << "\nSorry, this client number is not exist. \n";
		isExist = false;
	}
	
	return AllClients;
}

void ShowClients() {

	vector <stClientRecord> cRecords = ClientsRecord();

	cout << "\n\t\t\t\t\tClient List (" << cRecords.size() << ") Client(s).\n";

	cout << "______________________________________________________________";
	cout << "__________________________________________________________\n\n";
	cout << "|" << setw(20) << left << " Account Number" << "|" << setw(17) << left << " Pincode";
	cout << "|" << setw(37) << left << " Client Name" << "|" << setw(20) << left << " Phone" << "|" << setw(16) << " Balance";
	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n";


	for (stClientRecord& record : cRecords) {

		PrintRecord(record);
		cout << endl;

	}


	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n\n\n";
}

void AddNewClients() {

	cout << "\n---------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------------\n";

	vector <stClientRecord> ClientsInfo = AddMoreClients();
	UploadClientsRecord(ClientsInfo);

}

void DeleteClient() {

	vector <stClientRecord> Clients = ChooseClientToDelete();

	UploadClientsRecordWithoutDeleted(Clients);

	return;

}

void MainMenue() {

	system("cls");

	enMenues menu;

	cout << "===========================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "===========================================\n";

	cout << "\t" << "[1] Show Clients List. \n";
	cout << "\t" << "[2] Add New Client. \n";
	cout << "\t" << "[3] Delete Client. \n";
	cout << "\t" << "[4] Update Client Info. \n";
	cout << "\t" << "[5] Find Client. \n";
	cout << "\t" << "[6] Exit. \n";

	cout << "==========================================\n";

	short answer;
	cout << "Choose what do you want to do ? [1-6]\n";
	cin >> answer;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Choose what do you want to do ? [1-6]\n";
		cin >> answer;
	}

	switch (answer) {

	case enMenues::Show:

		system("cls");
		ShowClients();
		system("pause");
		MainMenue();
		break;

	case enMenues::Add:

		system("cls");
		AddNewClients();
		system("pause");
		MainMenue();
		break;

	case enMenues::Del:

		system("cls");
		DeleteClient();
		system("pause");
		MainMenue();
		break;

	}

	system("pause>0");
}

int main() {

	MainMenue();

	return 0;
}