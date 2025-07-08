#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;
string fileName = "Clients.txt";
string fileUsers = "Users.txt";

enum enMenues { Show = 1, Add = 2, Del = 3, Edit = 4, Find = 5, Trans = 6, Mange = 7, Logout = 8 };

enum enTransctionsMenu { Deposite = 1, Withdraw = 2, Total = 3, Goback = 4 };

enum enManageUsersMenu { List = 1, UserAdd = 2, UserDel = 3, UserEdit = 4, UserFind = 5, Main = 6 };

struct stClientRecord {

	string AccountNumber;
	string Pincode;
	string FullName;
	string PhoneNumber;
	double Balance;
	bool MarkToDelete = false;
	bool MarkToEdit = false;

};

struct stUsers {

	string Username;
	string Password;
	short Permissions = 0;
	bool MarkToUpdate = false;
	bool MarkToDelete = false;

};

vector <stClientRecord> ClientsRecord();

void MangeUsersMenu(stUsers user);

void TransactionMenue(stUsers user);

void MainMenue(stUsers user);

vector <stUsers> UsersRecord();

void Login();

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

stUsers AddPermissions(stUsers& User) {

	char answer = 'n';

	cout << "\nDo you want to give this user all the permissions ? ";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions = -1;
		return User;
	}

	cout << "\nList Clients ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 1);
	}

	answer = 'n';

	cout << "\nAdd Clients ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 2);
	}

	answer = 'n';

	cout << "\nDelete Clients ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 3);
	}

	answer = 'n';

	cout << "\nUpdate Clients ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 4);
	}

	answer = 'n';

	cout << "\nFind Clients ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 5);
	}

	cout << "\nTransactions Menu ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 6);
	}

	cout << "\nManage Users ? [Y/N]";
	cin >> answer;
	if (toupper(answer) == 'Y') {
		User.Permissions += (1 << 7);
	}

	return User;

}

stUsers AddUser() {

	vector <stUsers> records = UsersRecord();

	stUsers User;

	bool isExist = false;

	do {

		cout << "\nEnter Username: \n";
		getline(cin >> ws, User.Username);

		for (stUsers& record : records) {

			if (record.Username == User.Username) {

				cout << "Sorry, the client with the number [" << User.Username<< "] Already Exists. \n";
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

		cout << "Enter Password: \n";
		getline(cin, User.Password);

		cout << "Choose the permissions you want to give to this user: \n";

		AddPermissions(User);

	}


	return User;
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

vector <stUsers> AddMoreUsers() {

	char answer = 'n';
	stUsers UserInfo;

	vector <stUsers> vUsersInfo;

	do {

		UserInfo = AddUser();

		vUsersInfo.push_back(UserInfo);

		cout << "Do you want to add more users? [Y/N]\n";
		cin >> answer;
		cout << endl;

	} while (toupper(answer) == 'Y');

	return vUsersInfo;

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

string ConvertUsersInfosToRecord(stUsers ClientInfo, string delim = "#//#") {

	string Record = "";

	Record += ClientInfo.Username + delim;
	Record += ClientInfo.Password + delim;
	Record += to_string(ClientInfo.Permissions);

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

void UploadUsersRecord(vector <stUsers> UsersInfo) {

	stUsers Records;

	fstream file;

	file.open(fileUsers, ios::out | ios::app);

	if (file.is_open()) {

		string line = "";

		for (stUsers& info : UsersInfo) {

			line = ConvertUsersInfosToRecord(info);
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

void UploadUsersRecordWithoutDeleted(vector <stUsers> UsersInfo) {

	stUsers Records;

	fstream file;

	file.open(fileUsers, ios::out);

	if (file.is_open()) {

		string line = "";

		for (stUsers& info : UsersInfo) {

			if (info.MarkToDelete == false) {

				line = ConvertUsersInfosToRecord(info);
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

stUsers LoadLinesToRecordUser(vector <string> splittedLine) {

	stUsers User;

	User.Username = splittedLine[0];
	User.Password = splittedLine[1];
	User.Permissions = stoi(splittedLine[2]);

	return User;

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

vector <stUsers> UsersRecord() {

	vector <stUsers> Users;
	vector <string> UsersString;

	fstream file;

	file.open(fileUsers, ios::in);

	if (file.is_open()) {

		string line = "";
		stUsers record;

		while (getline(file, line)) {

			UsersString = SplitRecordWord(line);
			record = LoadLinesToRecordUser(UsersString);

			Users.push_back(record);

		}


		file.close();
	}

	return Users;

}

void PrintRecord(stClientRecord Record) {

	cout << "| " << setw(19) << left << Record.AccountNumber;
	cout << "| " << setw(16) << left << Record.Pincode;
	cout << "| " << setw(36) << left << Record.FullName;
	cout << "| " << setw(19) << left << Record.PhoneNumber;
	cout << "| " << setw(15) << left << Record.Balance;

}

void PrintUserRecord(stUsers Record) {

	cout << "| " << setw(19) << left << Record.Username;
	cout << "| " << setw(19) << left << Record.Password;
	cout << "| " << setw(19) << left << Record.Permissions;

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

void ShowUserRecord(stUsers record) {

	cout << "\nThe following are the user details: \n";

	cout << "-------------------------------------------------\n";

	cout << "Username             :" << record.Username << endl;
	cout << "Password             :" << record.Password << endl;
	cout << "Permissions          :" << record.Permissions << endl;

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

void DeleteUserScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tDelete User Screen\n";
	cout << "---------------------------------------\n";

}

void UpdateClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tUpdate Client Screen\n";
	cout << "---------------------------------------\n";

}

void UpdateUserScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tUpdate User Screen\n";
	cout << "---------------------------------------\n";

}

void FindClientScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tFind Client Screen\n";
	cout << "---------------------------------------\n\n";

}

void FindUserScreen() {

	cout << "\n---------------------------------------\n";
	cout << "\tFind User Screen\n";
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

void LoginScreen() {

	cout << "\n---------------------------------\n";
	cout << "\tLogin Screen\n";
	cout << "---------------------------------\n";

}

void ErrorScreen(stUsers user) {

	cout << "\n---------------------------------\n";
	cout << "\tAccess Denied :-(\n";
	cout << "---------------------------------\n";
	cout << "You don't have access to this feature, pleaase\n";
	cout << "Contact you're admin for more help\n\n\n";

	system("pause");
	MainMenue(user);

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

void performTransactionsMenue(enTransctionsMenu task, stUsers user) {

	switch (task) {

	case enTransctionsMenu::Deposite:

		system("cls");
		DepoisteTask();
		system("pause");
		TransactionMenue(user);
		break;

	case enTransctionsMenu::Withdraw:

		system("cls");
		WithdrawTask();
		system("pause");
		TransactionMenue(user);
		break;

	case enTransctionsMenu::Total:

		system("cls");
		TotalBalance();
		system("pause");
		TransactionMenue(user);
		break;

	case enTransctionsMenu::Goback:

		system("cls");
		MainMenue(user);
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

void ManageUsersScreen() {

	cout << "===========================================\n";
	cout << "\tManage Users Menu Screen\n";
	cout << "===========================================\n";

	cout << "\t" << "[1] List Users. \n";
	cout << "\t" << "[2] Add User. \n";
	cout << "\t" << "[3] Delete User. \n";
	cout << "\t" << "[4] Update User. \n";
	cout << "\t" << "[5] Find User. \n";
	cout << "\t" << "[6] Main Menu. \n";

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

				cout << "\nUser Deleted Successfully. \n\n";

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

vector <stUsers> ChooseUserToDelete(stUsers Admin) {

	vector <stUsers> AllUsers = UsersRecord();
	stUsers user;

	bool isExist = false;


	cout << "\n Enter User Username: \n";
	getline(cin >> ws, user.Username);

	for (stUsers& record : AllUsers) {

		if (user.Username == "Admin") {

			system("cls");
			cout << "\n-----------------------------------------\n";
			cout << "Sorry you cannot delete this user\n";
			cout << "This user is the admin of the project.";
			cout << "\n-----------------------------------------\n\n\n";
			system("pause");
			MangeUsersMenu(Admin);
			
		}

		if (user.Username == record.Username) {

			isExist = true;
			ShowUserRecord(record);

			char answer = 'n';

			cout << "\nAre you sure you want to delete this client ? [Y/N]\n";
			cin >> answer;

			cout << endl << endl;

			if (toupper(answer) == 'Y') {

				record.MarkToDelete = true;

				cout << "\nUser Deleted Successfully. \n\n";

			}

			break;
		}

	}


	if (!isExist) {
		cout << "\nSorry, the User with the username [" << user.Username << "] is not exist. \n\n\n";
		isExist = false;
	}
	
	return AllUsers;
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

vector <stUsers> ChooseUserToUpdate(stUsers Admin) {
	;

	vector <stUsers> AllUsers = UsersRecord();
	stUsers user;

	bool isExist = false;



	cout << "\n Enter User Username: \n";
	getline(cin >> ws, user.Username);

	for (stUsers& record : AllUsers) {

		if (user.Username == "Admin") {

			system("cls");
			cout << "\n-----------------------------------------\n";
			cout << "Sorry you cannot delete this user\n";
			cout << "This user is the admin of the project.";
			cout << "\n-----------------------------------------\n\n\n";
			system("pause");
			MangeUsersMenu(Admin);

		}

		if (user.Username == record.Username) {

			isExist = true;
			ShowUserRecord(record);

			char answer = 'n';

			cout << "\nAre you sure you want to update this user ? [Y/N]\n";
			cin >> answer;
			cout << endl << endl;

			if (toupper(answer) == 'Y') {

				record.MarkToUpdate = true;

			}

			break;
		}

	}



	if (!isExist) {
		cout << "\nSorry, the User with the username [" << user.Username << "] is not exist. \n\n\n";
		isExist = false;
	}

	return AllUsers;
}

bool ValidateLogin(stUsers& UserToCheck) {

	vector <stUsers> vUsers = UsersRecord();

	for (stUsers& user : vUsers) {

		if (user.Username == UserToCheck.Username && user.Password == UserToCheck.Password) {

			UserToCheck = user;
			return true;

		}

	}
	return false;
}

stUsers UserLogin(stUsers& user) {

	cout << "Please enter username ? ";
	cin >> user.Username;
	cout << "Plesse enter password ? ";
	cin >> user.Password;

	while (!ValidateLogin(user)) {
		cout << "\nInvalid Username and Paswword, try again.\n";

		cout << "Please enter username ? ";
		cin >> user.Username;
		cout << "Plesse enter password ? ";
		cin >> user.Password;
	}

	if (ValidateLogin(user)) {
		system("cls");
		MainMenue(user);
	}

	return user;
}

void ShowClients(stUsers user) {

	if ((user.Permissions & 1 << 1) == 0) {
		system("cls");
		ErrorScreen(user);
	}

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

void ShowUsers() {

	vector <stUsers> cRecords = UsersRecord();

	cout << "\n\t\t\t\t\tClient List (" << cRecords.size() << ") User(s).\n";

	cout << "______________________________________________________________";
	cout << "__________________________________________________________\n\n";
	cout << "|" << setw(20) << left << " Username" << "|" << setw(20) << left << " Password";
	cout << "|" << setw(20) << left << " Permissions";
	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n";


	for (stUsers& user : cRecords) {

		PrintUserRecord(user);
		cout << endl;

	}


	cout << "\n______________________________________________________________";
	cout << "__________________________________________________________\n\n\n\n";
}

void AddNewClients(stUsers user) {

	if ((user.Permissions & 1 << 2) == 0) {
		system("cls");
		ErrorScreen(user);
	}

	cout << "\n---------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "---------------------------------------\n";

	vector <stClientRecord> ClientsInfo = AddMoreClients();
	UploadClientsRecord(ClientsInfo);

}

void AddNewUsers() {

	cout << "\n---------------------------------------\n";
	cout << "\tAdd New Users Screen\n";
	cout << "---------------------------------------\n";

	vector <stUsers> UsersInfo = AddMoreUsers();
	UploadUsersRecord(UsersInfo);

}

void DeleteClient(stUsers user) {

	if ((user.Permissions & 1 << 3) == 0) {
		system("cls");
		ErrorScreen(user);
	}

	DeleteClientScreen();

	vector <stClientRecord> Clients = ChooseClientToDelete();

	UploadClientsRecordWithoutDeleted(Clients);

	//Refresh:
	Clients = ClientsRecord();

	return;

}

void DeleteUser(stUsers user) {

	DeleteUserScreen();

	vector <stUsers> Users = ChooseUserToDelete(user);

	UploadUsersRecordWithoutDeleted(Users);

	//Refresh:
	Users = UsersRecord();

	return;

}

void UpdateClient(stUsers user) {

	if ((user.Permissions & 1 << 4) == 0) {
		system("cls");
		ErrorScreen(user);
	}

	UpdateClientScreen();

	vector <stClientRecord> ClientToUpdate = ChooseClientToUpdate();

	for (stClientRecord& Client : ClientToUpdate) {

		if (Client.MarkToEdit == true) {

			cout << "Enter Pincode: \n";
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

void UpdateUser(stUsers user) {

	UpdateClientScreen();

	vector <stUsers> UserToUpdate = ChooseUserToUpdate(user);

	for (stUsers& User : UserToUpdate) {

		if (User.MarkToUpdate == true) {

			cout << "Enter Password: \n";
			getline(cin >> ws, User.Password);

			User.Permissions = 0;
			User = AddPermissions(User);

			cout << "\nClient Infos Updated Successfully. \n\n";
		}

	}

	UploadUsersRecordWithoutDeleted(UserToUpdate);

}

void FindClient(stUsers user) {

	if ((user.Permissions & 1 << 5) == 0) {
		system("cls");
		ErrorScreen(user);
	}

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

void FindUser() {

	FindUserScreen();

	vector <stUsers> Users = UsersRecord();
	stUsers User;

	bool isFound = false;

	cout << "Enter Username: \n";
	getline(cin >> ws, User.Username);

	for (stUsers& record : Users) {

		if (User.Username == record.Username) {

			isFound = true;
			ShowUserRecord(record);

		}

	}

	if (!isFound) {
		cout << "\nSorry, the user with username [" << User.Username << "] is Not Found.\n\n";
	}

}

void performMangeUsersMenu(enManageUsersMenu users, stUsers user) {

	switch (users) {

	case enManageUsersMenu::List:

		system("cls");
		ShowUsers();
		system("pause");
		MangeUsersMenu(user);
		break;

	case enManageUsersMenu::UserAdd:

		system("cls");
		AddNewUsers();
		system("pause");
		MangeUsersMenu(user);
		break;

	case enManageUsersMenu::UserDel:

		system("cls");
		DeleteUser(user);
		system("pause");
		MangeUsersMenu(user);
		break;

	case enManageUsersMenu::UserEdit:

		system("cls");
		UpdateUser(user);
		system("pause");
		MangeUsersMenu(user);
		break;

	case enManageUsersMenu::UserFind:

		system("cls");
		FindUser();
		system("pause");
		MangeUsersMenu(user);
		break;

	case enManageUsersMenu::Main:

		system("cls");
		MainMenue(user);
		system("pause");
		break;

	}

}

void TransactionMenue(stUsers user) {

	if ((user.Permissions & 1 << 6) == 0) {
		system("cls");
		ErrorScreen(user);
	}

	system("cls");

	TransactionsMenueScreen();

	performTransactionsMenue((enTransctionsMenu)ReadAnswer("Choose what do you want to do ? [1-4] "), user);

}

void MangeUsersMenu(stUsers user) {

	if ((user.Permissions & 1 << 7) == 0) {
		system("cls");
		ErrorScreen(user);
	}

	system("cls");

	ManageUsersScreen();

	performMangeUsersMenu((enManageUsersMenu)ReadAnswer("Choose what you want to do ? [1-6]"), user);

}

void ExitProgram() {

	cout << "\n---------------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "---------------------------------------\n";

}

void MainMenue(stUsers user) {

	system("cls");

	enMenues menu;

	cout << "===========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "===========================================\n";

	cout << "\t" << "[1] Show Clients List. \n";
	cout << "\t" << "[2] Add New Client. \n";
	cout << "\t" << "[3] Delete Client. \n";
	cout << "\t" << "[4] Update Client Info. \n";
	cout << "\t" << "[5] Find Client. \n";
	cout << "\t" << "[6] Transactions. \n";
	cout << "\t" << "[7] Mange Users Menu. \n";
	cout << "\t" << "[8] Logout. \n";

	cout << "==========================================\n";

	short answer;
	cout << "Choose what do you want to do ? [1-8]\n";
	cin >> answer;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Choose what do you want to do ? [1-8]\n";
		cin >> answer;
	}

	switch (answer) {

	case enMenues::Show:

		system("cls");
		ShowClients(user);
		system("pause");
		MainMenue(user);
		break;

	case enMenues::Add:

		system("cls");
		AddNewClients(user);
		system("pause");
		MainMenue(user);
		break;

	case enMenues::Del:

		system("cls");
		DeleteClient(user);
		system("pause");
		MainMenue(user);
		break;

	case enMenues::Edit:

		system("cls");
		UpdateClient(user);
		system("pause");
		MainMenue(user);
		break;

	case enMenues::Find:

		system("cls");
		FindClient(user);
		system("pause");
		MainMenue(user);
		break;

	case enMenues::Trans:

		system("cls");
		TransactionMenue(user);
		system("pause");
		break;

	case enMenues::Mange:

		system("cls");
		MangeUsersMenu(user);
		system("pause");
		break;

	case enMenues::Logout:
		system("cls");
		Login();
		system("pause>0");
		break;
	}

	system("pause>0");
}

void Login() {

	stUsers user;

	LoginScreen();

	user = UserLogin(user);


}

int main() {
	
	Login();

	return 0;
}