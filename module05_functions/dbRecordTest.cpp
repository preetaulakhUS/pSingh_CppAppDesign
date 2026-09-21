#include <iostream>
#include "gxFunctions.h"

using namespace std;
int main()
{
	loadDB();

    cout<<"\nALAMEDA COUNTY:"<<endl;
    printCities(alamedaCities,&iAL);
    cout<<"\nCONTRA COSTA COUNTY:"<<endl;
    printCities(contraCostaCities,&iCC);
    cout<<"\nSAN FRANCISCO COUNTY:"<<endl;
    printCities(sanFranciscoCities,&iSF);
    cout<<"\nSAN MATEO COUNTY:"<<endl;
    printCities(sanMateoCities,&iSM);
    cout<<"\nSANTA CLARA COUNTY:"<<endl;
    printCities(santaClaraCities,&iSC);
    
	system("pause");system("cls");
}