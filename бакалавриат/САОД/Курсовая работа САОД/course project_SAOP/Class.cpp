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

//������� ��� ���������� ��������
void Dlist::add(string pnumber, string rnumber, string start, string end)
{
	if (head == NULL) //���������, �������� �� ������ ������
	{
		NOTE* contact = new NOTE(pnumber, rnumber, start, end); //���� ��������, �� ������ ���������� ������� � ������� ������
		head = contact;
		tail = contact;
	}
	else { //���� � ������ ���-�� ����

		NOTE* contact = new NOTE(pnumber, rnumber, start, end);
		contact->next = head;
		head = contact;
	}
}

//������� ��� ������ ������ �� �����
void Dlist::show()
{
	cout << "\n������ � �������� � ��������� :\n";
	NOTE* temp = head;

	while (temp != NULL) //������� ��������, ���� �� ����� �� ����� ������
	{
		cout << "____________________________________________________\n";
		cout << "����� � ����� ��������:   " << temp->pnumber << endl;
		cout << "����� ������:             " << temp->rnumber << endl;
		cout << "���� ���������:           " << temp->start << endl;
		cout << "���� ���������:           " << temp->end << endl;
		cout << "____________________________________________________\n";
		temp = temp->next;
	}

}

//������� ��� �������� ������ �� �����
void Dlist::load()
{
	ifstream fin("infolist.txt");
	int crash = 0;
	if (!fin)
	{
		cout << "���� �� �����������!\n";
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

	cout << "������� ����� ��������: \n";
	series = check.checkseries();
	cout << "������� ����� ��������:\n";
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

			if (pCurrent == head) // �������� ������� ������
			{
				head = pCurrent->next;
				delete pCurrent;
			}
			else if (pCurrent->next == NULL) // ��������� ������� ���������
			{
				while (pbehindCurrent->next != pCurrent)
				{
					pbehindCurrent = pbehindCurrent->next;
				}
				pbehindCurrent->next = NULL;
				tail = pbehindCurrent;
				delete pCurrent;
			}
			else // ��������� ������� � ��������
			{
				while (pbehindCurrent->next != pCurrent)
				{
					pbehindCurrent = pbehindCurrent->next;
				}
				pbehindCurrent->next = pCurrent->next;
				delete pCurrent;
			}
			cout << endl << "������� " << endl;
			return;
		}

		pCurrent = pCurrent->next;
	}
	cout << endl << "�� ������� " << endl;
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

//������� ��� ����������
void Dlist::sorting()
{
	quickSort(&head);

}

//������� ��� ����������
void Dlist::quickSort(NOTE** headRef)
{
	(*headRef) = quickSortRecur(*headRef, getTail(*headRef));
	return;
}

//���������� ������
NOTE* Dlist::getTail(NOTE* cur)
{
	while (cur != NULL && cur->next != NULL)
		cur = cur->next;
	return cur;
}

//����������� ������� ��� ������� ����������
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


//������� ��� ���������� ������(��� ������� ����������)
//��������� ������, �������� ��������� ������� � �������� ���
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
			// ������ ����, ������� ����� ������� �������� ���������� �������
			if ((*newHead) == NULL)
				(*newHead) = cur;

			prev = cur;
			cur = cur->next;
		}
		else //���� ���� ������ pivot
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

	//���� �������� ������� ������ ���������� �������
	if ((*newHead) == NULL)
		(*newHead) = pivot;

	// ������� ����� ��������� �������
	(*newEnd) = tail;

	// ���������� ����������� ����
	return pivot;
}

int Dlist::findelem(string num)
{
	NOTE* temp = head;
	int counter = 0;
	while (temp != NULL) //���� ����� � ������ ���������, ���� �� ����� �� �����
	{
		string number = temp->rnumber;
		if (number == num)
		{
			cout << "\n����� ������!\n";
			cout << "____________________________________________________\n";
			cout << "����� � ����� ��������:   " << temp->pnumber << endl;
			cout << "����� ������:             " << temp->rnumber << endl;
			cout << "���� ���������:           " << temp->start << endl;
			cout << "���� ���������:           " << temp->end << endl;
			cout << "____________________________________________________\n";
			counter++;
		}
		if (number != num && temp->next == NULL)
		{
			cout << "������ ������ ���!\n";
		}
		temp = temp->next;
	}
	return counter;
}

