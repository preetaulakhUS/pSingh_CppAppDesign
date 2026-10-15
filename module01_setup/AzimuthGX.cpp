#include <iostream>
#include "../module02_menu/gxMenu.h"
using namespace std;
int main()
{
	loadDB();
	cout<<"Welcome to Azimuth GX: Geographic Explorer! This application in its developmental phase.\n";
	system("pause");system("cls");
	mainMenu();
}