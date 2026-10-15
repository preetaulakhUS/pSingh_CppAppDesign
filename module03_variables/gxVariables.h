#include <iostream>
using namespace std;

string appName="Azimuth GX";
string appTagline="Geographic Explorer";
double appVersion=4.1;

//? fetch user's name
string userName;

//? database status
bool databaseLoaded=false;
int loadedCityCount=0;

//? trip status
double tripDistance=0.0;
char unit='k';        // km: kilometres, mi: miles
float walkSpeed=4.8f; // km/h


//? display all variables
void printVariables(){
	system("cls");
	cout<<"=== SESSION VARIABLES ===\n";
	cout<<"appName (string): "<<appName<<endl;
	cout<<"appTagline (string): "<<appTagline<<endl;
	cout<<"appVersion (double): "<<appVersion<<endl;
	cout<<"userName (string): "<<userName<<endl;
	cout<<"databaseLoaded (bool): "<<(databaseLoaded?"true":"false")<<endl;
	cout<<"loadedCityCount (int): "<<loadedCityCount<<endl;
	cout<<"tripDistance (double): "<<tripDistance<<endl;
	cout<<"unit (char): "<<unit<<endl;
	cout<<"walkSpeed (float): "<<walkSpeed<<endl;
	system("pause");system("cls");
}