#include "Class.h"
#include "Check.h"
#include <ctype.h>
#include <sstream> 
#include "main.cpp"

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
		unsigned short int date[6];
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

void Dlist::remove()
{
	NOTE* pCurrent = head;
	NOTE* pbehindCurrent = head;
	string pnumber;
	Check check;
	int series, number;
	string ser, num;
	stringstream ssNum, ssSer;

	cout << "Введите серию паспорта: \n";
	series = check.checkseries();
	cout << "Введите номер паспорта:\n";
	number = check.checknumber();
	ssNum << number;
	ssSer << series;
	num = ssNum.str();
	ser = ssSer.str();
	pnumber = ser + "-" + num;

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

int Dlist::findelem(string num)
{
	NOTE* temp = head;
	int counter = 0;
	while (temp != NULL) //ищем номер в списке контактов, пока не дойдём до конца
	{
		string number = temp->rnumber;
		if (number == num)
		{
			cout << "\nНомер найден!\n";
			cout << "____________________________________________________\n";
			cout << "Серия и номер паспорта:   " << temp->pnumber << endl;
			cout << "Номер номера:             " << temp->rnumber << endl;
			cout << "Дата заселения:           " << temp->start << endl;
			cout << "Дата выселения:           " << temp->end << endl;
			cout << "____________________________________________________\n";
			counter++;
		}
		if (number != num && temp->next == NULL)
		{
			cout << "Такого номера нет!\n";
		}
		temp = temp->next;
	}
	return counter;
}

