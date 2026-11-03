#include <iostream>
using namespace std;

string appName="Azimuth GX";
string appTagline="Geographic Explorer";
double appVersion=5.0;

//? colours
string colorReset="\033[0m";		string cR=colorReset;		// reset
string colorBorder="\033[36m";		string cB=colorBorder;		// dim cyan
string colorHeader="\033[1;96m";	string cH=colorHeader;		// cyan
string colorWater="\033[94m";		string cW=colorWater;		// blue
string colorCity="\033[92m";		string cC=colorCity;		// green
string colorTag="\033[1;93m";		string cT=colorTag;			// yellow
string colorAlert="\033[91m";		string cA=colorAlert;		// red
string colorDim="\033[90m";			string cD=colorDim;			// grey divider
string colorWhite="\033[97m";		string cWh=colorWhite;		// white text
string colorMagenta="\033[95m";		string cM=colorMagenta;		// magenta

//? fetch user's name
string userName;

//? database status
bool databaseLoaded=false;
int loadedCityCount=0;

//? trip status
double tripDistance=0.0;
char unit='k';        // km: kilometres, mi: miles
float walkSpeed=4.5f; // km/h

//? display variables
void printVariables(){
	system("cls");
	cout<<cH<<"=== SESSION VARIABLES ==="<<cR<<"\n";
	cout<<cD<<"appName (string): "<<cWh<<appName<<endl;
	cout<<cD<<"appTagline (string): "<<cWh<<appTagline<<endl;
	cout<<cD<<"appVersion (double): "<<cWh<<appVersion<<endl;
	cout<<cD<<"userName (string): "<<cWh<<userName<<endl;
	cout<<cD<<"databaseLoaded (bool): "<<cC<<(databaseLoaded?"true":"false")<<endl;
	cout<<cD<<"loadedCityCount (int): "<<cWh<<loadedCityCount<<endl;
	cout<<cD<<"tripDistance (double): "<<cWh<<tripDistance<<endl;
	cout<<cD<<"unit (char): "<<cWh<<unit<<endl;
	cout<<cD<<"walkSpeed (float): "<<cWh<<walkSpeed<<cR<<endl;
	system("pause");system("cls");
}