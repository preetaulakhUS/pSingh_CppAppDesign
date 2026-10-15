#include <iostream>
#include "gxFunctions.h"

using namespace std;
int main()
{
	loadDB();


    cout<<"Please insert the location (e.g. city_name, county_name)\n\t-> ";
    string input;
    getline(cin,input);
    analyseCities(&input);
}