/*Check.h*/
#include "Check.h"

//Фунция для проверки введённого пункта меню
int Check::checkc()
{
	cout << "\nНомер операции: ";
	int var;
	cin >> var;
	while (cin.fail() || var < 0 || var >20 || cin.get() != '\n')
	{
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите еще раз:\n ";
		cin >> var;
	}
	return var;
}


//Функция для проверки введённой серии паспорта
int Check::checkseries()
{
	int series;
	cin >> series;
	while (cin.fail() || series < 1000 || series>9999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите попытку!\n\n";
		cin >> series;
	}
	return series;
}

//функция для проверки введённого номера паспорта
int Check::checknumber()
{
	int number;
	cin >> number;
	while (cin.fail() || number < 100000 || number>999999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите попытку!\n\n";
		cin >> number;
	}
	return number;
}


//Функция для проверки введённого типа номера
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
				cout << "Некорректный ввод, повторите попытку!\n";
				t++;
				break;
			}

		}
	}
	return type;
}

//Функция для проверки введённого номера номера
int Check::checkcount()
{
	int number;
	cin >> number;
	while (cin.fail() || number < 100 || number>999) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите попытку!\n\n";
		cin >> number;
	}
	return number;
}

//Функция для проверки введённой даты
string Check::fillandcheckdate()
{
	string date, d, y, m;
	int day, month, year;
	stringstream ssday, ssmonth, ssyear;


	cout << "Введите год (от 2021 до 2023):\n";
	cin >> year;
	while (cin.fail() || year < 2021 || year>2023) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите попытку!\n\n";
		cout << "Введите год(от 1900 до 2021)\n";
		cin >> year;
	}
	cout << "Введите месяц (от 1 до 12)\n";
	cin >> month;
	while (cin.fail() || month < 1 || month>12) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
		cout << "Неверный ввод, повторите попытку!\n\n";
		cout << "Введите месяц отъезда(от 1 до 12)\n";
		cin >> month;
	}
	cout << "Введите день\n";
	cin >> day;
	if (month == 2) //если февраль
	{
		if (year % 4)//проверка на високосный год
		{
			while (cin.fail() || day < 1 || day>28)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "Неверный ввод, повторите попытку!\n\n";
				cout << "Введите день(от 1 до 28)\n";
				cin >> day;
			}
		}
		else
		{
			while (cin.fail() || day < 1 || day>29)
			{
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
				cout << "Неверный ввод, повторите попытку!\n\n";
				cout << "Введите день (от 1 до 29)\n";
				cin >> day;
			}
		}
	}

	//если январь, март, май, июль, август, октябрь, декабрь 
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		while (cin.fail() || day < 1 || day>31) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "Неверный ввод, повторите попытку!\n\n";
			cout << "Введите день(от 1 до 31)\n";
			cin >> day;
		}
	}
	//если апрель, июнь, сентябрь, ноябрь
	else
	{
		while (cin.fail() || day < 1 || day>30) {
			cin.clear();
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cout << "Неверный ввод, повторите попытку!\n\n";
			cout << "Введите день(от 1 до 30)\n";
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
				cout << "Некорректный ввод, повторите попытку!\n";
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
		cout << "Неверный ввод, повторите попытку!\n\n";
		cout << "Введите год рождения (от 1900 до 2021)\n";
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
		cout << "Неверный ввод, повторите еще раз:\n ";
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
		cout << "Неверный ввод, повторите еще раз:\n ";
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

