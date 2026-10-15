#include <iostream>
#include "gxMap.h"
using namespace std;

bool running=true;
void mainMenu(){
	do{
		system("cls");
		cout<<string(38,'-')<<"\n\t\tMenu\n"<<string(38,'-')<<"\n";
		cout<<"1) Initiate Analysis\n2) View Map\n3) Help\n4) Settings\n5) Exit";
		int input;cout<<"\n==> ";
		cin>>input;
		system("cls");
		switch (input){
			case 1:
			cout<<"You're attempting to initiate analysis. This feature is currently under development."<<endl;
			system("pause");break;

			case 2:
			viewMap();break;

			case 3:
			cout<<"This section is meant to understand the features and utilisation of this application. It is currently under development."<<endl;
			system("pause");break;
			
			case 4:
			cout<<"This feature is meant to tweak settings. This feature is currently under development."<<endl;
			system("pause");break;
			
			case 5:
			cout<<"Goodbye!"<<endl;system("pause");running=false;break;

			default:break;
		}
	} while(running);
}