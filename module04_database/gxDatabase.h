#include <iostream>
#include <fstream>
using namespace std;

struct City{
    string name;
    double latitude;
    double longitude;
    int population;
    double density;
    string zips;
};

City alademaCities[20]={};
City contraCostaCities[50]={};
City sanFranciscoCities[1]={};
City sanMateoCities[33]={};
City santaClaraCities[23]={};

void loadDB(){
    ifstream file("../module04_database/bayAreaCities.csv");

    if (!file){cout<<"Could not open file."<<endl;return;}

    string line;
    while (getline(file,line)){
        cout<<line<<endl;
    }
}