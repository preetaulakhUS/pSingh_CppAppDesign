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
			if (locked){cout<<"Account locked after too many attempts.\n";return false;}
			if (attempt==password){loginAttempts=0;cout<<"Login successful: "<<username<<"\n";return true;}
			loginAttempts++;
			cout<<"Wrong password ("<<loginAttempts<<"/3)\n";
			if (loginAttempts>=3){locked=true;cout<<"Account '"<<username<<"' is now locked.\n";}
			return false;
		}

		bool canView(){return role=="Regular"||role=="Admin";}
		bool canAdd(){return role=="Admin";}
		bool canDelete(){return role=="Admin";}

		void printProfile(){
			cout<<"User: "<<username<<" | Role: "<<role<<" | Locked: "<<(locked?"yes":"no")<<"\n";
		}

		void viewRecord(City city){
			if (!canView()){cout<<"Access denied.\n";return;}
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
			if (count>=maxSize){cout<<"[Admin] Cannot add: array full.\n";return;}
			cities[count]=newCity;
			count++;
			cout<<"[Admin] Added: "<<newCity.name<<"\n";
		}

		void deleteRecord(City cities[],int &count,string targetName){
			int found=-1;
			for (int i=0;i<count;i++) if (cities[i].name==targetName){found=i;break;}
			if (found==-1){cout<<"[Admin] Not found: "<<targetName<<"\n";return;}
			cout<<"[Admin] Deleted: "<<cities[found].name<<"\n";
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