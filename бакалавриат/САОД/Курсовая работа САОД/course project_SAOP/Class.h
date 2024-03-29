/*Class.h*/
#pragma once
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Dlist;

class NOTE
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

class Dlist
{
private:
	NOTE* head = NULL;
	NOTE* tail = NULL;
public:
	void add(string, string, string, string);
	void show();
	void load();
	void remove();
	bool free();
	void sorting();
	//void sort(NOTE*& , NOTE*& );
	void quickSort(NOTE** headRef);
	NOTE* getTail(NOTE* cur);
	NOTE* quickSortRecur(NOTE* head, NOTE* end);
	NOTE* partition(NOTE* head, NOTE* end, NOTE** newHead, NOTE** newEnd);
	int findelem(string);
};
