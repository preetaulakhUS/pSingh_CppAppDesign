#include <iostream>
#include "gxClasses.h"

using namespace std;
int main()
{
	loadDB();
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

	//? vector space distance (Math 3C / 3E)
	tripDistance=currentLocation.distanceTo(destinationLocation);
	Vector3D disp=currentLocation.displacementTo(destinationLocation);
	cout<<"\n=== VECTOR ANALYSIS ===\n";
	cout<<"Displacement Vector <dx, dy, dz>: <"<<disp.x<<", "<<disp.y<<", "<<disp.z<<">\n";
	cout<<"Chord Distance: "<<disp.norm()<<" km\n";
	cout<<"Surface Arc Distance: "<<tripDistance<<" km\n";

	system("pause");
}