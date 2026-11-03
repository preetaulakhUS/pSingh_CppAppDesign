#include <iostream>
#include "gxMenu.h"
using namespace std;
int main()
{
	loadDB();
	system("cls");
	cout<<cB<<string(52,'=')<<cR<<"\n";
	cout<<cH<<"                  AZIMUTH GX"<<cR<<"\n";
	cout<<cD<<"             Geographic Explorer v"<<appVersion<<cR<<"\n";
	cout<<cB<<string(52,'=')<<cR<<"\n\n";
	if (!loginPrompt()){
		cout<<cD<<"Exiting application.\n"<<cR;
		return 0;
	}
	system("cls");
	mainMenu();
}