#include <iostream>
#include "../module08_validation/gxValidation.h"
using namespace std;

// demo entries
City demoEntries[10]={
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
	string name=getString("Enter username: ");
	RegularUser testUser(name,"secret");
	cout<<"(Hint: correct password is 'secret')\n";
	for (int i=0;i<4;i++){
		string pass=getString("Enter password attempt "+to_string(i+1)+": ");
		bool ok=testUser.tryLogin(pass);
		if (ok) break;
	}
	system("pause");
}

void testRolePermissions(){
	system("cls");
	cout<<"Role Permissions Test\n";
	cout<<"Select role to test:\n1) Regular User\n2) Admin\n";
	int choice=getInt("==> ",1,2);
	User *u;
	if (choice==1) u=&demoRegular;
	else u=&demoAdmin;
	u->printProfile();
	cout<<"  canView:   "<<(u->canView()?"yes":"no")<<"\n";
	cout<<"  canAdd:    "<<(u->canAdd()?"yes":"no")<<"\n";
	cout<<"  canDelete: "<<(u->canDelete()?"yes":"no")<<"\n";
	string searchName=getString("Enter a city name to view (e.g. Oakland): ");
	int idx=binarySearchCity(demoEntries,demoCount,searchName);
	if (idx!=-1) u->viewRecord(demoEntries[idx]);
	else cout<<"City not found in demo entries.\n";
	system("pause");
}

void testBinarySearch(){
	system("cls");
	cout<<"Entry Binary Search Test\n";
	cout<<"Demo entries:\n";
	for (int i=0;i<demoCount;i++) cout<<"  "<<demoEntries[i].name<<"\n";
	string target=getString("Enter city name to search: ");
	int idx=binarySearchCity(demoEntries,demoCount,target);
	if (idx!=-1)
		cout<<"Found '"<<target<<"' at index "<<idx<<" | pop: "<<demoEntries[idx].population<<"\n";
	else
		cout<<"'"<<target<<"' not found.\n";
	system("pause");
}

void testAdminActions(){
	system("cls");
	cout<<"Admin Add & Delete Test\n";
	City localEntries[10];
	int localCount=demoCount;
	for (int i=0;i<demoCount;i++) localEntries[i]=demoEntries[i];

	cout<<"Current entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localEntries[i].name<<"\n";

	City newCity;
	newCity.name=getString("\nEnter city name to add: ");
	newCity.population=getInt("Enter population: ",1,99999999);
	newCity.density=getDouble("Enter density (people/km^2): ",0.1,99999.9);
	newCity.latitude=0;newCity.longitude=0;newCity.zips="N/A";

	demoAdmin.addRecord(localEntries,localCount,10,newCity);
	sortCitiesByName(localEntries,localCount);
	cout<<"Updated entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localEntries[i].name<<"\n";

	string delName=getString("\nEnter city name to delete: ");
	demoAdmin.deleteRecord(localEntries,localCount,delName);
	cout<<"Updated entries:\n";
	for (int i=0;i<localCount;i++) cout<<"  "<<localEntries[i].name<<"\n";
	system("pause");
}

void testIntBinarySearch(){
	system("cls");
	cout<<"Integer Binary Search Test\n";
	int ids[7]={101,204,305,412,519,623,780};
	cout<<"Sorted IDs: ";
	for (int i=0;i<7;i++) cout<<ids[i]<<" ";
	cout<<"\n";
	int target=getInt("Enter an ID to search: ",1,999999);
	int idx=binarySearch(ids,7,target);
	if (idx!=-1) cout<<"Found "<<target<<" at index "<<idx<<"\n";
	else cout<<target<<" not in list.\n";
	system("pause");
}

int main(){
	loadDB();
	int choice;
	do {
		system("cls");
		cout<<"Module 07 Test\n";
		cout<<"1) Login lockout\n";
		cout<<"2) Role permissions\n";
		cout<<"3) Binary search (cities)\n";
		cout<<"4) Admin add & delete\n";
		cout<<"5) Binary search (integers)\n";
		cout<<"0) Exit\n";
		choice=getInt("==> ",0,5);
		switch(choice){
			case 1: testLoginLockout(); break;
			case 2: testRolePermissions(); break;
			case 3: testBinarySearch(); break;
			case 4: testAdminActions(); break;
			case 5: testIntBinarySearch(); break;
			case 0: break;
			default: break;
		}
	} while(choice!=0);
}