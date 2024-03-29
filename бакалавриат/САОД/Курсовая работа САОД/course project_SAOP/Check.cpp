/*Check.h*/
#include "Check.h"

//������ ��� �������� ��������� ������ ����
int Check::checkc()
{
	cout << "\n����� ��������: ";
	int var;
	cin >> var;
	while (cin.fail() || var < 0 || var >20 || cin.get() != '\n')
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� ��� ���:\n ";
		cin >> var;
	}
	return var;
}


//������� ��� �������� �������� ����� ��������
int Check::checkseries()
{
	int series;
	cin >> series;
	while (cin.fail() || series < 1000 || series>9999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cin >> series;
	}
	return series;
}

//������� ��� �������� ��������� ������ ��������
int Check::checknumber()
{
	int number;
	cin >> number;
	while (cin.fail() || number < 100000 || number>999999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cin >> number;
	}
	return number;
}


//������� ��� �������� ��������� ���� ������
string Check::checktype()
{
	string type;
	int t = 1;
	while (t != 0) {
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		getline(cin, type);
		t = 0;
		for (int i = 0; i < type.length(); i++) {
			if (isdigit((unsigned char)type.at(i))) {
				cout << "������������ ����, ��������� �������!\n";
				t++;
				break;
			}

		}
	}
	return type;
}

//������� ��� �������� ��������� ������ ������
int Check::checkcount()
{
	int number;
	cin >> number;
	while (cin.fail() || number < 100 || number>999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cin >> number;
	}
	return number;
}

//������� ��� �������� �������� ����
string Check::fillandcheckdate()
{
	string date, d, y, m;
	int day, month, year;
	stringstream ssday, ssmonth, ssyear;


	cout << "������� ��� (�� 2021 �� 2023):\n";
	cin >> year;
	while (cin.fail() || year < 2021 || year>2023) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cout << "������� ���(�� 1900 �� 2021)\n";
		cin >> year;
	}
	cout << "������� ����� (�� 1 �� 12)\n";
	cin >> month;
	while (cin.fail() || month < 1 || month>12) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cout << "������� ����� �������(�� 1 �� 12)\n";
		cin >> month;
	}
	cout << "������� ����\n";
	cin >> day;
	if (month == 2) //���� �������
	{
		if (year % 4)//�������� �� ���������� ���
		{
			while (cin.fail() || day < 1 || day>28)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "�������� ����, ��������� �������!\n\n";
				cout << "������� ����(�� 1 �� 28)\n";
				cin >> day;
			}
		}
		else
		{
			while (cin.fail() || day < 1 || day>29)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "�������� ����, ��������� �������!\n\n";
				cout << "������� ���� (�� 1 �� 29)\n";
				cin >> day;
			}
		}
	}

	//���� ������, ����, ���, ����, ������, �������, ������� 
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		while (cin.fail() || day < 1 || day>31) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "�������� ����, ��������� �������!\n\n";
			cout << "������� ����(�� 1 �� 31)\n";
			cin >> day;
		}
	}
	//���� ������, ����, ��������, ������
	else
	{
		while (cin.fail() || day < 1 || day>30) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "�������� ����, ��������� �������!\n\n";
			cout << "������� ����(�� 1 �� 30)\n";
			cin >> day;
		}
	}

	ssday << day;
	ssmonth << month;
	ssyear << year;
	d = ssday.str();
	m = ssmonth.str();
	y = ssyear.str();
	date = d + "." + m + "." + y;
	return date;
}

string Check::checkname()
{
	string name;
	int t = 1;
	while (t != 0) {
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		getline(cin, name);
		t = 0;
		for (int i = 0; i < name.length(); i++) {
			if (isdigit((unsigned char)name.at(i))) {
				cout << "������������ ����, ��������� �������!\n";
				t++;
				break;
			}
		}
	}
	return name;
}

int Check::checkyear()
{
	int year;
	cin >> year;
	while (cin.fail() || year < 1900 || year>2021) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� �������!\n\n";
		cout << "������� ��� �������� (�� 1900 �� 2021)\n";
		cin >> year;
	}
	return year;
}

int Check::checkquantity()
{
	int var;
	cin >> var;
	while (cin.fail() || var < 0 || var >5 || cin.get() != '\n')
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� ��� ���:\n ";
		cin >> var;
	}
	return var;
}

bool Check::checkbathroom()
{
	int var;
	cin >> var;
	while (cin.fail() || var < 0 || var >1 || cin.get() != '\n')
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "�������� ����, ��������� ��� ���:\n ";
		cin >> var;
	}
	if (var == 0) {
		return false;
	}
	else
	{
		return true;
	}

}

