#pragma once
#include "Support.h"
#include <fstream>

void ReadFile(MatList& matList) {
	ifstream FileIn;
	FileIn.open("Material.txt", ios::in);
	while (!FileIn.eof()) {
		Material* p = new Material;
		getline(FileIn, p->mID, ',');
		getline(FileIn, p->mName, ',');
		getline(FileIn, p->unit, ',');
		FileIn >> p->remain;
		FileIn.ignore();
		FileIn >> p->check;
		FileIn.ignore();
		matList.list[matList.count] = p;
		matList.count++;
	}
	FileIn.close();
}

void sReadFile(StaffList& sList) {
	ifstream FileIn;
	FileIn.open("Staff.txt", ios::in);
	while (!FileIn.eof()) {
		Staff* p = newStaff();
		FileIn >> p->sID;
		FileIn.ignore();

		getline(FileIn, p->FirstName, ',');
		getline(FileIn, p->LastName, ',');
		getline(FileIn, p->gender, '\n');

		addStaff(sList.tree, p);
		sList.count++;
	}
	FileIn.close();
}