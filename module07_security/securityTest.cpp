#include <iostream>
#include "gxSecurity.h"
using namespace std;

// demo records
City demoRecords[10]={
	{"Berkeley",37.87,-122.27,120257,4450.9,"94704"},
	{"Fremont",37.52,-121.98,228295,1128.6,"94536"},
	{"Oakland",37.79,-122.21,439418,3031.6,"94607"},
	{"San Jose",37.33,-121.89,1013240,2148.4,"95101"}
};
int demoCount=4;

// demo users
RegularUser demoRegular("Preetinder","pass123");
Admin demoAdmin("Dr. Singh","admin999");

void testLoginLockout(){
	system("cls");
	cout<<"Login Lockout Test\n";
	string name, pass;
	cout<<"Enter username: ";cin>>name;
	RegularUser testUser(name,"secret");
	cout<<"(Hint: correct password is 'secret')\n";
	for (int i=0;i<4;i++){
		cout<<"Enter password attempt "<<(i+1)<<": ";
		cin>>pass;
		bool ok=testUser.tryLogin(pass);
		if (ok) break;
	}
	system("pause");
}

void testRolePermissions(){
	system("cls");
	cout<<"Role Permissions Test\n";
	cout<<"Select role to test:\n1) Regular User\n2) Admin\n==> ";
	int choice;cin>>choice;
	User *u;
	if (choice==1) u=&demoRegular;
	else u=&demoAdmin;
	u->printProfile();
	cout<<"  canView:   "<<(u->canView()?"yes":"no")<<"\n";
	cout<<"  canAdd:    "<<(u->canAdd()?"yes":"no")<<"\n";
	cout<<"  canDelete: "<<(u->canDelete()?"yes":"no")<<"\n";
	string searchName;
	cout<<"Enter a city name to view (e.g. Oakland (case sensitive)): ";
	cin.ignore();getline(cin,searchName);
	int idx=binarySearchCity(demoRecords,demoCount,searchName);
	if (idx!=-1) u->viewRecord(demoRecords[idx]);
	else cout<<"City not found in demo records.\n";
	system("pause");
}

void testBinarySearch(){
	system("cls");
	cout<<"City Binary Search Test\n";
	cout<<"Demo records (sorted):\n";
	for (int i=0;i<demoCount;i++) cout<<"  "<<demoRecords[i].name<<"\n";
	string target;
	cout<<"Enter city name to search: ";
	cin.ignore();getline(cin,target);
	int idx=binarySearchCity(demoRecords,demoCount,target);
	if (idx!=-1)
		cout<<"Found '"<<target<<"' at index "<<idx<<" | population: "<<demoRecords[idx].population<<"\n";
	else
		cout<<"'"<<target<<"' not found.\n";
	system("pause");
}

void testAdminActions(){
	system("cls");
	cout<<"Admin Add & Delete Test\n";
	City localRecords[10];
	int localCount=demoCount;
	for (int i=0;i<demoCount;i++) localRecords[i]=demoRecords[i];

	cout<<"Current entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localRecords[i].name<<"\n";

	string newName;
	cout<<"\nEnter city name to add: ";
	cin.ignore();getline(cin,newName);
	City newCity;
	newCity.name=newName;
	cout<<"Enter population: ";cin>>newCity.population;
	cout<<"Enter density: ";cin>>newCity.density;
	newCity.latitude=0;newCity.longitude=0;newCity.zips="null";

	demoAdmin.addRecord(localRecords,localCount,10,newCity);
	sortCitiesByName(localRecords,localCount);
	cout<<"Updated entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localRecords[i].name<<"\n";

	string delName;
	cout<<"\nEnter city name to delete: ";
	cin.ignore();getline(cin,delName);
	demoAdmin.deleteRecord(localRecords,localCount,delName);
	cout<<"Updated entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localRecords[i].name<<"\n";
	system("pause");
}

void testIntBinarySearch(){
	system("cls");
	cout<<"Integer Binary Search Test\n";
	int ids[7]={101,204,305,412,519,623,780};
	cout<<"Sorted IDs: ";
	for (int i=0;i<7;i++) cout<<ids[i]<<" ";
	cout<<"\n";
	int target;
	cout<<"Enter an ID to search: ";cin>>target;
	int idx=binarySearch(ids,7,target);
	if (idx!=-1) cout<<"Found "<<target<<" at index "<<idx<<"\n";
	else cout<<target<<" not in list.\n";
	system("pause");
}

int main(){
	loadDB();
	int i;
	do {
		system("cls");
		cout<<"Module 07 Test\n";
		cout<<"1) Login lockout\n";
		cout<<"2) Role permissions\n";
		cout<<"3) Binary search (cities)\n";
		cout<<"4) Admin add & delete\n";
		cout<<"5) Binary search (integers)\n";
		cout<<"0) Exit\n";
		cout<<"==> ";cin>>i;
		switch(i){
			case 1: testLoginLockout(); break;
			case 2: testRolePermissions(); break;
			case 3: testBinarySearch(); break;
			case 4: testAdminActions(); break;
			case 5: testIntBinarySearch(); break;
			case 0: break;
			default: break;
		}
	} while(i!=0);
}