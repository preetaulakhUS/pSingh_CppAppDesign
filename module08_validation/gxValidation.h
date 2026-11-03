#include <iostream>
#include "../module07_security/gxSecurity.h"
using namespace std;

string getString(string prompt){
	string val;
	do {
		cout<<prompt;
		getline(cin,val);
		if (val.empty()) cout<<cA<<"Field cannot be empty. Try again.\n"<<cR;
	} while(val.empty());
	return val;
}

int getInt(string prompt,int min,int max){
	int val;
	while (true){
		cout<<prompt;
		if (cin>>val&&val>=min&&val<=max){cin.ignore(10000,'\n');return val;}
		cout<<cA<<"Enter a number between "<<min<<" and "<<max<<". Try again.\n"<<cR;
		cin.clear();cin.ignore(10000,'\n');
	}
}

double getDouble(string prompt,double min,double max){
	double val;
	while (true){
		cout<<prompt;
		if (cin>>val&&val>=min&&val<=max){cin.ignore(10000,'\n');return val;}
		cout<<cA<<"Enter a value between "<<min<<" and "<<max<<". Try again.\n"<<cR;
		cin.clear();cin.ignore(10000,'\n');
	}
}

char getChar(string prompt,string valid){
	char val;
	while (true){
		cout<<prompt;
		cin>>val;cin.ignore(10000,'\n');
		for (int i=0;i<(int)valid.length();i++) if (val==valid[i]) return val;
		cout<<cA<<"Enter one of: "<<valid<<". Try again.\n"<<cR;
	}
}