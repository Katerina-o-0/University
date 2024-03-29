/*main.cpp*/
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <windows.h>
#include "Check.h"
#include <ctype.h>
#include <string> 
#include <sstream> 
#include <fstream>
#include <map>

using namespace std;

//Структуры
//Хеш-таблица
struct HashTable
{
	string hashKey; //Ключ. Номер паспорта
	string name; //ФИО
	int year; //год рождения
	string  address; //адрес
	string purp; //цель прибытия

	HashTable()
	{
		hashKey.clear();
		name.clear();
		year = 0;
		address.clear();
		purp.clear();
	}
};
//АВЛ-дерево
struct Node
{
	string number; // номер гостинечного номера формата ANNN
	int quantity; //Кол-во мест
	int room; // Кол-во комнат
	bool bathroom; // Наличие санузла
	string 	device; // оборудование
	unsigned char height; // Высота дерева
	Node* left;
	Node* right;

	Node(string Number, int Quantity, int Room, bool Bathroom, string Device)
	{
		number = Number;
		quantity = Quantity;
		room = Room;
		bathroom = Bathroom;
		device = Device;
		left = right = 0;
		height = 0;
	}
};

//Линейный односвязный список
struct Dlist;
struct NOTE
{
private:
	string pnumber; //номер паспорта
	string rnumber; //номер комнаты
	string start; //дата заселения
	string end; //даты выселения
	NOTE* next = NULL;
public:
	NOTE(string, string, string, string);
	friend Dlist;
};

struct Dlist
{
private:
	NOTE* head = NULL;
	NOTE* tail = NULL;
public:
	void add(string, string, string, string);
	void show();
	void load();
	void removedata(string pnumber);
	int findelem(string);
	void findelemp(string num);
	bool findelemhash(string num);
	int findelemfordel(string num);
	void sorting();
	void quickSort(NOTE** headRef);
	NOTE* getTail(NOTE* cur);
	NOTE* quickSortRecur(NOTE* head, NOTE* end);
	NOTE* partition(NOTE* head, NOTE* end, NOTE** newHead, NOTE** newEnd);
	bool free();
	bool clear();
};


//Константы и глобальные переменные
const int HASH_TABLE_SIZE = 100; // размер хеш таблицы 
HashTable myHashTable[HASH_TABLE_SIZE]; // Хеш таблица 
int g_Hashes = 0; // элементы хеш таблицы 
Node* pTreeCurrent = NULL; // Дерево
int g_Trees = 0; // элементы дерева

//Функции

/*Для хеш-таблицы*/

//Функция хеширования(Линейное опробование)
int hashFunc(string Key);
//Функция для добавление нового гостя в хеш-таблицу
void addnewguest();
//Функция для удаления данных о госте из хеш-таблицы
int delguest(string hashKey);
//Функция для показа списка постояльцев
void showHash();
//функция для очистки списка постоялицев
bool clearUsers();
//функция для поиска постоялица по паспорту 
int searchpassport(string hashKey);
//Функция для поиска постояльцев по ФИО
int searchRate();
//функция для загрузки списка постояльцев из файла
void loadguests();


/*Для дерева*/

//Добавление данных о гостиничном номере
void addClient(string& Number, int& Quantity, int& Room, bool& Bathroom, string& Device);
//Функция для возврата высоты дерева
unsigned char height(Node* p);
//Функция значения баланса
int bfactor(Node* p);
//Функция восстанавливает корректное значение поля height заданного узла
void fixheight(Node* p);
//Поворот дерева направо (вправо)(поворот относительно p направо узла q)
Node* rotateright(Node* p);
// Поворот дерева налево (влево)(поворот относительно q узла p налево)
Node* rotateleft(Node* q);
//Балансировка дерева
Node* balance(Node* p);
// Вставка ключа 
Node* insert(Node* p, string Number, int Quantity, int Room, bool Bathroom, string Device);
//Нахождение узла с минимальным ключем
Node* findmin(Node* p);
//Удаление минимального элемента
Node* removemin(Node* p);
//Удаление элемента
Node* remove(Node* p, string k);
// Вывод дерева 
void display(int level, Node* p);
//очистка данных о гостичных номерах
void clearTree(Node* p);
//Поиск гостиничного номера по его номеру
Node* searchTreeEl(Node* p, string key);
// Поиск гостиничного номера по его номеру без вывода значений
Node * searchTr(Node * p, string key);
//Поиск по фрагменту оборудования(Алгоритм Бойера-Мура)
int BMSearch(char* szHaystack, char* szNeedle, bool& f);
Node* searchTreePart(Node* p, char* szNeedle, int level);
//функция для загрузки списка постояльцев из файла
void loadrooms(string& Number, int& Quantity, int& Room, bool& Bathroom, string& Device);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	system("color F1 ");
	Dlist list;
	Check check;
	string  Series,hashKey,Number, Device;
	int Quantity, Room, nSeries, nNumber;
	bool Bathroom;
	unsigned short int x = 0,j,l;
	int series, number, count;
	string ser, num, type, c, pnumber, rnumber, start, end;
	stringstream ssNum, ssSer, sNum, sSer;
	char* szTreeKeyPart = new char[50]; // Часть искомого 

	do
	{
		cout << "\n\t          МЕНЮ:\n";
		cout << "\n\t     <<Регистрация>>\n";
		cout << "1.   Зарегистрировать вселение постояльца;\n2.   Зарегистрировать выселение постояльца;\n";
		cout << "3.   Просмотреть данные о заселении и выселении;\n\n\n";
		cout << "\t  <<Работа с постояльцами>>\n";
		cout << "4.   Удалить данные о постояльце;\n5.   Просмотреть всех зарегестрированных постояльцев;\n";
		cout << "6.   Очистить данные о постояльцах;\n7.   Найти постояльца по номеру паспорта;\n";
		cout << "8.   Найти постояльца по ФИО;\n\n\n";
		cout << "\t  <<Работа с номерами>>\n";
		cout << "9.    Добавить новый гостиничный номер;\n10.   Удалить сведения о гостиничном номере;\n";
		cout << "11.   Просмотреть все имеющиеся гостиничные номера;\n12.   Очистить данные о номерах;\n";
		cout << "13.   Поиск гостиничного номера по номеру гостиничного номера;\n14.   Поиск гостиничного номера по фрагментам оборудования;\n\n\n";
		cout << "\t  <<Загрузка из файла>>\n";
		cout << "15.   Загрузить данные о заселении и выселении;\n16.   Загрузить информацию о номерах;\n";
		cout << "17.   Загрузить информацию о постояльцах;\n\n0.    Выход из программы;\n";
		x = check.checkc();
		system("cls");
		switch (x)
		{
		case 1:
			cout << "Введите тип номера: \n";
			type = check.checktype();
			cout << "Введите порядковый номер номера: \n";
			count = check.checkcount();
			sNum << count;
			sSer << type;
			c = sNum.str();
			rnumber = type + c;
			j=list.findelem(rnumber);
			if (searchTr(pTreeCurrent, rnumber) != NULL)
			{
				if (j < (searchTr(pTreeCurrent, rnumber)->quantity))
				{
					addnewguest();
					cout << "Данные добавлены в список зарегистрированных постояльцев.\n";
					g_Hashes++;
					cout << "\nРегистрация вселения\n\n";
					cout << "Введите серию паспорта: \n";
					series = check.checkseries();
					cout << "Введите номер паспорта:\n";
					number = check.checknumber();
					ssNum << number;
					ssSer << series;
					num = ssNum.str();
					ser = ssSer.str();
					pnumber = ser + "-" + num;

					sNum.str(string());
					sSer.str(string());
					ssNum.str(string());
					ssSer.str(string());

					cout << "Введите тип номера: \n";
					type = check.checktype();
					cout << "Введите порядковый номер номера: \n";
					count = check.checkcount();
					sNum << count;
					sSer << type;
					c = sNum.str();
					rnumber = type + c;

					cout << "Введите дату заселения:\n";
					start = check.fillandcheckdate();
					cout << "Введите дату выселения:\n";
					end = check.fillandcheckdate();
					list.add(pnumber, rnumber, start, end);
					list.sorting();
					cout << "Данные добавлены.\n\n";
				}
				else
				{
					cout << "В данном номере нет свободных мест!\n\n";
				}
			}				
			else
			{
				cout << "Нет номера с таким номером.\n";
			}
			sNum.str(string());
			sSer.str(string());
			ssNum.str(string());
			ssSer.str(string());
			break;
		case 2:
			cout << "Введите серию паспорта: \n";
			series = check.checkseries();
			cout << "Введите номер паспорта:\n";
			number = check.checknumber();
			ssNum << number;
			ssSer << series;
			num = ssNum.str();
			ser = ssSer.str();
			pnumber = ser + "-" + num;
			j = list.findelemfordel(pnumber);
			if (j != 0)
			{
				g_Hashes--;
				delguest(pnumber);
				list.removedata(pnumber);
			}
			else
			{
				cout << "Постоялец с такими данными не был зарегистрирован!\n\n";
			}
			ssNum.str(string());
			ssSer.str(string());						
			break;
		case 3:
			list.show();
			break;
		case 4:
			cout << "Введите серию паспорта: \n";
			series = check.checkseries();
			cout << "Введите номер паспорта:\n";
			number = check.checknumber();
			ssNum << number;
			ssSer << series;
			num = ssNum.str();
			ser = ssSer.str();
			pnumber = ser + "-" + num;

			j = list.findelemfordel(pnumber);
			if (j != 0)
			{
				g_Hashes--;
				l = delguest(pnumber);
				if (l == 1)
				{
					cout << endl << "Данные постояльца удалены.\n";
				}
				else
				{
					cout << "Такого постояльца нет.\n";
				}
			}
			else
			{
				cout << "Вы не можете удалить данные о постояльце, поскольку он ещё зарегистрирован!\n\n";
			}
			ssNum.str(string());
			ssSer.str(string());			
			break;
		case 5:
			showHash();
			break;
		case 6:
			if (clearUsers() == true)
			{
				cout << endl << "Данные успешно удалены!\n";
			}
			break;
		case 7:
			cout << "Введите серию паспорта: \n";
			series = check.checkseries();
			cout << "Введите номер паспорта:\n";
			number = check.checknumber();
			ssNum << number;
			ssSer << series;
			num = ssNum.str();
			ser = ssSer.str();
			pnumber = ser + "-" + num;
			system("cls");
			if (searchpassport(pnumber) == 0)
			{
				cout << "Ничего не найдено!\n";
			}
			else
			{
				list.findelemp(pnumber);
			}
			ssNum.str(string());
			ssSer.str(string());
			break;
		case 8:
			if (searchRate() == 0)
			{
				cout << "Ничего не найдено!\n";
			}
			break;
		case 9:
			addClient(Number, Quantity, Room, Bathroom, Device);
			g_Trees++;
			pTreeCurrent = insert(pTreeCurrent, Number, Quantity, Room, Bathroom, Device);
			cout << "Гостиничный номер добавлен";
			break;
		case 10:
			cout << "Введите номер номера заселения постояльца\n";
			cout << "Введите тип номера: \n";
			type = check.checktype();
			cout << "Введите порядковый номер номера: \n";
			count = check.checkcount();
			sNum << count;
			sSer << type;
			c = sNum.str();
			rnumber = type + c;
			j = list.findelem(rnumber);
			if (j == 0)
			{
				if (searchTreeEl(pTreeCurrent, rnumber) != NULL)
				{
					pTreeCurrent = remove(pTreeCurrent, Number);
					cout << "Данные о номере удалены";
				}
				else
				{
					cout << "Нет номера с таким номером.\n";
				}
			}
			else
			{
				cout << "Вы не можете удалить данные об этом номере, потому что в нём живут постояльцы.\n\n";
			}	
			sNum.str(string());
			sSer.str(string());
			j = 0;
			break;
		case 11:
			if (g_Trees != 0)
			{
				display(0, pTreeCurrent);
			}
			else
			{
				cout << "Список пуст!";
			}
			break;
		case 12:
			clearTree(pTreeCurrent);
			cout << endl << "Данные были удалены!" << endl;
			break;
		case 13:
			cout << "Введите тип номера: \n";
			type = check.checktype();
			cout << "Введите порядковый номер номера: \n";
			count = check.checkcount();
			ssNum << count;
			ssSer << type;
			c = ssNum.str();
			Number = type + c;
			searchTreeEl(pTreeCurrent, Number);
			if (list.findelemhash(Number) == false)
			{
				cout << "Никто не живёт\n";
			}
			ssNum.str(string());
			ssSer.str(string());
			break;
		case 14:
			cout << endl << "Введите элемент оборудования: \n";
			cin.ignore(cin.rdbuf()->in_avail(), '\n');
			cin.getline(szTreeKeyPart, 50);
			if (searchTreePart(pTreeCurrent, szTreeKeyPart, 0))
			{
				cout << endl << "Найдено!" << endl << endl;
			}
			else
			{
				cout << endl << "Не найдено" << endl;
			}
			break;
		case 15:
			if (list.free())
			{
				cout << "Вы точно хотите загрузить данные из файла?\nПосле загрузки текущий список будет утерян!\n\n";
				cout << "1. Да;\n2. Нет;\n";
				l = check.checkc();
				if (l == 1)
				{
					list.clear();
					list.load();
					list.sorting();
					cout << "Данные загружены!\n";
				}
			}
			else
			{
				list.load();
				list.sorting();
				cout << "Данные загружены!\n";
			}
			break;
		case 16:
			
			loadrooms(Number, Quantity, Room, Bathroom, Device);
			cout << "Данные загружены!\n";
			
			break;
		case 17:
			loadguests();
			cout << "Данные загружены!\n";
			break;
		case 0:
			break;
		}
	} while (x);
	return 0;
}


int hashFunc(string key)
{
	int nSum = 0;
	int nSum1 = 0;
	const double multiplier = 2.3923;
	nSum1 = (int)((int)key[0] + ((int)key[1]) * multiplier
		+ ((int)key[2]) * pow(multiplier, 2) + ((int)key[3]) * pow(multiplier, 3)
		+ ((int)key[4]) * pow(multiplier, 4) + ((int)key[6]) * pow(multiplier, 6)
		+ ((int)key[7]) * pow(multiplier, 7)) % HASH_TABLE_SIZE;

	for (int i = 0; i < HASH_TABLE_SIZE - 1; i++)
	{
		nSum = (nSum1 + i * 1) % HASH_TABLE_SIZE;
		if (myHashTable[nSum].hashKey.empty())
		{
			return nSum;
		}
	}
	return nSum;
}

void addnewguest()
{
	Check check;
	string hashKey; //Ключ. Номер паспорта
	string Series;
	string Number;
	int nSeries; //серия паспорта
	int nNumber; //номер паспорта

	string name; //ФИО
	int year; //год рождения
	string  address; //адрес
	string purp; //цель прибытия

	cout << "Введите ФИО гостя: \n";
	name = check.checkname();

	cout << "Введите год рождения гостя: \n";
	year = check.checkyear();

	cout << "Введите адрес гостя:\n";
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, address);

	cout << "Введите цель прибытия гостя:\n";
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, purp);

	cout << "Введите серию паспорта: \n";
	nSeries = check.checkseries();

	cout << "Введите номер паспорта:\n";
	nNumber = check.checknumber();

	stringstream ssNum, ssSer;
	ssNum << nNumber;
	ssSer << nSeries;
	Number = ssNum.str();
	Series = ssSer.str();
	hashKey = Series + "-" + Number;

	int nHash = hashFunc(hashKey);
	myHashTable[nHash].hashKey = hashKey;
	myHashTable[nHash].name = name;
	myHashTable[nHash].year = year;
	myHashTable[nHash].address = address;
	myHashTable[nHash].purp = purp;
}

int delguest(string hashKey)
{

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (myHashTable[i].hashKey == hashKey)
		{
			myHashTable[i].hashKey.clear();
			myHashTable[i].name.clear();
			myHashTable[i].year = 0;
			myHashTable[i].address.clear();
			myHashTable[i].purp.clear();
			return 1;
		}
	}
	return 0;
}

void showHash()
{
	cout << endl;
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (!myHashTable[i].hashKey.empty())
			cout << "Номер паспорта: " << myHashTable[i].hashKey << "\nФИО: " << myHashTable[i].name << "\nГод рождения: " << myHashTable[i].year << "\nАдрес: " << myHashTable[i].address << "\nЦель приезда: " << myHashTable[i].purp << "\n_______________________________________________________" << endl;

	}
}

bool clearUsers()
{
	bool isFlag = true;
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		myHashTable[i].hashKey.clear();
		myHashTable[i].name.clear();
		myHashTable[i].year = 0;
		myHashTable[i].address.clear();
		myHashTable[i].purp.clear();
	}
	return isFlag;
}


int searchpassport(string hashKey)
{
	int nFlag = 0;
	

	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (myHashTable[i].hashKey == hashKey)
		{
			cout << "Номер паспорта: " << myHashTable[i].hashKey << "\nФИО: " << myHashTable[i].name << "\nГод рождения: " << myHashTable[i].year << "\nАдрес: " << myHashTable[i].address << "\nЦель приезда: " << myHashTable[i].purp << "\n_______________________________________________________\n";
			nFlag = 1;
		}
	}

	return nFlag;
}

int searchRate()
{
	Check check;
	int nFlag = 0;
	string name; // ФИО

	cout << endl << endl << "Введите ФИО: ";
	name = check.checkname();
	system("cls");
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		if (myHashTable[i].name == name)
		{
			cout << "Номер паспорта: " << myHashTable[i].hashKey << "\nФИО: " << myHashTable[i].name << "\n_______________________________________________________\n\n";
			nFlag = 1;
		}
	}
	return nFlag;
}

void loadguests()
{
	ifstream fin("guests.txt");
	int crash = 0;
	if (!fin)
	{
		cout << "Файл не открывается!\n";
	}
	else
	{
		string hashKey, Series, Number, name, address, purp, line, data;
		int year = 0;

		while (getline(fin, line))
		{
			int pos = line.find("-");
			Series = line.substr(0, pos);//присваиваем series часть строки до "-"

			line = line.substr(pos + 1);
			pos = line.find("|");
			Number = line.substr(0, pos); //присваиваем number часть строки до след "|"

			line = line.substr(pos + 1);
			pos = line.find("|");
			name = line.substr(0, pos); //присваиваем name часть строки до след "|"

			line = line.substr(pos + 1);
			pos = line.find("|");
			data = line.substr(0, pos); //присваиваем data часть строки до след "|"
			year = stoi(data); //преобразуем в int			

			line = line.substr(pos + 1);
			pos = line.find("|");
			address = line.substr(0, pos); //присваиваем address часть строки до след "|"

			line = line.substr(pos + 1);
			pos = line.find("|");
			purp = line.substr(0, pos); //присваиваем purp часть строки до след "|"

			hashKey = Series + "-" + Number;
			
			int nHash = hashFunc(hashKey);
			g_Hashes++;
			myHashTable[nHash].hashKey = hashKey;
			myHashTable[nHash].name = name;
			myHashTable[nHash].year = year;
			myHashTable[nHash].address = address;
			myHashTable[nHash].purp = purp;
			
		}
		fin.close();
	}
}

void addClient(string& Number, int& Quantity, int& Room, bool& Bathroom, string& Device)
{
	Check check;
	int count; //порядковый номер номера
	string c;//порядковый номер номера
	string type; //тип номера

	int quantity; //Кол-во мест
	int room; // Кол-во комнат
	bool bathroom; // Наличие санузла
	string 	device; // оборудование

	cout << "Введите тип номера: \n";
	type = check.checktype();

	cout << "Введите порядковый номер номера: \n";
	count = check.checkcount();

	stringstream ssNum, ssSer;
	ssNum << count;
	ssSer << type;
	c = ssNum.str();
	Number = type + c;

	cout << "Введите кол-во мест: \n";
	Quantity = check.checkquantity();

	cout << "Введите кол-во комнат: \n";
	Room = check.checkquantity();

	cout << "Введите информацию о наличии санузла: \n";
	Bathroom = check.checkbathroom();

	cout << "Введите через запятую имеющеся оборудование в номере: \n";
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, Device);
}
/* Возвращает высоту дерева, если она есть,
	*	Если указатель нулевой, возвращает 0
	*	(Если p - true, возвращает высоту, если false - 0)
	*/
unsigned char height(Node* p)
{
	return p ? p->height : 0;
}
/*
	*	Функция значения баланса. Возвращает разницу высоты деревьев
	*/
int bfactor(Node* p)
{
	return height(p->right) - height(p->left);
}
/* Функция восстанавливает корректное значение поля height заданного узла
*	(при условии, что значения этого поля в правом и левом дочерних узлах являются корректными)
*/
void fixheight(Node* p)
{
	unsigned char hl = height(p->left); unsigned char hr = height(p->right); p->height = (hl > hr ? hl : hr) + 1;
}

Node* rotateright(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

Node* rotateleft(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}
/* Балансировка дерева
	*	Если дисбаланс в правом поддереве, то
	*	-Если высота левого поддерева больше правого, то
	*	-Делаем правый поворот вокруг q
	*	Делаем поворот влево вокруг p
	*
	*	Если дисбаланс в левом, то
	*	-Тоже самое, только наоборот
	*	Делаем поворот право вокруг p
	*/
Node* balance(Node* p)
{
	fixheight(p);
	if (bfactor(p) == 2) //Дисбаланс справа
	{
		if (bfactor(p->right) < 0)
		{
			p->right = rotateright(p->right); // Поворот вокруг q вправо
		}
		return rotateleft(p); // Поворот вокруг p влево
	}
	if (bfactor(p) == -2) //Дисбаланс слева
	{
		if (bfactor(p->left) > 0) // Поворот вокруг q влево
		{
			p->left = rotateleft(p->left);
		}
		return rotateright(p); // Поворот вокруг p вправо
	}
	return p; //Нет дисбаланса, балансировка не нужна
}

Node* insert(Node* p, string Number, int Quantity, int Room, bool Bathroom, string Device)
{
	if (!p) // Если еще ничего нет, то создаем
	{
		return new Node(Number, Quantity, Room, Bathroom, Device);
	}

	if (Number < p->number) // Слева
	{
		p->left = insert(p->left, Number, Quantity, Room, Bathroom, Device);
	}
	else	// Справа
	{
		p->right = insert(p->right, Number, Quantity, Room, Bathroom, Device);
	}
	return balance(p); // Балансируем, по возвращению из рекурсии
}
/* Нахождение узла с минимальным ключем
	*	Это требуется для того, чтобы этот минимум подставить под удаляемый элемент
	*/
Node* findmin(Node* p)
{
	return p->left ? findmin(p->left) : p;
}
/* "Удаляем" минимальный элемент
	*	А именно - возвращаем указатель на правое его поддерево, при нахождении
	*	Сам элемент не удаляется, он нужен
	*/
Node* removemin(Node* p)
{
	if (p->left == 0)
	{
		return p->right;
	}
	p->left = removemin(p->left); return balance(p);
}

Node* remove(Node* p, string k)
{
	if (!p) // Если дерево пусто
	{
		cout << endl << "Данных нет" << endl;
		return p;
	}
	if (k == p->number)// Если k == p->number
	{
		Node* q = p->left; // Левое поддерево
		Node* r = p->right; // Правое поддерево 
		g_Trees--;
		delete p;
		if (!r) // Если правое поддерево пустое
		{
			return q;
		}
		Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		cout << endl << "Данные о клиенте удалены!" << endl;
		return balance(min);
	}
	else if (k < p->number)
	{
		p->left = remove(p->left, k);
	}
	else if (k > p->number)
	{

		p->right = remove(p->right, k);
	}
	else
	{

		cout << "Такого элемента нет!" << endl;
		return p;
	}

	return balance(p);
}

void display(int level, Node* p)
{
	if (p)
	{
		cout << "\nНомер гостиничного номера : " << p->number << "\nКол-во мест: " << p->quantity
			<< "\nКол-во комнат: " << p->room << "\nНаличие санузла: ";
		if (p->bathroom)
		{
			cout << "есть";
		}
		else
		{
			cout << "нет";
		}
		cout << "\nОборудование: " << p->device << "\n" << "_____________________________________________________________" << endl;
		display(level + 1, p->left);
		display(level + 1, p->right);
	}
}

void clearTree(Node* p)
{
	if (p != NULL)
	{
		if (p->left != NULL)
			clearTree(p->left);
		if (p->right != NULL)
			clearTree(p->right);
		delete p;
		g_Trees--;
	}
}

Node* searchTreeEl(Node* p, string key)
{
	
	while (NULL != p)
	{
		if (key == p->number)
		{
			cout << "\nНомер гостиничного номера : " << p->number << "\nКол-во мест: " << p->quantity
				<< "\nКол-во комнат: " << p->room << "\nНаличие санузла: ";
			if (p->bathroom)
			{
				cout << "есть";
			}
			else
			{
				cout << "нет";
			}
			cout << "\nОборудование: " << p->device << "\n" << "_____________________________________________________________" << endl;
			return p;
		}
		else if (key < p->number)
		{

			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	return p;
}

Node* searchTr(Node* p, string key)
{
	while (NULL != p)
	{
		if (key == p->number)
		{
			return p;
		}
		else if (key < p->number)
		{

			p = p->left;
		}
		else
		{
			p = p->right;
		}
	}
	return p;
}

int BMSearch(char* szHaystack, char* szNeedle, bool& f)
{
	int sourceLen = strlen(szHaystack);	// Длина исходного текста
	int templateLen = strlen(szNeedle);	// Длина слова, которое нужной найти

		// Неверные данные
	if (sourceLen == 0 || szHaystack == NULL || templateLen == 0 || szNeedle == NULL || templateLen > sourceLen) // Неверно задан исходный 	// Неверно задано слово для поиска
	{
		return -1;
	}
	map<char, int> offsetTable;
	for (int i = 0; i < templateLen - 1; i++) {
		offsetTable.insert(std::pair<char, int>(static_cast<char>(szNeedle[i]), templateLen - i - 1));
	}
	for (int i = 0; i <= 255; i++) {
		offsetTable.insert(std::make_pair(static_cast<char>(i), templateLen));
	}
	int i = templateLen - 1;
	int j = i;
	int k = i;
	while (j >= 0 && i <= sourceLen - 1) {
		j = templateLen - 1;
		k = i;
		while (j >= 0 && szHaystack[k] == szNeedle[j]) {
			k--;
			j--;
		}
		i += offsetTable.at(szHaystack[i]);
	}
	if (k >= sourceLen - templateLen) {
		return -1;
	}
	else {
		f = true;
		return 1;
	}
}

Node* searchTreePart(Node* p, char* szNeedle, int level)
{
	if (p)
	{
		char* szHaystack = new char[p->device.length() + 1];
		bool find = false;
		strcpy(szHaystack, p->device.c_str());
		BMSearch(szHaystack, szNeedle, find);
		if (find)
		{
			cout << "\nНомер гостиничного номера : " << p->number << "\nКол-во мест: " << p->quantity
				<< "\nКол-во комнат: " << p->room << "\nНаличие санузла: ";
			if (p->bathroom)
			{
				cout << "есть";
			}
			else
			{
				cout << "нет";
			}
			cout << "\nОборудование: " << p->device << "\n" << "_____________________________________________________________" << endl;

		}
		delete[] szHaystack;
		searchTreePart(p->left, szNeedle, level + 1);
		searchTreePart(p->right, szNeedle, level + 1);
	}
	return p;
}

void loadrooms(string& Number, int& Quantity, int& Room, bool& Bathroom, string& Device)
{
	ifstream fin("rooms.txt");
	int crash = 0;
	if (!fin)
	{
		cout << "Файл не открывается!\n";
	}
	else
	{
		string  Q, R, B, line;

		while (getline(fin, line))
		{
			int pos = line.find("|");
			Number = line.substr(0, pos);//присваиваем Number часть строки до "|"

			line = line.substr(pos + 1);
			pos = line.find("|");
			Q = line.substr(0, pos); //присваиваем Q часть строки до след "|"
			Quantity = stoi(Q); //преобразуем в int

			line = line.substr(pos + 1);
			pos = line.find("|");
			R = line.substr(0, pos); //присваиваем Q часть строки до след "|"
			Room = stoi(R); //преобразуем в int

			line = line.substr(pos + 1);
			pos = line.find("|");
			B = line.substr(0, pos); //присваиваем data часть строки до след "|"
			Bathroom = stoi(B); //преобразуем в int			

			line = line.substr(pos + 1);
			pos = line.find("|");
			Device = line.substr(0, pos); //присваиваем address часть строки до след "|"
			g_Trees++;
			pTreeCurrent = insert(pTreeCurrent, Number, Quantity, Room, Bathroom, Device);
		}
		fin.close();
	}
}

//функция для удаления списка
bool Dlist::clear()
{
	NOTE* temp = head;
	if (temp != NULL)
	{
		NOTE* next;
		while (temp != NULL)
		{
			next = temp->next;
			delete temp;
			temp = next;
			if (temp == NULL)
			{
				head = NULL;
				tail = NULL;
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}

bool Dlist::free()
{
	if (head != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

NOTE::NOTE(string pnumber, string rnumber, string start, string end)
{
	this->pnumber = pnumber;
	this->rnumber = rnumber;
	this->start = start;
	this->end = end;
}

//Функция для добавления элемента
void Dlist::add(string pnumber, string rnumber, string start, string end)
{
	if (head == NULL) //Проверяем, является ли список пустым
	{
		NOTE* contact = new NOTE(pnumber, rnumber, start, end); //если является, то данные становятся головой и хвостом списка
		head = contact;
		tail = contact;
	}
	else { //Если в списке что-то есть

		NOTE* contact = new NOTE(pnumber, rnumber, start, end);
		contact->next = head;
		head = contact;
	}
}

//Функция для вывода списка на экран
void Dlist::show()
{
	cout << "\nДанные о вселении и выселении :\n";
	NOTE* temp = head;

	while (temp != NULL) //выводим контакты, пока не дойдём до конца списка
	{
		cout << "____________________________________________________\n";
		cout << "Серия и номер паспорта:   " << temp->pnumber << endl;
		cout << "Номер номера:             " << temp->rnumber << endl;
		cout << "Дата заселения:           " << temp->start << endl;
		cout << "Дата выселения:           " << temp->end << endl;
		cout << "____________________________________________________\n";
		temp = temp->next;
	}

}

//Функция для загрузки данных из файла
void Dlist::load()
{
	ifstream fin("infolist.txt");
	int crash = 0;
	if (!fin)
	{
		cout << "Файл не открывается!\n";
	}
	else
	{
		string pnumber, rnumber, start, line, end;
		int h = 0, price = 0;
		while (getline(fin, line))
		{
			int pos = line.find("|");
			pnumber = line.substr(0, pos);

			line = line.substr(pos + 1);
			pos = line.find("|");
			rnumber = line.substr(0, pos);

			line = line.substr(pos + 1);
			pos = line.find("|");
			start = line.substr(0, pos);

			line = line.substr(pos + 1);
			end = line;

			add(pnumber, rnumber, start, end);
		}
		fin.close();
	}
}

void Dlist::removedata(string pnumber)
{
	NOTE* pCurrent = head;
	NOTE* pbehindCurrent = head;

	while (pCurrent)
	{
		if (pCurrent->pnumber == pnumber)
		{

			if (pCurrent == head) // удаляемы элемент первый
			{
				head = pCurrent->next;
				delete pCurrent;
			}
			else if (pCurrent->next == NULL) // удаляемый элемент последний
			{
				while (pbehindCurrent->next != pCurrent)
				{
					pbehindCurrent = pbehindCurrent->next;
				}
				pbehindCurrent->next = NULL;
				tail = pbehindCurrent;
				delete pCurrent;
			}
			else // удаляемый элемент в середине
			{
				while (pbehindCurrent->next != pCurrent)
				{
					pbehindCurrent = pbehindCurrent->next;
				}
				pbehindCurrent->next = pCurrent->next;
				delete pCurrent;
			}
			cout << endl << "удалено " << endl;
			return;
		}

		pCurrent = pCurrent->next;
	}
	cout << endl << "не найдено " << endl;
}



int Dlist::findelem(string num)
{
	NOTE* temp = head;
	int counter = 0;
	while (temp != NULL) //ищем номер в списке , пока не дойдём до конца
	{
		string number = temp->rnumber;
		if (number == num)
		{

			counter++;
		}
		temp = temp->next;
	}
	return counter;
}

void Dlist::findelemp(string num)
{
	NOTE* temp = head;
	while (temp != NULL) //ищем номер в списке , пока не дойдём до конца
	{
		string number = temp->pnumber;
		if (number == num)
		{
			cout << "Номер номера: " << temp->rnumber;
		}
		temp = temp->next;
	}
}

int Dlist::findelemfordel(string num)
{
	NOTE* temp = head;
	int counter = 0;
	while (temp != NULL) //ищем номер в списке , пока не дойдём до конца
	{
		string number = temp->pnumber;
		if (number == num)
		{

			counter++;
		}
		temp = temp->next;
	}
	return counter;
}

bool Dlist::findelemhash(string num)
{
	NOTE* temp = head;
	string pas;
	bool flag = false;
	while (temp != NULL) //ищем номер в списке контактов, пока не дойдём до конца
	{
		string number = temp->rnumber;
		if (number == num)
		{
			pas = temp->pnumber;
			for (int i = 0; i < HASH_TABLE_SIZE; i++)
			{
				if (myHashTable[i].hashKey == pas)
				{
					cout << "Номер паспорта: " << myHashTable[i].hashKey << "\nФИО: " << myHashTable[i].name << "\n_______________________________________________________\n";

				}
			}
		}
		temp = temp->next;
		flag = true;

	}
	return flag;
}


//Функция для сортировки
void Dlist::sorting()
{
	quickSort(&head);

}

//Функция для сортировки
void Dlist::quickSort(NOTE** headRef)
{
	(*headRef) = quickSortRecur(*headRef, getTail(*headRef));
	return;
}

//Нахождение хвоста
NOTE* Dlist::getTail(NOTE* cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return cur;
}

//Рекурсивная фенкция для быстрой сортировки
NOTE* Dlist::quickSortRecur(NOTE* head, NOTE* end)
{

	if (!head || head == end)
		return head;

	NOTE* newHead = NULL, * newEnd = NULL;
	NOTE* pivot = partition(head, end, &newHead, &newEnd);

	if (newHead != pivot)
	{
		NOTE* tmp = newHead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		newHead = quickSortRecur(newHead, tmp);

		tmp = getTail(newHead);
		tmp->next = pivot;
	}
	pivot->next = quickSortRecur(pivot->next, newEnd);

	return newHead;
}


//Функция для разделения списка(для быстрой сортировки)
//Разделяем список, принимая последний элемент в качестве оси
NOTE* Dlist::partition(NOTE* head, NOTE* end, NOTE** newHead, NOTE** newEnd)
{
	NOTE* pivot = end;
	NOTE* prev = NULL, * cur = head, * tail = pivot;
	string p, r, help1, help2;

	while (cur != pivot)
	{
		help1 = pivot->rnumber;
		help2 = cur->rnumber;
		p = help1.substr(1, 3);
		r = help2.substr(1, 3);
		if (r < p)
		{
			// Первый узел, который имеею меньшее значение становится головой
			if ((*newHead) == NULL)
				(*newHead) = cur;

			prev = cur;
			cur = cur->next;
		}
		else //если узел больше pivot
		{
			if (prev)
				prev->next = cur->next;
			NOTE* tmp = cur->next;
			cur->next = NULL;
			tail->next = cur;
			tail = cur;
			cur = tmp;
		}
	}

	//Самы маленьки элемент списка становится головой
	if ((*newHead) == NULL)
		(*newHead) = pivot;

	// находим новый последний элемент
	(*newEnd) = tail;

	// возвращаем разрешающий узел
	return pivot;
}



