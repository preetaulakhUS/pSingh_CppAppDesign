#include <iostream>
#include "../module03_variables/gxVariables.h"
using namespace std;

short i=1;
void mainMenu(){
	do{
		system("cls");
		cout<<string(38,'-')<<"\n\t\tMenu\n"<<string(38,'-')<<"\n";
		cout<<"1) Initiate Analysis\n2) View Map\n3) Help\n4) Settings\n5) Exit\n0) Beta Testing";
		int input;cout<<"\n==> ";
		cin>>input;
		system("cls");
		switch (input){
			case 1:
			cout<<"You're attempting to initiate analysis. This feature is currently under development."<<endl;
			system("pause");break;

			case 2:
			cout<<"You're attempting to view map. This feature is currently under development."<<endl;
			system("pause");break;

			case 3:
			cout<<"This section is meant to understand the features and utilisation of this application. It is currently under development."<<endl;
			system("pause");break;
			
			case 4:
			cout<<"This feature is meant to tweak settings. This feature is currently under development."<<endl;
			system("pause");break;
			
			case 5:
			cout<<"Goodbye!"<<endl;system("pause");i=0;break;

			//? beta testing module 03
			case 0:{
			Location loc;loc.printIL();loc.printDL();
			}

			
			default:break;
		}
		// if(input==1){}
		// else if(input==2){}
		// else if(input==3){}
		// else if(input==4){}
		// else if(input==5){
		// 	system("cls");
		// 	cout<<"\nGoodbye!";
		// 	cin>>input;
		// 	return 0;}
	} while(i);
}