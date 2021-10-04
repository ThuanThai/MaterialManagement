#pragma once
#include "InputStream.h"

// =================ADD FUNCTION==================

string create_mId(MatList matlist);
int checkDuplicate(string mID, MatList matList);
void Material_add(MatList& matList);
void Mdisplay(MatList matList);

// =================DELETE FUNCTION=====================

void mDelete(MatList& matList);
int checkDelete(string id, MatList matList);

// =================EDIT FUNCTION==================

void mEdit(MatList& matList);

// =================STAFF FUNCTION==================
int create_sID(Staff* staff);
bool checkDuplicate_staff(Staff* staff, int id);
void sInput(StaffList& sList);

//============== STAFFDISPLAY ============
void transToArray(Staff* p, Staff* sList[], int& count);
void sDisplay(Staff* p[], int count);
void Sort(Staff* p[], int count);
void Free(Staff* p[], int count);

//======================= Delete Staff ====================
void sDelete(StaffList& sList);
//============== STAFFDISPLAY ============
void sDelete(StaffList& sList);
// ====================================================

void Menu() {
	MatList matList;
	StaffList sList;

	ReadFile(matList);
	sReadFile(sList);
	
	int val;
	bool flag = true;
	int choice;

	Staff* list[100];
	while (flag) {
		system("cls");
		cout << "1: Add Material\n";
		cout << "2: Show Material List\n";
		cout << "3: Delete Material\n";
		cout << "4: Edit Material\n";
		cout << "5: Add Staff\n";
		cout << "6: Display Staff\n";
		cout << "7: Delete Staff\n";
		cout << "0: Exit\n";

		cin >> choice;

		switch (choice)
		{
		case 1:
			if (matList.count == 100) {
				cout << "Not enough memory!\n";
			}
			else {
				Material_add(matList);
				cout << "update success!!!";
			}
			system("pause");
			break;
		case 2:
			Mdisplay(matList);
			system("pause");
			break;
		case 3:
			if (matList.count == 0) {
				cout << "Empty!!!\n";
				continue;
			}
			else {
				mDelete(matList);
				break;
			}
			
		case 4:
			if (matList.count == 0) {
				cout << "Empty!!!\n";
				continue;
			}
			else {
				mEdit(matList);
				break;
			}

		case 5: 
			sInput(sList);
			break;

		case 6:
			val = 0;
			transToArray(sList.tree, list, val);
			Sort(list, val);

			sDisplay(list, val);
			system("pause");

			Free(list, val);
			break;

		case 7:
			sDelete(sList);
			break;
		case 0:
			flag = false;
			break;

		default:
			cout << "Wrong choice\n";
			continue;
		}
	}
}

void Material_add(MatList& matList) {
	Material* material = new Material;
	
	material->mID = create_mId(matList);
	
	cout << "Enter Material Name: \n";
	cin.ignore();
	getline(cin, material->mName);
	standardlize(material->mName);

	cout << "Enter Material Unit: \n";
	getline(cin, material->unit);
	standardlize(material->unit);

	cout << ("Enter remain quantity\n");
	cin >> material->remain;
	
	matList.list[matList.count] = material;
	matList.count++;
}

string create_mId(MatList matlist) {
	string mID = "MA0000";
	do {
		for (int i = 2; i < mID.length(); i++) {
			mID[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (checkDuplicate(mID, matlist) >= 0);

	return mID;
}

int checkDuplicate(string mID, MatList matList) {
	for (int i = 0; i < matList.count; i++) {
		if (mID == matList.list[i]->mID) {
			return i;
		}
	}
	return -1;
}

void Mdisplay(MatList matList) {
	for (int i = 0; i < matList.count; i++) {
		cout << "\t\t ========= Material " << i + 1 << " ========= \n";
		cout << "Material ID: " << matList.list[i]->mID << endl;
		cout << "Name: " << matList.list[i]->mName << endl;
		cout << "Unit: " << matList.list[i]->unit << endl;
		cout << "Quantity in stock: " << matList.list[i]->remain << endl;
	}
}

int checkDelete(string id, MatList matList) {
	for (int i = 0; i < matList.count; i++) {
		if (id.compare(matList.list[i]->mID) == 0) {
			if (!matList.list[i]->check) {
				return i;
			}
		}
	}
	return -1;
}

void mDelete(MatList& matList) {
	string id;
	cout << "Enter ID: \n";
	cin >> id;
	Id_standardlize(id);

	if (checkDelete(id, matList) == -1) {
		cout << "Invalid ID !!!!\n";
		system("pause");
	} 
	else {
		for (int i = checkDelete(id, matList); i < matList.count - 1; i++) {
			matList.list[i]->mID = matList.list[i + 1]->mID;
			matList.list[i]->mName = matList.list[i + 1]->mName;
			matList.list[i]->unit = matList.list[i + 1]->unit;
			matList.list[i]->remain = matList.list[i + 1]->remain;
			matList.list[i]->check = matList.list[i + 1]->check;
		}
		matList.count--;
		cout << "Delete Success!!!\n";
		system("pause");
	}
}

void mEdit(MatList& matList) {
	string id;
	cout << "Enter ID: \n";
	cin >> id;
	Id_standardlize(id);

	if (checkDuplicate(id, matList) == -1) {
		cout << "Invalid ID !!!!\n";
		system("pause");
	}
	else {
		int pos = checkDuplicate(id, matList);
		cout << "\t\t====== Material Data =======\n";
		cout << "Material ID: " << matList.list[pos]->mID << endl;
		cout << "Name: " << matList.list[pos]->mName << endl;
		cout << "Unit: " << matList.list[pos]->unit << endl;
		cout << "Quantity in stock: " << matList.list[pos]->remain << endl;

		cout << "\nUpdate Data\n";

		cout << "\nMAterial Name: ";
		cin.ignore();
		getline(cin, matList.list[pos]->mName);
		standardlize(matList.list[pos]->mName);

		cout << "\nMaterial Unit: ";
		getline(cin, matList.list[pos]->unit);
		standardlize(matList.list[pos]->unit);

		cout << "Update Success\n";
		system("pause");
	}
}

//====================STAFF-LIST======================

bool checkDuplicate_staff(Staff* staff, int id) {
	if (staff == NULL) {
		return false;
	}
	else {
		if (id == staff->sID) {
			return true;
		}
		else {
			if (id < staff->sID) {
				checkDuplicate_staff(staff->pLeft, id);
			}
			else if (id > staff->sID) {
				checkDuplicate_staff(staff->pRight, id);
			}
		}
	}
}

int create_sID(Staff* staff) {
	int id;
	do {
		id = rand() % (999 - 100 + 1) + 100;
	} while (checkDuplicate_staff(staff, id));
	return id;
}


void sInput(StaffList& sList) {
	Staff* staff = newStaff();
	cin.ignore();
	cout << "First name: \n"; getline(cin, staff->FirstName); standardlize(staff->FirstName);
	cout << "Last name: \n"; getline(cin, staff->LastName); standardlize(staff->LastName);
	cout << "Gender: \n"; getline(cin, staff->gender); standardlize(staff->gender);
	staff->sID = create_sID(sList.tree);
	addStaff(sList.tree, staff);
	sList.count++;
}

void transToArray(Staff* p, Staff* sList[], int& count) {
	if (p != NULL)
	{
		sList[count] = new Staff;
		sList[count]->sID = p->sID;
		sList[count]->FirstName = p->FirstName;
		sList[count]->LastName = p->LastName;
		sList[count]->gender = p->gender;
		count++;
		transToArray(p->pLeft, sList, count);
		transToArray(p->pRight, sList, count);
	}
}

void swap(Staff* a, Staff* b) {
	Staff* temp = new Staff;
	temp->sID = a->sID;
	temp->FirstName = a->FirstName;
	temp->LastName = a->LastName;
	temp->gender = a->gender;

	a->sID = b->sID;
	a->FirstName = b->FirstName;
	a->LastName = b->LastName;
	a->gender = b->gender;

	b->sID = temp->sID;
	b->FirstName = temp->FirstName;
	b->LastName = temp->LastName;
	b->gender = temp->gender;

	delete temp;
}

void Sort(Staff* p[], int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (p[i]->FirstName > p[j]->FirstName) {
				swap(p[i], p[j]);
			}
			else if (p[i]->FirstName == p[j]->FirstName) {
				if (p[i]->LastName > p[j]->LastName) {
					swap(p[i], p[j]);
				}
			}
		}
	}
}

void sDisplay(Staff* p[], int count) {
	for (int i = 0; i < count; i++) {
		cout << "\n\t\t======== Staff " << i + 1 << " ==========\n";
		cout << "ID: " << p[i]->sID << endl;
		cout << "First name: " << p[i]->FirstName << endl;
		cout << "Last name: " << p[i]->LastName << endl;
		cout << "Gender: " << p[i]->gender << endl;
	}
}

void Free(Staff* p[], int count) {
	for (int i = 0; i < count; i++) {
		delete p[i];
	}
}

//===================== DELETE ==================

void spDelete(Staff*& x, Staff*& y) {
	if (x->pLeft != NULL) {
		spDelete(x->pLeft, y);
	}
	else {
		swap(x, y);
		y = x;
		x = x->pRight;
	}
}

void deleteStaff(Staff*& p, int id) {
	if (p != NULL) {
		if (p->sID == id) {
			Staff* temp = p;
			if (p->pLeft == NULL) {
				p = p->pRight;
			} 
			else if (p->pRight == NULL) {
				p = p->pLeft;
			}
			else if (p->pRight != NULL && p->pLeft != NULL) {
				spDelete(p->pRight, temp);
			}
			delete temp;
		}
		else if (p->sID > id) {
				deleteStaff(p->pLeft, id);
		}
		else if (p->sID < id) {
			deleteStaff(p->pRight, id);
		}
	}
}

//======================= Delete Staff ====================
void sDelete(StaffList& sList) {
	int id;
	cout << "Enter staff ID: \n";
	cin >> id;
	if (checkDuplicate_staff(sList.tree, id)) {
		deleteStaff(sList.tree, id);
		sList.count--;
		cout << "Success Delete\n";
	}
	else {
		cout << "ID is invalid!!!\n";
	}
	system("pause");
}




