#include <iostream>
#include "../module02_menu/gxHelp.h"
using namespace std;

//? analysis submenu
void initiateAnalysis(){
	if (!activeUser->canView()){cout<<cA<<"Access denied. Insufficient permissions.\n"<<cR;system("pause");return;}
	int choice;
	do {
		system("cls");
		cout<<cB<<string(42,'=')<<cR<<"\n";
		cout<<cH<<"                 ANALYSIS"<<cR<<"\n";
		cout<<cB<<string(42,'=')<<cR<<"\n";
		activeUser->printProfile();
		cout<<"\n"
		    <<cT<<"  1) "<<cWh<<"Analyse City\n"
		    <<cT<<"  2) "<<cWh<<"Compare Cities\n"
		    <<cT<<"  3) "<<cWh<<"List Cities by County\n";
		if (activeUser->getRole()=="Admin")
			cout<<cT<<"  4) "<<cWh<<"Regional Summary "<<cM<<"[Admin]\n"<<cR;
		cout<<cT<<"  0) "<<cWh<<"Back\n"<<cR;
		int maxChoice=(activeUser->getRole()=="Admin")?4:3;
		choice=getInt("\n==> ",0,maxChoice);
		system("cls");
		if (choice==1) analyseCity();
		else if (choice==2) compareCities();
		else if (choice==3) listCounty();
		else if (choice==4&&activeUser->getRole()=="Admin") adminRegionalSummary();
	} while (choice!=0);
}

//? main menu
bool running=true;
void mainMenu(){
	do{
		system("cls");
		cout<<cB<<string(42,'=')<<cR<<"\n";
		cout<<cH<<"              AZIMUTH GX"<<cR<<"\n";
		cout<<cD<<"         Geographic Explorer v"<<appVersion<<cR<<"\n";
		cout<<cB<<string(42,'=')<<cR<<"\n";
		activeUser->printProfile();
		cout<<"\n"
		    <<cT<<"  1) "<<cWh<<"Initiate Analysis\n"
		    <<cT<<"  2) "<<cWh<<"View Map\n"
		    <<cT<<"  3) "<<cWh<<"Help\n"
		    <<cT<<"  4) "<<cWh<<"Exit\n"<<cR;
		int input=getInt("\n==> ",1,4);
		system("cls");
		switch (input){
			case 1:
			initiateAnalysis();break;

			case 2:
			viewMap();break;

			case 3:
			showHelp();break;

			case 4:
			cout<<cH<<"Thank you for using Azimuth GX. Goodbye!"<<cR<<endl;
			system("pause");running=false;break;

			default:break;
		}
	} while(running);
}