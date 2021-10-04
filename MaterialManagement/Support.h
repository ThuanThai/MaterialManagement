#pragma once
#include "DataStructure.h";

void standardlize(string& obj) {
	while (isspace(obj[0])) {
		obj.erase(obj.begin() + 0);
	}
	while (isspace(obj[obj.length() - 1])) {
		obj.erase(obj.begin() + obj.length() - 1);
	}
	for (int i = 0; i < obj.length(); i++) {
		if (isspace(obj[i]) && isspace(obj[i + 1])) {
			obj.erase(obj.begin() + i + 1);
			i--;
		}
	}

	for (int i = 0; i < obj.length(); i++) {
		if (isspace(obj[i])) {
			i++;
			if (obj[i] >= 97 && obj[i] <= 122) {
				obj[i] -= 32;
			}
		}
		else {
			if (obj[i] >= 65 && obj[i] <= 90) {
				obj[i] += 32;
			}
		}
	}

	if (obj[0] >= 97 && obj[0] <= 122) {
		obj[0] -= 32;
	}
}

void Id_standardlize(string& obj) {
	while (isspace(obj[0])) {
		obj.erase(obj.begin() + 0);
	}
	while (isspace(obj[obj.length() - 1])) {
		obj.erase(obj.begin() + obj.length() - 1);
	}

	for (int i = 0; i <= 1; i++) {
		if (obj[i] >= 97 && obj[i] <= 122) {
			obj[i] -= 32;
		}
	}
}

Staff* newStaff() {
	Staff* staff = new Staff;
	staff->pLeft = NULL;
	staff->pRight = NULL;
	return staff;
}

void addStaff(Staff*& staff, Staff* p) {
	if (staff == NULL) {
		staff = p;
	}
	else {
		if (staff->sID < p->sID) {
			addStaff(staff->pRight, p);
		}
		else if (staff->sID > p->sID) {
			addStaff(staff->pLeft, p);
		}
	}
}