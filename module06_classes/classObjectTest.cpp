#include <iostream>
#include "gxClasses.h"
#include "../module03_variables/gxVariables.h"

using namespace std;
int main()
{
	loadDB();
	databaseLoaded=true;
	loadedCityCount=iAL+iCC+iSF+iSM+iSC;

	welcomeScreen();
	printVariables();

	//? class example
	Location currentLocation;
	Location destinationLocation;

	if (!currentLocation.load("Oakland"))
		cout<<"Oakland could not be found in the records."<<endl;
	currentLocation.print("Your location");

	if (!destinationLocation.load("Berkeley"))
		cout<<"Berkeley could not be found in the records."<<endl;
	destinationLocation.print("Destination");

	//? parameterised constructor example
	Location savedLocation("San Jose","Santa Clara",37.3012,-121.848,1827643,2148.4);
	savedLocation.print("Saved location");

	//? getter and setter example
	Location copiedLocation;
	copiedLocation.setCity(currentLocation.getCity());
	copiedLocation.setCounty(currentLocation.getCounty());
	copiedLocation.setCoordinates(currentLocation.getLatitude(),currentLocation.getLongitude());
	copiedLocation.setPopulation(currentLocation.getPopulation());
	copiedLocation.setDensity(currentLocation.getDensity());
	copiedLocation.print("Copied location");

	// todo get distance between locations using vector space implementation.

	system("pause");
}