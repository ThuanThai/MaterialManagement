#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Material {
	string mID;
	string mName;
	string unit;
	int remain;
	bool check;
};

struct MatList {
	Material* list[100];
	int count = 0;
};

struct sBill {
	string mID;
	int quanitity;
	int price;
	float VAT;
	bool state;
};

struct sBillList {
	sBill sbill[20];
	int count = 0;
};

struct Bill {
	int bID;
	string Date;
	char type;
	sBillList sbList;
	Bill* pNext;
};

struct BillList {
	Bill* pHead = NULL; 
	int count = 0;
};

struct Staff {
	int sID;
	string FirstName;
	string LastName;
	string gender;
	BillList bList;
	Staff* pLeft;
	Staff* pRight;
};

struct StaffList {
	Staff* tree = NULL;
	int count = 0;
};
