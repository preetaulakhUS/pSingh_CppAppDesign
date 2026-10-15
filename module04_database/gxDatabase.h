#include <iostream>
#include <fstream>
#include <sstream>
#include "../module03_variables/gxVariables.h"
using namespace std;

struct City{
    string name;
    double latitude;
    double longitude;
    int population;
    double density;
    string zips;
};

City alamedaCities[20]={};
City contraCostaCities[50]={};
City sanFranciscoCities[1]={};
City sanMateoCities[33]={};
City santaClaraCities[23]={};

int iAL=0, iCC=0, iSF=0, iSM=0, iSC=0; //indices per county

void loadDB(){
    ifstream file("../module04_database/bayAreaCities.csv");
    if (!file){
        file.clear();
        file.open("module04_database/bayAreaCities.csv");
    }
    if (!file){
        file.clear();
        file.open("bayAreaCities.csv");
    }

    if (!file){cout<<"Could not open file."<<endl;return;}

    string line;getline(file,line); // to skip the header line
    
    while (getline(file,line)){
        stringstream ss(line);
        string county;
        City city;
        string latitude;
        string longitude;
        string population;
        string density;

        getline(ss,county,',');
        getline(ss,city.name,',');
        getline(ss,latitude,',');city.latitude=stod(latitude);
        getline(ss,longitude,',');city.longitude=stod(longitude);
        getline(ss,population,',');city.population=stoi(population);
        getline(ss,density,',');city.density=stod(density);
        getline(ss,city.zips,',');

        if (county=="Alameda"){alamedaCities[iAL]=city;iAL++;}
        else if (county=="Contra Costa"){contraCostaCities[iCC]=city;iCC++;}
        else if (county=="San Francisco"){sanFranciscoCities[iSF]=city;iSF++;}
        else if (county=="San Mateo"){sanMateoCities[iSM]=city;iSM++;}
        else if (county=="Santa Clara"){santaClaraCities[iSC]=city;iSC++;}
    }

    databaseLoaded=true;
    loadedCityCount=iAL+iCC+iSF+iSM+iSC;
}