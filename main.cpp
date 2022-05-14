#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
#include<fstream>

using namespace std;

int phase1_reg_hour_unit_priceD = NULL;
int phase1_peak_hours_unit_priceD = NULL;
int phase1_percentage_of_taxD = NULL;
int phase1_fixed_chargesD = NULL;

int phase1_reg_hour_unit_priceC = NULL;
int phase1_peak_hours_unit_priceC = NULL;
int phase1_percentage_of_taxC = NULL;
int phase1_fixed_chargesC = NULL;

int phase3_reg_hour_unit_priceD = NULL;
int phase3_peak_hours_unit_priceD = NULL;
int phase3_percentage_of_taxD = NULL;
int phase3_fixed_chargesD = NULL;

int phase3_reg_hour_unit_priceC = NULL;
int phase3_peak_hours_unit_priceC = NULL;
int phase3_percentage_of_taxC = NULL;
int phase3_fixed_chargesC = NULL;

int strlength(char* str);
char* get_string(char* str);
bool employee(string username, string password);
void load_cus_data(int& no_of_customer, char**& cus_ID, char**& cus_DOB, char**& cus_name, char**& cus_address, char**& cus_contactnum, char**& cus_type, char**& cus_metertype, char**& cus_connectiondate, int*& reg_hrs, int*& peak_hrs, char**& cus_pass);
 
void load_emp_data(char**& emp_user, char**& emp_pass, int& no_of_employee);
bool Employee_Verification(char** employee_username, char** employee_password, char* loggedin_Username, char* loggedin_Password, int totalEmployees, int& foundIndex);


void Phase3_Tariff_for_C(int& phase3_reg_hour_unit_priceC, int& phase3_peak_hours_unit_priceC, int& phase3_percentage_of_taxC, int& phase3_fixed_chargesC, ifstream& tarriff_input);
void Phase3_Tariff_for_D(int& phase3_reg_hour_unit_priceD, int& phase3_peak_hours_unit_priceD, int& phase3_percentage_of_taxD, int& phase3_fixed_chargesD, ifstream& tarriff_input);
void Phase1_Tariff_for_D(int& phase1_reg_hour_unit_priceD, int& phase1_peak_hours_unit_priceD, int& phase1_percentage_of_taxD, int& phase1_fixed_chargesD, ifstream& tarriff_input);
void Phase1_Tariff_for_C(int& phase1_reg_hour_unit_priceC, int& phase1_peak_hours_unit_priceC, int& phase1_percentage_of_taxC, int& phase1_fixed_chargesC, ifstream& tarriff_input);
void Phase1_Tariff_for_D(int& phase1_reg_hour_unit_priceD, int& phase1_peak_hours_unit_priceD, int& phase1_percentage_of_taxD, int& phase1_fixed_chargesD);

void Phase1_Tariff_for_C(int& phase1_reg_hour_unit_priceC, int& phase1_peak_hours_unit_priceC, int& phase1_percentage_of_taxC, int& phase1_fixed_chargesC);
void Phase3_Tariff_for_D(int& phase3_reg_hour_unit_priceD, int& phase3_peak_hours_unit_priceD, int& phase3_percentage_of_taxD, int& phase3_fixed_chargesD);
void Phase3_Tariff_for_C(int& phase3_reg_hour_unit_priceC, int& phase3_peak_hours_unit_priceC, int& phase3_percentage_of_taxC, int& phase3_fixed_chargesC);
void update_tariff(ofstream& put);

void load_bill_info(char**& ID, int*& BillingMonth, int*& ConsumedUnits, int*& Totalbill, int*& DueDate, bool*& Status, int totalcustomers);
void view_bill(char** id, bool* status, int* TotalBill, int i);
void change_password(char**& emp_user, char**& emp_pass, int no_of_employee);
void register_customer(int& no_of_customer);
void billing_info(char**& id, int no_of_customer, char** cus_metertype, char** cus_type, bool*& status, int*& Total_bill);
void view_cus_bill(char** ID, char* id, int no_of_customer, bool* status, char** cus_metertype, char** cus_type, int* Total_bill);
void bill_statistic(char** ID, bool* status, int no_of_customer, int* totalbill);
void change_status(int index, bool* status);
int find_cus(char** ID, char* id, int no_of_customers);
bool customer(char** ID, char** customerpassword, char* loggedin_username, char* loggedin_password, int total_customers, int& foundIndex);

int main()
{
	// Employee Information
	char** emp_user = NULL; // 2D array to load employees list
	char** emp_pass = NULL; // 2D array to load employees's password
	// Customer Information
	char** cus_ID = NULL; // customer ID
	char** cus_DOB = NULL; // Date of Birth of customer 
	char** cus_name = NULL; // Name of customer
	char** cus_address = NULL;	// Address of customer
	char** cus_contactnumber = NULL; // contact number
	char** cus_type = NULL; // customer type i.e. either commercial or domestic
	char** cus_metertype = NULL; // meter type i.e. 1phase meter or 3phase meter
	char** cus_connectiondate = NULL; // connection date
	char** cus_pass = NULL;	//customer's passwords array

	int* reg_hrs = NULL; // meter reading in regular hours
	int* peak_hrs = NULL; // meter reading on peak hours
	int option = NULL; // choice for menu control
	int no_of_customers = NULL;//total customers
	int no_of_employees = NULL;//total employees

	int* Total_bill = new int[10];
	int* billing_month = new int[no_of_customers];
	int* consumed_units = new int[no_of_customers];
	int* total_bill = new int[no_of_customers];
	int* duedate = new int[no_of_customers];

	bool* bill_status = new bool[10];
	bool* status = new bool[no_of_customers];

	char* login_username;
	char* login_password;
	// loading Customers Data
	load_cus_data(no_of_customers, cus_ID, cus_DOB, cus_name, cus_address, cus_contactnumber, cus_type, cus_metertype, cus_connectiondate, reg_hrs, peak_hrs, cus_pass);
	//loading employee data
	load_emp_data(emp_user, emp_pass, no_of_employees);
										// Loading Tariff Data
	ifstream input_tarriff("TariffTaxInfo.txt");
	Phase1_Tariff_for_D(phase1_reg_hour_unit_priceD, phase1_peak_hours_unit_priceD, phase1_percentage_of_taxD, phase1_fixed_chargesD, input_tarriff);
	Phase1_Tariff_for_C(phase1_reg_hour_unit_priceC, phase1_peak_hours_unit_priceC, phase1_percentage_of_taxC, phase1_fixed_chargesC, input_tarriff);
	Phase3_Tariff_for_D(phase3_reg_hour_unit_priceD, phase3_peak_hours_unit_priceD, phase3_percentage_of_taxD, phase3_fixed_chargesD, input_tarriff);
	Phase3_Tariff_for_C(phase3_reg_hour_unit_priceC, phase3_peak_hours_unit_priceC, phase3_percentage_of_taxC, phase3_fixed_chargesC, input_tarriff);


	// loading Bill Info
	char** id = new char* [no_of_customers];
	load_bill_info(id, billing_month, consumed_units, total_bill, duedate, status, no_of_customers);
	string username;// for emp & cus login;
	string password;// for emp & cus login;
	bool isverified;
	int tries = 3;
	char choice;
	char temp_string[50];
	char* _id;
	int index;
	bool verified;
a:
	system("cls");
	cout << "\t\tWelcome to LESCO Biling System\n";
	cout << "\t\tPress 1. For Employee interface\n";
	cout << "\t\tPress 2. For Customer interface\n";
	cout << "\t\tPress Esc. To Exit\n";
	choice = _getch();
	switch (choice)
	{
	case '1':
	b:
		system("cls");
		cout << '\n';
		cout << "Enter your username\n";
		cin >> username;
		cout << "Enter your password\n";
		cin >> password;
		isverified = employee(username, password);
		if (isverified)
		{
			int choice2;
		m:
			system("cls");
			cout << "\n\t\tPress 1. To Change your account's Password\n";
			cout << "\t\tPress 2. To Register a new Customer\n";
			cout << "\t\tPress 3. To Enter Billing Information\n";
			cout << "\t\tPress 4. To View the Bill of a Customer \n";
			cout << "\t\tPress 5. To View the Statistics of Bills\n";
			cout << "\t\tPress 6. To Update the Tariff Information\n";
			cout << "\t\tPress 7. To Change the Status of a customer \n";
			cout << "\t\tPress 0. To Get back to main page\n";
			cin >> choice2;
			switch (choice2)
			{
			case 1:
				system("cls");
				change_password(emp_user, emp_pass, no_of_employees);
				goto m;
				break;
			case 2:
				system("cls");
				register_customer(no_of_customers);
				goto m;
				break;
			case 3:
				system("cls");
				billing_info(cus_ID, no_of_customers, cus_metertype, cus_type, bill_status, Total_bill);
				goto m;
				break;
			case 4:
				cout << "Enter Customer ID :";
				cin >> temp_string;
				char* id;
				id = get_string(temp_string);
				view_cus_bill(cus_ID, id, no_of_customers, status, cus_metertype, cus_type, total_bill);
				goto m;
				break;
			case 5:
				bill_statistic(cus_ID, status, no_of_customers, total_bill);
				goto m;
				break;
			case 6:
				int temp;
			l:
				system("cls");
				cout << "\t\tPress 1. For 1-Phase meter Domestic Customer\n";
				cout << "\t\tPress 2. For 1-Phase meter Commercial Customer\n";
				cout << "\t\tPress 3. For 3-Phase meter Domestic Customer\n";
				cout << "\t\tPress 4. For 3-Phase meter Commercial Customer\n";
				cout << "\t\tPress 5. To Go back to previous page\n";
				cin >> temp;
				if (temp == 1)
				{
					Phase1_Tariff_for_D(phase1_reg_hour_unit_priceD, phase1_peak_hours_unit_priceD, phase1_percentage_of_taxD, phase1_fixed_chargesD);
					goto l;
				}
				else if (temp == 2)
				{
					Phase1_Tariff_for_C(phase1_reg_hour_unit_priceC, phase1_peak_hours_unit_priceC, phase1_percentage_of_taxC, phase1_fixed_chargesC);
					goto l;
				}
				else if (temp == 3)
				{
					Phase3_Tariff_for_D(phase3_reg_hour_unit_priceD, phase3_peak_hours_unit_priceD, phase3_percentage_of_taxD, phase3_fixed_chargesD);
					goto l;
				}
				else if (temp == 4)
				{
					Phase3_Tariff_for_C(phase3_reg_hour_unit_priceC, phase3_peak_hours_unit_priceC, phase3_percentage_of_taxC, phase3_fixed_chargesC);
					goto l;
				}
				else if (temp == 5)
				{
					goto m;
				}
				else
				{
					cout << "Invalid Input\n";
					goto l;
				}
				break;
			case 7:
				cout << "Enter customer ID :";
				cin >> temp_string;
				_id = get_string(temp_string);
				index = find_cus(cus_ID, _id, no_of_customers);
				change_status(index, status);
				view_bill(cus_ID, status, total_bill, index);
				goto m;
				break;
			case 0:
				goto a;
				break;
			default:
				cout << "Invalid Input.Enter again\n";
				goto m;
				break;
			}
		}
		else
		{
			tries--;
			if (tries == 0)
			{
				int opt;
			c:
				system("cls");
				cout << "System disabled \n";
				cout << "Enter 1 to restart\n";
				cout << "Enter 2 to exit\n";
				cin >> opt;
				if (opt == 1)
				{
					goto a;
				}
				else if (opt == 2)
				{
					cout << "Thanks For Using \n";
				}
				else
				{
					goto c;
				}
			}
			else
			{
				goto b;
			}
		}
		break;
	case '2':
		cout << "Enter username: \n";
		cin.getline(temp_string, 50);
		login_username = get_string(temp_string);
		cout << "Enter Password: \n";
		cin.getline(temp_string, 50);
		login_password = get_string(temp_string);
		int foundcustomer;
		verified = customer(cus_ID, cus_pass, login_username, login_password, no_of_customers, foundcustomer);
		if (verified)
		{
			cout << "\n\t\tPress 1 To View bill\n";
			cout << "Press 2 To Exit\n";
			view_bill(id, status, total_bill, foundcustomer);
		}
		else
		{
			cout << "Invalid ID or password\n";
		}
		break;
	case 27:
		cout << "Thank You For Using Our System\n";
		break;
	default:
		cout << "\t\tInvalid Input.Enter again\n";
		goto a;
		break;
	}
}

int strlength(char* str)
{
	int stringLen = 0;
	for (char* temp = str; *temp != '\0'; temp++)
		stringLen++;

	return stringLen;
}   // to calculate lenght of string

// This function will return the string
char* get_string(char* str)
{
	int strLen = strlength(str);
	char* mystr = 0;

	if (strLen > 0)
	{
		mystr = new char[strLen + 1];
		for (int i = 0; i < strLen; i++)
		{
			mystr[i] = str[i];
		}
		mystr[strLen] = '\0';
	}
	return mystr;
}

bool employee(string username, string password)
{
	ifstream fin;
	string line;
	bool check2 = false;
	fin.open("emp.txt");
	if (fin.is_open())
	{

		while (getline(fin, line))
		{

			for (int i = 0; username[i] != '\0'; i++)
			{
				if (username[i] == line[i] && line[i] != ',')
				{
					check2 = true;
				}
				else
					check2 = false;

			}
			if (check2)
			{
				check2 = false;
				int size = username.length();
				for (int i = size + 1, j = 0; password[j] != '\0'; i++, j++)
				{
					if (password[j] == line[i] && line[i] != '\0')
					{
						check2 = true;

					}
					else
						check2 = false;
				}

			}
			if (check2)
			{
				cout << "LOGIN SUCCESFUL";
				break;
			}
		}
	}
	if (check2 == false)
	{
		cout << "USERNAME OR PASS INCORECT ";
	}
	return check2;
}
void load_cus_data(int& no_of_customer, char**& cus_ID, char**& cus_DOB, char**& cus_name, char**& cus_address, char**& cus_contactnum, char**& cus_type, char**& cus_metertype, char**& cus_connectiondate, int*& reg_hrs, int*& peak_hrs, char**& cus_pass)
{
	ifstream fin("cus.txt");
	if (fin.is_open())
	{
		cus_ID = new char* [10];
		cus_DOB = new char* [10];
		cus_name = new char* [10];
		cus_address = new char* [10];
		cus_contactnum = new char* [10];
		cus_type = new char* [10];
		cus_metertype = new char* [10];
		cus_connectiondate = new char* [10];
		reg_hrs = new int[10];
		peak_hrs = new int[10];
		cus_pass = new char* [10];

		char temp[100];
		int i = 0;
		while (!fin.eof())
		{

			fin.getline(temp, 100, ',');
			cus_ID[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_DOB[i] = get_string(temp);
			cus_pass[i] = get_string(temp);


			fin.getline(temp, 100, ',');
			cus_name[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_address[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_contactnum[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_type[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_metertype[i] = get_string(temp);

			fin.getline(temp, 100, ',');
			cus_connectiondate[i] = get_string(temp);

			int number;
			fin >> number;
			reg_hrs[i] = number;
			fin.ignore();

			fin >> number;
			peak_hrs[i] = number;
			i++;
		}
		no_of_customer = i;
		fin.close();
	}
	else
	{
		cout << "OPS!! \n NO DATA FOUND\n";
	}

}
void load_emp_data(char**& emp_user, char**& emp_pass, int& no_of_employee)
{
	ifstream fin("emp.txt");

	if (fin.is_open())
	{
		emp_user = new char* [4];
		emp_pass = new char* [4];

		char temp[100];

		int i = 0;
		while (!fin.eof())
		{
			fin.getline(temp, 100, ',');
			emp_user[i] = get_string(temp);

			fin.getline(temp, 100);
			emp_pass[i] = get_string(temp);

			i++;
			no_of_employee = i;
		}
		fin.close();
	}
	else
	{
		cout << "OPS!! DATA NOT FOUND\n";
	}
}
void Phase1_Tariff_for_D(int& phase1_reg_hour_unit_priceD, int& phase1_peak_hours_unit_priceD, int& phase1_percentage_of_taxD, int& phase1_fixed_chargesD, ifstream& tariff_input)
{
	char buffer[100];
	tariff_input.getline(buffer, 100, ',');

	tariff_input >> phase1_reg_hour_unit_priceD;

	tariff_input.ignore();
	tariff_input >> phase1_peak_hours_unit_priceD;

	tariff_input.ignore();
	tariff_input >> phase1_percentage_of_taxD;

	tariff_input.ignore();
	tariff_input >> phase1_fixed_chargesD;

}
void Phase1_Tariff_for_C(int& phase1_reg_hour_unit_priceC, int& phase1_peak_hours_unit_priceC, int& phase1_percentage_of_taxC, int& phase1_fixed_chargesC, ifstream& tariff_input)
{
	char buffer[100];
	tariff_input.getline(buffer, 100, ',');

	tariff_input >> phase1_reg_hour_unit_priceC;

	tariff_input.ignore();
	tariff_input >> phase1_peak_hours_unit_priceC;

	tariff_input.ignore();
	tariff_input >> phase1_percentage_of_taxC;

	tariff_input.ignore();
	tariff_input >> phase1_fixed_chargesC;
}
void Phase3_Tariff_for_D(int& phase3_reg_hour_unit_priceD, int& phase3_peak_hours_unit_priceD, int& phase3_percentage_of_taxD, int& phase3_fixed_chargesD, ifstream& tariff_input)
{
	char buffer[100];
	tariff_input.getline(buffer, 100, ',');

	tariff_input >> phase3_reg_hour_unit_priceD;

	tariff_input.ignore();
	tariff_input >> phase3_peak_hours_unit_priceD;

	tariff_input.ignore();
	tariff_input >> phase3_percentage_of_taxD;

	tariff_input.ignore();
	tariff_input >> phase3_fixed_chargesD;
}
void Phase3_Tariff_for_C(int& phase3_reg_hour_unit_priceC, int& phase3_peak_hours_unit_priceC, int& phase3_percentage_of_taxC, int& phase3_fixed_chargesC, ifstream& tariff_input)
{
	char buffer[100];

	tariff_input.getline(buffer, 100, ',');

	tariff_input >> phase3_reg_hour_unit_priceC;

	tariff_input.ignore();
	tariff_input >> phase3_peak_hours_unit_priceC;

	tariff_input.ignore();
	tariff_input >> phase3_percentage_of_taxC;

	tariff_input.ignore();
	tariff_input >> phase3_fixed_chargesC;

}
//update tariff information
void Phase1_Tariff_for_D(int& phase1_reg_hour_unit_priceD, int& phase1_peak_hours_unit_priceD, int& phase1_percentage_of_taxD, int& phase1_fixed_chargesD)
{
	cout << "Enter Regular Hour Unit Price: ";
	cin >> phase1_reg_hour_unit_priceD;

	phase1_peak_hours_unit_priceD = 0;

	cout << "Enter Percentage of Tax: ";
	cin >> phase1_percentage_of_taxD;

	cout << "Enter Fixed Charges";
	cin >> phase1_fixed_chargesD;

	ofstream fout("TariffTaxInfo.txt");
	update_tariff(fout);
}
void Phase1_Tariff_for_C(int& phase1_reg_hour_unit_priceC, int& phase1_peak_hours_unit_priceC, int& phase1_percentage_of_taxC, int& phase1_fixed_chargesC)
{
	cout << "Enter Regular Hour Unit Price: ";
	cin >> phase1_reg_hour_unit_priceC;

	phase1_peak_hours_unit_priceD = 0;

	cout << "Enter Percentage of Tax: ";
	cin >> phase1_percentage_of_taxC;

	cout << "Enter Fixed Charges";
	cin >> phase1_fixed_chargesC;
	ofstream fout("TariffTaxInfo.txt");
	update_tariff(fout);
}
void Phase3_Tariff_for_D(int& phase3_reg_hour_unit_priceD, int& phase3_peak_hours_unit_priceD, int& phase3_percentage_of_taxD, int& phase3_fixed_chargesD)
{
	cout << "Enter Regular hours Price: ";
	cin >> phase3_reg_hour_unit_priceD;

	cout << "Enter Peak Hours Price: ";
	cin >> phase3_peak_hours_unit_priceD;

	cout << "Enter Pecentage of Tax: ";
	cin >> phase3_percentage_of_taxD;

	cout << "Enter Fixed Charges: ";
	cin >> phase3_fixed_chargesD;

	ofstream fout("TariffTaxInfo.txt");
	update_tariff(fout);
}
void Phase3_Tariff_for_C(int& phase3_reg_hour_unit_priceC, int& phase3_peak_hours_unit_priceC, int& phase3_percentage_of_taxC, int& phase3_fixed_chargesC)
{
	cout << "Enter Regular hours Price: ";
	cin >> phase3_reg_hour_unit_priceC;

	cout << "Enter Peak Hours Price: ";
	cin >> phase3_peak_hours_unit_priceC;

	cout << "Enter Pecentage of Tax: ";
	cin >> phase3_percentage_of_taxC;

	cout << "Enter Fixed Charges: ";
	cin >> phase3_fixed_chargesC;

	ofstream fout("TariffTaxInfo.txt");
	update_tariff(fout);
}
void update_tariff(ofstream& fout)
{
	fout << "1Phase" << "," << phase1_reg_hour_unit_priceD << "," << phase1_peak_hours_unit_priceD << "," << phase1_percentage_of_taxD << "," << phase1_fixed_chargesD << endl;
	fout << "1Phase" << "," << phase1_reg_hour_unit_priceC << "," << phase1_peak_hours_unit_priceC << "," << phase1_percentage_of_taxC << "," << phase1_fixed_chargesC << endl;
	fout << "3Phase" << "," << phase3_reg_hour_unit_priceD << "," << phase3_peak_hours_unit_priceD << "," << phase3_percentage_of_taxD << "," << phase3_fixed_chargesD << endl;
	fout << "3Phase" << "," << phase3_reg_hour_unit_priceC << "," << phase3_peak_hours_unit_priceC << "," << phase3_percentage_of_taxC << "," << phase3_fixed_chargesC << endl;

}

void load_bill_info(char**& ID, int*& BillingMonth, int*& ConsumedUnits, int*& Totalbill, int*& DueDate, bool*& Status, int totalcustomers)
{
	char buffer[100];
	ifstream input("BillingInfo.txt");
	if (input.is_open())
	{
		for (int i = 0; i < totalcustomers; i++)
		{
			input.getline(buffer, 100, ',');
			ID[i] = get_string(buffer);

			int number;

			input >> BillingMonth[i];
			input.ignore();

			input >> ConsumedUnits[i];
			input.ignore();

			input >> Totalbill[i];
			input.ignore();

			input >> DueDate[i];
			input.ignore();

			input >> Status[i];

		}
	}
}
void view_bill(char** id, bool* status, int* TotalBill, int i)
{
	cout << id[i] << " ";
	if (status[i] == true)
		cout << "Customer bill is Paid" << " ";
	else
		cout << "Customer bill is Un-Paid" << " ";
	cout << " " << TotalBill[i] << endl;
}

void change_password(char**& emp_user, char**& emp_pass, int no_of_employee)
{
	char buffer[50];
	cout << "Enter Your Username: ";
	cin >> buffer;
	char* loggedin_Username = get_string(buffer);

	cout << "Enter your current Password: ";
	cin >> buffer;
	char* loggedin_Password = get_string(buffer);
	int foundIndex = NULL;
	bool verified = Employee_Verification(emp_user, emp_pass, loggedin_Username, loggedin_Password, no_of_employee, foundIndex);
	if (verified) {
		emp_pass[foundIndex] = NULL;
		cout << "Enter new Password: ";
		cin.ignore();
		cin.getline(buffer, 100);
		emp_pass[foundIndex] = get_string(buffer);

		ofstream put("emp.txt");
		for (int i = 0; i < no_of_employee; i++)
		{
			put << emp_user[i] << "," << emp_pass[i] << endl;
		}
		put.close();
	}
	if (!verified)
	{
		cout << "No Such Username Exist\n";
	}
	cout << "Password Changed Successfully\n";
}

bool Employee_Verification(char** employee_username, char** employee_password, char* loggedin_Username, char* loggedin_Password, int totalEmployees, int& foundIndex)
{
	bool correctUsername = false;
	bool correctPassword = false;

	for (int i_index = NULL; i_index < totalEmployees; i_index++)
	{
		char* temp = employee_username[i_index];

		if (strlength(temp) == strlength(loggedin_Username))
		{
			for (int j_index = NULL; j_index < strlength(temp); j_index++)
			{
				correctUsername = false;
				if (temp[j_index] == loggedin_Username[j_index])
				{
					correctUsername = true;
				}
			}

			if (correctUsername == true)
			{
				char* temp2 = employee_password[i_index];

				for (int j_index = NULL; j_index < strlength(temp2); j_index++)
				{
					correctPassword = false;
					if (temp2[j_index] == loggedin_Password[j_index])
					{
						correctPassword = true;
						foundIndex = i_index;
					}
					else
					{
						foundIndex = NULL;
					}
				}
			}

			if (correctPassword == true)
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
}

void register_customer(int& no_of_customer)
{
	ofstream fout;
	fout.open("cus.txt", std::fstream::app);
	string data;
	cout << "Enter ID: ";
	cin >> data;
	fout << endl << data << ",";

	cout << "Enter Date Of Birth: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Name: ";
	cin.ignore();
	getline(cin, data);
	fout << data << ",";

	cout << "Enter Address: ";
	getline(cin, data);
	fout << data << ",";

	cout << "Enter Contact Number: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Customer Type: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Meter Type: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Cd: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Regular Hours Consumption: ";
	cin >> data;
	fout << data << ",";

	cout << "Enter Peak Hours Consumption: ";
	cin >> data;
	fout << data;

	no_of_customer++;
}

void billing_info(char**& id, int no_of_customer, char** cus_metertype, char** cus_type, bool*& status, int*& Total_bill)
{
	int* BillingMonth = new int[no_of_customer];

	int* SalesTax = new int[no_of_customer];
	int* FixedCharges = new int[no_of_customer];
	Total_bill = new int[no_of_customer];
	int* DueDate = new int[no_of_customer];
	status = new bool[no_of_customer];


	int* reading_entry_date = new int[no_of_customer];

	int* currentRegular_meterReading = new int[no_of_customer];
	int* currentPeak_meterReading = new int[no_of_customer];

	int* Regular_costperunit = new int[no_of_customer];
	int* Peak_costperunit = new int[no_of_customer];


	int* regularconsumedunits = new int[no_of_customer];
	int* peakconsumedunits = new int[no_of_customer];

	int* currentmeterRead = new int[no_of_customer];
	int* previousmeterRead = new int[no_of_customer];

	for (int i = 0; i < no_of_customer; i++)
	{
		previousmeterRead[i] = 0;
	}
	int* costperunits = new int[no_of_customer];
	int* consumedUnits = new int[no_of_customer];

	ofstream OutputBill("BillingInfo.txt");
	if (OutputBill.is_open())
	{
		for (int index = NULL; index < no_of_customer; index++)
		{
			char buffer[100];
			OutputBill << id[index] << ",";

			int number;
			cout << "Billing Month: ";
			cin >> number;
			BillingMonth[index] = number;
			OutputBill << BillingMonth[index] << ",";

			currentmeterRead[index] = 0;
			//OutputBill << currentmeterRead[index] << ",";

			cout << "Reading Entry Date: ";
			cin >> number;
			reading_entry_date[index] = number;
			//OutputBill << reading_entry_date[index] << ",";

			if (cus_metertype[index][0] == '1')
			{
				cout << "Current Meter Reading for regular hours:  ";
				cin >> number;
				currentRegular_meterReading[index] = number;
				//OutputBill << currentRegular_meterReading[index] << ",";


				if (cus_type[index][0] == 'D')
				{
					FixedCharges[index] = phase1_fixed_chargesD;
					//OutputBill << FixedCharges[index]<<",";

					Peak_costperunit[index] = phase1_peak_hours_unit_priceD;
					//OutputBill << Peak_costperunit[index]<<",";

					Regular_costperunit[index] = phase1_reg_hour_unit_priceD;
					//OutputBill << Regular_costperunit[index]<<",";

					consumedUnits[index] = currentRegular_meterReading[index];
					OutputBill << consumedUnits[index] << ",";

					int currentmonthunits = consumedUnits[index] - previousmeterRead[index];
					//OutputBill << previousmeterRead[index] << ",";
					//OutputBill << currentmonthunits << ",";

					SalesTax[index] = phase1_percentage_of_taxD;
					//OutputBill << SalesTax[index]<<",";

					Total_bill[index] = currentmonthunits * SalesTax[index] / 100 + FixedCharges[index];
					OutputBill << Total_bill[index] << ",";
				}
				else
				{
					if (cus_type[index][0] == 'C')
					{
						FixedCharges[index] = phase1_fixed_chargesC;

						Peak_costperunit[index] = phase1_peak_hours_unit_priceC;

						Regular_costperunit[index] = phase1_reg_hour_unit_priceC;
						//OutputBill << Regular_costperunit[index] << ",";


						consumedUnits[index] = currentRegular_meterReading[index];
						OutputBill << consumedUnits[index] << ",";

						int currentmonthunits = consumedUnits[index] - previousmeterRead[index];
						//OutputBill << previousmeterRead[index] << ",";
						//OutputBill << currentmonthunits;


						SalesTax[index] = phase1_percentage_of_taxC;
						Total_bill[index] = currentmonthunits * SalesTax[index] / 100 + FixedCharges[index];
						OutputBill << Total_bill[index] << ",";
					}
				}
			}
			else
			{
				if (cus_metertype[index][0] == '3')
				{
					cout << "Current Meter Reading for regular hours:  ";
					cin >> number;
					currentRegular_meterReading[index] = number;
					//OutputBill << currentRegular_meterReading[index] << ",";

					cout << "Current Meter Reading for Peak Hours: ";
					cin >> number;
					currentPeak_meterReading[index] = number;


					if (cus_type[index][0] == 'D')
					{
						FixedCharges[index] = phase3_fixed_chargesD;
						//OutputBill << FixedCharges[index] << ",";

						// price
						Peak_costperunit[index] = phase3_peak_hours_unit_priceD;
						//OutputBill << Peak_costperunit[index] << ",";

						// price
						Regular_costperunit[index] = phase3_reg_hour_unit_priceD;
						//OutputBill << Regular_costperunit[index] << ",";

						consumedUnits[index] = currentRegular_meterReading[index] + currentPeak_meterReading[index];
						OutputBill << consumedUnits[index] << ",";

						int currentmonthunits = consumedUnits[index] - previousmeterRead[index];
						//OutputBill << previousmeterRead[index] << ",";
						//OutputBill << currentmonthunits << ",";

						SalesTax[index] = phase3_percentage_of_taxD;
						//OutputBill << SalesTax[index] << ",";

						Total_bill[index] = currentmonthunits * SalesTax[index] / 100 + FixedCharges[index];
						OutputBill << Total_bill[index] << ",";
					}
					else
					{
						if (cus_type[index][0] == 'C')
						{
							FixedCharges[index] = phase3_fixed_chargesC;
							// Price
							Peak_costperunit[index] = phase3_peak_hours_unit_priceC;
							//OutputBill << Peak_costperunit[index] << ",";


							Regular_costperunit[index] = phase3_reg_hour_unit_priceC;
							//OutputBill << Regular_costperunit[index] << ",";

							consumedUnits[index] = currentRegular_meterReading[index] + currentPeak_meterReading[index];
							OutputBill << consumedUnits[index] << ",";

							int currentmonthunits = consumedUnits[index] - previousmeterRead[index];

							SalesTax[index] = phase3_percentage_of_taxC;
							Total_bill[index] = currentmonthunits * SalesTax[index] / 100 + FixedCharges[index];
							OutputBill << Total_bill[index] << ",";
						}
					}
				}
			}

			DueDate[index] = reading_entry_date[index] + 7;
			OutputBill << DueDate[index] << ",";
			status[index] = false;
			OutputBill << status[index] << endl;

		}

	}
	else
	{
		cout << "BillingInfo File cannot be openned.\n";
	}

}

void view_cus_bill(char** ID, char* id, int no_of_customer, bool* status, char** cus_metertype, char** cus_type, int* Total_bill)
{
	bool found = false;
	for (int i = 0; i < no_of_customer; i++)
	{
		char* temp = ID[i];

		for (int j = 0; j < strlen(temp); j++)
		{
			found = false;
			if (temp[j] == id[j])
			{
				found = true;
			}
		}
		if (found == true)
		{
			if (status[i] == 1)
				cout << "Status of " << temp << " is Paid" << " ";
			else
				if (status[i] == 0)
					cout << "Status of " << temp << " is Un-Paid" << " ";
			cout << "\nBill: " << Total_bill[i] << endl;
			cout << "Customer Type: " << cus_type[i] << endl;
			cout << "Meter Type: " << cus_metertype[i] << endl;

		}
	}
}

void bill_statistic(char** ID, bool* status, int no_of_customer, int* totalbill)
{
	int unpaid = NULL;
	int paid = NULL;
	for (int i = 0; i < no_of_customer; i++)
	{
		if (status[i] == 0)
		{
			cout << ID[i] << "'s" << " bill " << totalbill[i] << " is unpaid\n";
			unpaid = unpaid + totalbill[i];
		}

		if (status[i] == 1)
		{
			cout << ID[i] << "'s" << " bill " << totalbill[i] << " is Paid\n";
			paid = paid + totalbill[i];
		}

	}

	cout << "Total amount of unapid bills is: " << unpaid<<'\n';
	cout << "Total amount of paid bills is: " << paid;
}

void change_status(int index, bool* status)
{
	cout << "Status changed to paid\n";
	status[index] = 1;
}

int find_cus(char** ID, char* id, int no_of_customer)
{
	bool found = false;
	for (int i = 0; i < no_of_customer; i++)
	{
		char* temp = ID[i];

		found = false;
		for (int j = 0; j < strlen(temp); j++)
		{
			if (temp[j] == id[j])
				found = true;
			else {
				break;
			}
		}
		if (found == true)
		{
			return i;
		}
	}
}

bool customer(char** ID, char** customerpassword, char* loggedin_username, char* loggedin_password, int total_customers, int& foundIndex)
{
	bool customerID = false;
	bool customer_Password = false;

	for (int index = NULL; index < total_customers; index++)
	{
		char* temp = ID[index];
		char* newString = temp;
		if (temp[0] == '\n')
		{
			int len = strlength(temp);

			newString = new char[len];

			int counter = 1;
			int index = NULL;
			for (; index < len; index++)
			{
				newString[index] = temp[counter];
				counter++;
			}
			newString[index] = '\0';
		}
		temp = newString;
		int check = NULL;
		if (strlength(temp) == strlength(loggedin_username))
		{
			for (int j = NULL; j < strlength(temp); j++)
			{
				customerID = false;

				if (temp[j] == loggedin_username[j])
				{
					customerID = true;
					check++;
				}

			}

			if (check == strlength(loggedin_username))
			{
				check = NULL;
				char* _temp = customerpassword[index];
				if (strlength(_temp) == strlength(loggedin_password))
				{
					for (int j_index = NULL; j_index < strlength(_temp); j_index++)
					{
						customer_Password = false;

						if (_temp[j_index] == loggedin_password[j_index])
						{
							customer_Password = true;
							check++;
						}
					}
					if (check == strlength(loggedin_password))
					{
						foundIndex = index;
						return true;
					}
				}
				else
				{
					return false;
				}
			}
		}
	}
}

