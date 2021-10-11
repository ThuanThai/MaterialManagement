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

//================ Edit Staff ==================
void sEdit(StaffList& sList);
//=========== BILL===================
void createSbList(sBillList& sbill, MatList& mList);
void EstablishBill(StaffList& sList, MatList& mList);
void showBill(StaffList sList);
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
		cout << "8: Edit Staff\n";
		cout << "9: Create Bill\n";
		cout << "10: show Bill\n";
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

		case 8:
			sEdit(sList);
			break;
		case 9:
			EstablishBill(sList, matList);
			break;
		case 10:
			showBill(sList);
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

//================ Edit Staff ==================

void EditStaff(Staff* p, int id) {
	if (p != NULL) {
		if (p->sID == id) {
			cin.ignore();
			cout << "First name: \n"; getline(cin, p->FirstName); standardlize(p->FirstName);
			cout << "Last name: \n"; getline(cin, p->LastName); standardlize(p->LastName);
			cout << "Gender: \n"; getline(cin, p->gender); standardlize(p->gender);
		}
		else if (p->sID > id) {
			EditStaff(p->pLeft, id);
		}
		else if (p->sID < id) {
			EditStaff(p->pRight, id);
		}
	}
}

void Find(Staff* p, int id) {
	if (p != NULL) {
		if (p->sID == id) {
			cout << "\n" << p->sID << endl;
			cout << p->FirstName << endl;
			cout << p->LastName << endl;
			cout << p->gender << endl;
		}
		else if (p->sID < id) {
			Find(p->pRight, id);
		}
		else if (p->sID > id) {
			Find(p->pLeft, id);
		}
	}
}

void sEdit(StaffList& sList) {
	int id;
	cout << "Enter staff ID: \n";
	cin >> id;
	if (checkDuplicate_staff(sList.tree, id)) {
		Find(sList.tree, id);
		EditStaff(sList.tree, id);
		cout << "Edit Success" << endl;
	}
	else {
		cout << "ID is invalid!!!\n";
	}
	system("pause");
}


//===================== BILL-FUCTION ===================
Staff* bFind(Staff* p, int id) {
	if (p != NULL) {
		if (p->sID == id) {
			return p;
		}
		else if (p->sID < id) {
			bFind(p->pRight, id);
		}
		else if (p->sID > id) {
			bFind(p->pLeft, id);
		}
	}
	else {
		return NULL;
	}	
}

Bill* NewBIll() {
	Bill* bill = new Bill;
	bill->pNext = NULL;
	return bill;
}

bool checkDublicate_Bill(Bill* pHead, string id) {
	for (Bill* k = pHead; k != NULL; k = k->pNext) {
		if (k->bID == id) {
			return true;
		}
	}
	return false;
}

string create_bId(Bill* bill) {
	string bID = "BL0000";
	do {
		for (int i = 2; i < bID.length(); i++) {
			bID[i] = rand() % (57 - 48 + 1) + 48;
		}
	} while (checkDublicate_Bill(bill, bID));

	return bID;
}

void addBill(Bill*& pHead, Bill* p) {
	if (pHead == NULL) {
		pHead = p;
	}
	else {
		for (Bill* bill = pHead; bill != NULL; bill = bill->pNext) {
			if (bill->pNext == NULL) {
				bill->pNext = p;
			}
		}
	}
}

void updateQuantity(sBill*& p, MatList& mList, Bill* bill ,int i) {
	if (bill->type == 'I') {
		cin >> p->quanitity;
		mList.list[i]->remain += p->quanitity;
	}
	else if (bill->type == 'E') {
		bool flag = true;
		while (flag) {
			cin >> p->quanitity;
			int temp = p->quanitity;
			if (mList.list[i]->remain >= temp) {
				mList.list[i]->remain -= temp;
				break;
			}
			else {
				cout << "The quantity in stock is not enough!!!\n";
				cout << "The quantity in stock of this material: " << mList.list[i]->remain << endl;
				cout << "please choose another quantity!\n";
				system("pause");
				continue;
			}
		}
	}
}

void createSbList(sBillList& sbill, Bill*& bill, MatList& mList) {
	string id;
	cout << "Enter Material ID: " << endl;
	cin >> id;
	Id_standardlize(id);

	if (checkDuplicate(id, mList) >= 0) {
		int i = checkDelete(id, mList);
		bool flag = true;
		int choice;
		sBill* p = new sBill;
		cout << "Enter quantity: \n";
		updateQuantity(p, mList, bill, i);
		cout << "Enter price: \n";
		cin >> p->price;
		cout << "Enter VAT: \n";
		cin >> p->VAT;

		while (flag) {
			system("cls");
			cout << "Enter the state of material\n";
			cout << "1: sold good\n";
			cout << "2: returned good\n";
			cin >> choice;
			switch (choice)
			{
			case 1:
				p->state = 1;
				flag = false;
				break;

			case 2:
				p->state = 0;
				flag = false;
				break;

			default:
				continue;
			}
		}
		sbill.arr[sbill.count] = p;
		sbill.count++;
		cout << "Success update specified bill\n";
	}
	else {
		cout << "Invalid material ID!!!\n";
	}
}

void EstablishBill(StaffList& sList, MatList& mList) {
	int id;
	cout << "Enter Staff ID: "; 
	cin >> id;
	Staff* staff = bFind(sList.tree, id);

	if (staff == NULL) {
		cout << "Invalid ID!!!" << endl;
	} 
	else {
		Bill* bill = NewBIll();
		bool flag = true;
		while (flag) {
			system("cls");
			cout << "Select type of Bill\n";
			cout << "1: imported invoice\n";
			cout << "2: exported invoice\n";
			
			int choice;
			cin >> choice;
			
			switch (choice)
			{
			case 1:
				cout << "Type of Bill: imported\n";
				bill->type = 'I';
				flag = false;
				break;

			case 2: 
				cout << "Type of Bill: exported\n";
				bill->type = 'E';
				flag = false;
				break;

			default:
				cout << "Wrong choice!!!!\n";
				continue;
			}
		}
		bill->bID = create_bId(staff->bList.pHead);
		cin.ignore();
		cout << "enter date added: \n"; 
		getline(cin, bill->Date);

		addBill(staff->bList.pHead, bill);
		staff->bList.count++;

		cout << "Success creating Bill!!!\n";
		system("pause");

		cout << "Invoice: " << bill->type << "\nBill ID: " << bill->bID << "\nDate: " << bill->Date << endl;
		cout << "\n";

		Mdisplay(mList);
		createSbList(bill->sbList, bill, mList);
	}
	system("pause");
}

void showSBill(sBillList sbill) {
	for (int i = 0; i < sbill.count; i++) {
		cout << "ID: " << sbill.arr[i]->mID<< endl;
		cout << "Price" << sbill.arr[i]->price << endl;
		cout << "Quantity: " << sbill.arr[i]->quanitity << endl;
		cout << "VAT: " << sbill.arr[i]->VAT << endl;
		cout << "State: " << (sbill.arr[i]->state ? "sold goods" : "return goods") << endl;
	}
}

void showBill(StaffList sList) {
	int id;
	cout << "Enter Staff ID: ";
	cin >> id;
	Staff* staff = bFind(sList.tree, id);
	if (staff == NULL) {
		cout << "Invalid ID!!!" << endl;
	}
	else {
		for (Bill* p = staff->bList.pHead; p != NULL; p = p->pNext) {
			cout << "Bill ID: " << p->bID << endl;
			cout << "Date: " << p->Date << endl;
			cout << "Type: " << p->type << endl;
			showSBill(p->sbList);
		}
	}
	system("pause");
}






