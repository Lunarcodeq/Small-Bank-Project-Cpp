#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
string fileName = "Clients.txt";

enum enMenues { Show = 1, Add = 2, Del = 3, Edit = 4, Find = 5, Trans = 6, Exit = 7 };

enum enTransctionsMenu { Deposite = 1, Withdraw = 2, Total = 3, Goback = 4 };

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

void TransactionMenue();

void MainMenue();

short ReadAnswer(string message) {
	short answer = 0;

	cout << message << endl;
	cin >> answer;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<streamsize>::max(), '\n');

		cout << message << endl;
		cin >> answer;
	}

	return answer;
}

stClientRecord ReadClientNumber() {
	stClientRecord client;

	cout << "Please enter Account number\n";
	getline(cin >> ws, client.AccountNumber);

	return client;
}

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
		cout << endl;

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

void PrintTotalBalanceRecord(stClientRecord Record) {

	cout << "| " << setw(19) << left << Record.AccountNumber;
	cout << "| " << setw(49) << left << Record.FullName;
	cout << "| " << setw(45) << left << Record.Balance;

}

void ShowClientRecord(stClientRecord record) {

	cout << "\nThe following are the client details: \n";

	cout << "-------------------------------------------------\n";

	cout << "Account Number          :" << record.AccountNumber << endl;
	cout << "Pincode          :" << record.Pincode << endl;
	cout << "Name          :" << record.FullName << endl;
	cout << "Phone        :" << record.PhoneNumber << endl;
	cout << "Account Balance         :" << record.Balance<< endl;

	cout << "-------------------------------------------------\n\n";

}

void MakeDeposite(stClientRecord& client, double Amount) {

	client.Balance += Amount;

}

void MakeWithdraw(stClientRecord& client, double Amount) {

	client.Balance += (Amount * -1);

}

void DeleteClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tDelete Client Screen\n";
	cout << "---------------------------------------\n";

}

void UpdateClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "---------------------------------------\n";

}

void FindClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------------\n\n";

}

void ShowDepositeTaskScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tDeposite Screen\n";
	cout << "---------------------------------------\n\n";

}

void ShowWithdrawTaskScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tWithdraw Screen\n";
	cout << "---------------------------------------\n\n";

}

void DepoisteTask() {

	ShowDepositeTaskScreen();

	stClientRecord Client = ReadClientNumber();

	vector <stClientRecord> Records = ClientsRecord();

	bool isFound = false;

	for (stClientRecord& record : Records) {

		if (record.AccountNumber == Client.AccountNumber) {

			ShowClientRecord(record);

			isFound = true;

			double amount = (double)ReadAnswer("Please enter the Amount: ");

			char answer = 'n';
			cout << "Are you sure you want to perform this task ? [Y/N]\n";
			cin >> answer;

			cout << endl;

			if (toupper(answer) == 'Y') {
				MakeDeposite(record, amount);
				UploadClientsRecordWithoutDeleted(Records);
				break;
			}

		}

	}

	if (!isFound) {
		cout << "\nSorry, the Client with the number [" << Client.AccountNumber << "] is not exist. \n\n\n";
		isFound = false;
	}

}

void WithdrawTask() {

	ShowWithdrawTaskScreen();

	stClientRecord Client = ReadClientNumber();

	vector <stClientRecord> Records = ClientsRecord();

	bool isFound = false;

	for (stClientRecord& record : Records) {

		if (record.AccountNumber == Client.AccountNumber) {

			ShowClientRecord(record);

			isFound = true;

			double amount = (double)ReadAnswer("Please enter the Amount: ");

			char answer = 'n';
			cout << "Are you sure you want to perform this task ? [Y/N]\n";
			cin >> answer;

			cout << endl;

			if (toupper(answer) == 'Y') {
				MakeWithdraw(record, amount);
				UploadClientsRecordWithoutDeleted(Records);
				break;
			}

		}

	}

	if (!isFound) {
		cout << "\nSorry, the Client with the number [" << Client.AccountNumber << "] is not exist. \n\n\n";
		isFound = false;
	}

}

void TotalBalance() {

	vector <stClientRecord> cRecords = ClientsRecord();

	int sum = 0;

	cout << "\n\t\t\t\t\tClient List (" << cRecords.size() << ") Client(s).\n";

	cout << "______________________________________________________________";
	cout << "__________________________________________________________\n\n";
	cout << "|" << setw(20) << left << " Account Number";
	cout << "|" << setw(50) << left << " Client Name" << "|" << setw(45) << left << " Balance";
	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n";


	for (stClientRecord& record : cRecords) {

		PrintTotalBalanceRecord(record);
		sum += record.Balance;
		cout << endl;

	}


	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n";
	cout << "\t\t\t\t\tTotal Balance: " << sum << endl << endl;

}

void performTransactionsMenue(enTransctionsMenu task) {

	switch (task) {

	case enTransctionsMenu::Deposite:

		system("cls");
		DepoisteTask();
		system("pause");
		TransactionMenue();
		break;

	case enTransctionsMenu::Withdraw:

		system("cls");
		WithdrawTask();
		system("pause");
		TransactionMenue();
		break;

	case enTransctionsMenu::Total:

		system("cls");
		TotalBalance();
		system("pause");
		TransactionMenue();
		break;

	case enTransctionsMenu::Goback:

		system("cls");
		MainMenue();
		system("pause");
	}

}

void TransactionsMenueScreen() {

	cout << "===========================================\n";
	cout << "\tTransactions Menue Screen\n";
	cout << "===========================================\n";

	cout << "\t" << "[1] Deposite. \n";
	cout << "\t" << "[2] Withdraw. \n";
	cout << "\t" << "[3] Total Balance. \n";
	cout << "\t" << "[4] Main Menue. \n";

	cout << "==========================================\n\n";

}

vector <stClientRecord> ChooseClientToDelete() {

	vector <stClientRecord> AllClients = ClientsRecord();
	stClientRecord client;

	bool isExist = false;


	cout << "\n Enter Client Account Number: \n";
	getline(cin >> ws, client.AccountNumber);

	for (stClientRecord& record : AllClients) {

		if (client.AccountNumber == record.AccountNumber) {

			isExist = true;
			ShowClientRecord(record);

			char answer = 'n';

			cout << "\nAre you sure you want to delete this client ? [Y/N]\n";
			cin >> answer;

			cout << endl << endl;

			if (toupper(answer) == 'Y') {

				record.MarkToDelete = true;

				cout << "\nClient Deleted Successfully. \n\n";

			}

			break;
		}

	}


	if (!isExist) {
		cout << "\nSorry, the Client with the number [" << client.AccountNumber << "] is not exist. \n\n\n";
		isExist = false;
	}
	
	return AllClients;
}

vector <stClientRecord> ChooseClientToUpdate() {;

	vector <stClientRecord> AllClients = ClientsRecord();
	stClientRecord client;

	bool isExist = false;



	cout << "\n Enter Client Account Number: \n";
	getline(cin >> ws, client.AccountNumber);

	for (stClientRecord& record : AllClients) {

		if (client.AccountNumber == record.AccountNumber) {

			isExist = true;
			ShowClientRecord(record);

			char answer = 'n';

			cout << "\nAre you sure you want to update this client ? [Y/N]\n";
			cin >> answer;
			cout << endl << endl;

			if (toupper(answer) == 'Y') {

				record.MarkToEdit = true;

			}

			break;
		}

	}
	


	if (!isExist) {
		cout << "\nSorry, the Client with the number [" << client.AccountNumber << "] is not exist. \n\n\n";
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

	DeleteClientScreen();

	vector <stClientRecord> Clients = ChooseClientToDelete();

	UploadClientsRecordWithoutDeleted(Clients);

	//Refresh:
	Clients = ClientsRecord();

	return;

}

void UpdateClient() {

	UpdateClientScreen();

	vector <stClientRecord> ClientToUpdate = ChooseClientToUpdate();

	for (stClientRecord& Client : ClientToUpdate) {

		if (Client.MarkToEdit == true) {

			cout << "\nEnter Pincode: \n";
			getline(cin >> ws, Client.Pincode);

			cout << "Enter Name: \n";
			getline(cin, Client.FullName);

			cout << "Enter Phone Number: \n";
			getline(cin, Client.PhoneNumber);

			cout << "Enter Balance: \n";
			cin >> Client.Balance;

			cout << "\nClient Infos Updated Successfully. \n\n";
		}

	}

	UploadClientsRecordWithoutDeleted(ClientToUpdate);

}

void FindClient() {

	FindClientScreen();

	vector <stClientRecord> Clients = ClientsRecord();
	stClientRecord Client;

	bool isFound = false;

	cout << "Enter Account Number: \n";
	getline(cin >> ws, Client.AccountNumber);

	for (stClientRecord& record : Clients) {

		if (Client.AccountNumber == record.AccountNumber) {

			isFound = true;
			ShowClientRecord(record);

		}

	}

	if (!isFound) {
		cout << "\nSorry, the client with number [" << Client.AccountNumber << "] is Not Found.\n\n";
		}

}

void TransactionMenue() {

	system("cls");

	TransactionsMenueScreen();

	performTransactionsMenue((enTransctionsMenu)ReadAnswer("Choose what do you want to do ? [1-4] "));

}

void ExitProgram() {

	cout << "\n---------------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "---------------------------------------\n";

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
	cout << "\t" << "[6] Transactions. \n";
	cout << "\t" << "[7] Exit. \n";

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

	case enMenues::Edit:

		system("cls");
		UpdateClient();
		system("pause");
		MainMenue();
		break;

	case enMenues::Find:

		system("cls");
		FindClient();
		system("pause");
		MainMenue();
		break;

	case enMenues::Trans:

		system("cls");
		TransactionMenue();
		system("pause");
		break;

	case enMenues::Exit:
		system("cls");
		ExitProgram();
		system("pause>0");
		break;
	}

	system("pause>0");
}

int main() {

	MainMenue();

	return 0;
}