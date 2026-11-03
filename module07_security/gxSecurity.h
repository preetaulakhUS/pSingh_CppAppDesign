#include <iostream>
#include "../module06_classes/gxClasses.h"
using namespace std;

//? user roles
class User{
	protected:
		string username;
		string password;
		string role;
		int loginAttempts;
		bool locked;
	public:
		User(string name="User",string pass="",string r="Regular"){
			username=name;password=pass;role=r;
			loginAttempts=0;locked=false;
		}
		string getUsername(){return username;}
		string getRole(){return role;}
		bool isLocked(){return locked;}

		bool tryLogin(string attempt){
			if (locked){cout<<cA<<"Account locked after too many attempts.\n"<<cR;return false;}
			if (attempt==password){loginAttempts=0;cout<<cC<<"Login successful: "<<username<<"\n"<<cR;return true;}
			loginAttempts++;
			cout<<cA<<"Wrong password ("<<loginAttempts<<"/3)\n"<<cR;
			if (loginAttempts>=3){locked=true;cout<<cA<<"Account '"<<username<<"' is now locked.\n"<<cR;}
			return false;
		}

		bool canView(){return role=="Regular"||role=="Admin";}
		bool canAdd(){return role=="Admin";}
		bool canDelete(){return role=="Admin";}

		void printProfile(){
			cout<<cD<<"Logged in as: "<<cT<<username<<cR<<"\n";
		}

		void viewRecord(City city){
			if (!canView()){cout<<cA<<"Access denied.\n"<<cR;return;}
			cout<<"[View] "<<city.name<<", population: "<<city.population<<", density: "<<city.density<<"\n";
		}
};

class RegularUser: public User{
	public:
		RegularUser(string name="User",string pass=""): User(name,pass,"Regular"){}
};

class Admin: public User{
	public:
		Admin(string name="Admin",string pass=""): User(name,pass,"Admin"){}

		void addRecord(City cities[],int &count,int maxSize,City newCity){
			if (count>=maxSize){cout<<cA<<"[Admin] Cannot add: array full.\n"<<cR;return;}
			cities[count]=newCity;
			count++;
			cout<<cC<<"[Admin] Added: "<<newCity.name<<"\n"<<cR;
		}

		void deleteRecord(City cities[],int &count,string targetName){
			int found=-1;
			for (int i=0;i<count;i++) if (cities[i].name==targetName){found=i;break;}
			if (found==-1){cout<<cA<<"[Admin] Not found: "<<targetName<<"\n"<<cR;return;}
			cout<<cC<<"[Admin] Deleted: "<<cities[found].name<<"\n"<<cR;
			for (int i=found;i<count-1;i++) cities[i]=cities[i+1];
			count--;
		}
};

//? sort cities alphabetically
void sortCitiesByName(City cities[],int count){
	for (int i=0;i<count-1;i++){
		for (int j=0;j<count-1-i;j++){
			if (cities[j].name>cities[j+1].name){
				City temp=cities[j];
				cities[j]=cities[j+1];
				cities[j+1]=temp;
			}
		}
	}
}

//? binary search
int binarySearch(int data[],int size,int target){
	int left=0, right=size-1;
	while (left<=right){
		int mid=left+(right-left)/2;
		if (data[mid]==target) return mid;
		if (data[mid]<target) left=mid+1;
		else right=mid-1;
	}
	return -1;
}

int binarySearchCity(City cities[],int size,string target){
	int left=0, right=size-1;
	while (left<=right){
		int mid=left+(right-left)/2;
		if (cities[mid].name==target) return mid;
		if (cities[mid].name<target) left=mid+1;
		else right=mid-1;
	}
	return -1;
}

//? set activeUser during login
RegularUser sessionGuest("Guest","");
Admin sessionAdmin("Admin","admin123");				//! password for admin login!
User *activeUser=nullptr;

bool loginPrompt(){
	int choice;
	while (true){
		cout<<cB<<string(42,'=')<<cR<<"\n";
		cout<<cH<<"          AZIMUTH GX ACCESS"<<cR<<"\n";
		cout<<cB<<string(42,'=')<<cR<<"\n";
		cout<<cT<<"  1) "<<cWh<<"Guest\n"
		    <<cT<<"  2) "<<cWh<<"Admin"<<(sessionAdmin.isLocked()?cA+" [Locked]":cWh)<<"\n"
		    <<cT<<"  0) "<<cWh<<"Exit\n"<<cR;
		cout<<cB<<"==> "<<cR;
		if (!(cin>>choice)){
			cin.clear();
			cin.ignore(10000,'\n');
			cout<<cA<<"Invalid option. Try again.\n\n"<<cR;
			continue;
		}
		cin.ignore(10000,'\n');
		if (choice==0) return false;
		if (choice==1){activeUser=&sessionGuest;return true;}
		if (choice==2){
			if (sessionAdmin.isLocked()){
				cout<<cA<<"\nAdmin account is locked.\n"<<cR;
				cout<<cT<<"1) Continue as Guest\n0) Exit\n"<<cR;
				cout<<cB<<"==> "<<cR;
				int lockChoice;
				if (cin>>lockChoice&&lockChoice==1){
					cin.ignore(10000,'\n');
					activeUser=&sessionGuest;
					return true;
				}
				cin.clear();
				cin.ignore(10000,'\n');
				return false;
			}
			while (true){
				cout<<cH<<"Password (0 to go back): "<<cR;
				string pass;getline(cin,pass);
				if (pass=="0") break;
				if (sessionAdmin.tryLogin(pass)){activeUser=&sessionAdmin;return true;}
				if (sessionAdmin.isLocked()){
					cout<<cA<<"\nAdmin account locked due to too many failed attempts.\n"<<cR;
					cout<<cT<<"1) Continue as Guest\n0) Exit\n"<<cR;
					cout<<cB<<"==> "<<cR;
					int lockChoice;
					if (cin>>lockChoice&&lockChoice==1){
						cin.ignore(10000,'\n');
						activeUser=&sessionGuest;
						return true;
					}
					cin.clear();
					cin.ignore(10000,'\n');
					return false;
				}
			}
		}
	}
}