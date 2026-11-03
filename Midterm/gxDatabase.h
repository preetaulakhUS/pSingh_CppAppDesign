#include <iostream>
#include <fstream>
#include <sstream>
#include "gxVariables.h"
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

//? list all cities per county
void listCounty(){
    cout<<cH<<"Select County to View:\n"<<cR;
    cout<<cT<<"  1) "<<cWh<<"Alameda\n"
        <<cT<<"  2) "<<cWh<<"Contra Costa\n"
        <<cT<<"  3) "<<cWh<<"San Francisco\n"
        <<cT<<"  4) "<<cWh<<"San Mateo\n"
        <<cT<<"  5) "<<cWh<<"Santa Clara\n"<<cR;
    int choice=0;
    while (true){
        cout<<cB<<"==> "<<cR;
        if (cin>>choice&&choice>=1&&choice<=5){
            cin.ignore(10000,'\n');
            break;
        }
        cout<<cA<<"Invalid input. Please enter a number between 1 and 5.\n"<<cR;
        cin.clear();
        cin.ignore(10000,'\n');
    }
    City *cities;int count;string countyName;
    if (choice==1){cities=alamedaCities;count=iAL;countyName="Alameda";}
    else if (choice==2){cities=contraCostaCities;count=iCC;countyName="Contra Costa";}
    else if (choice==3){cities=sanFranciscoCities;count=iSF;countyName="San Francisco";}
    else if (choice==4){cities=sanMateoCities;count=iSM;countyName="San Mateo";}
    else{cities=santaClaraCities;count=iSC;countyName="Santa Clara";}

    cout<<"\n"<<cB<<string(52,'=')<<cR<<"\n";
    cout<<cH<<"  "<<countyName<<" County "<<cD<<"("<<count<<" cities tracked)"<<cR<<"\n";
    cout<<cB<<string(52,'=')<<cR<<"\n";
    for (int i=0;i<count;i++){
        cout<<cT<<"  "<<(i+1<10?" ":"")<<(i+1)<<") "<<cWh<<cities[i].name;
        int dots=30-(int)cities[i].name.length();
        if (dots<2) dots=2;
        cout<<cD<<string(dots,'.')<<" "<<cC<<cities[i].population<<" residents"<<cR<<"\n";
    }
    cout<<cB<<string(52,'=')<<cR<<"\n\n";
    system("pause");
}

//? admin only ... regional summary across counties
void adminRegionalSummary(){
    cout<<cB<<string(58,'=')<<cR<<"\n";
    cout<<cH<<"                 REGIONAL SUMMARY"<<cR<<"\n";
    cout<<cB<<string(58,'=')<<cR<<"\n\n";

    int totalPop=0;
    string maxPopCity="", maxDenseCity="", minDenseCity="";
    int maxPop=-1;
    double maxDense=-1.0, minDense=999999.0;

    City *counties[5]={alamedaCities,contraCostaCities,sanFranciscoCities,sanMateoCities,santaClaraCities};
    int counts[5]={iAL,iCC,iSF,iSM,iSC};
    string countyNames[5]={"Alameda","Contra Costa","San Francisco","San Mateo","Santa Clara"};

    for (int c=0;c<5;c++){
        for (int i=0;i<counts[c];i++){
            totalPop+=counties[c][i].population;
            if (counties[c][i].population>maxPop){
                maxPop=counties[c][i].population;
                maxPopCity=counties[c][i].name+" ("+countyNames[c]+" County)";
            }
            if (counties[c][i].density>maxDense){
                maxDense=counties[c][i].density;
                maxDenseCity=counties[c][i].name+" ("+countyNames[c]+" County)";
            }
            if (counties[c][i].density<minDense){
                minDense=counties[c][i].density;
                minDenseCity=counties[c][i].name+" ("+countyNames[c]+" County)";
            }
        }
    }

    cout<<cD<<"  * Total Cities Tracked : "<<cWh<<loadedCityCount<<cR<<"\n";
    cout<<cD<<"  * Total Regional Population    : "<<cC<<totalPop<<" residents"<<cR<<"\n";
    cout<<cD<<"  * Average City Population         : "<<cWh<<(totalPop/loadedCityCount)<<" residents"<<cR<<"\n\n";

    cout<<cT<<string(58,'-')<<cR<<"\n\n";
    for (int c=0;c<5;c++){
        cout<<cD<<"  * "<<cWh<<countyNames[c];
        int dots=20-(int)countyNames[c].length();
        if (dots<2) dots=2;
        cout<<cD<<string(dots,'.')<<" "<<cT<<counts[c]<<" cities"<<cR<<"\n";
    }

    cout<<cT<<string(58,'-')<<cR<<"\n\n";
    cout<<cD<<"  * Most Populous  : "<<cWh<<maxPopCity<<" "<<cC<<"("<<maxPop<<" residents)"<<cR<<"\n";
    cout<<cD<<"  * Highest Density: "<<cWh<<maxDenseCity<<" "<<cM<<"("<<maxDense<<" people/km^2)"<<cR<<"\n";
    cout<<cD<<"  * Lowest Density : "<<cWh<<minDenseCity<<" "<<cD<<"("<<minDense<<" people/km^2)"<<cR<<"\n\n";

    cout<<cB<<string(58,'=')<<cR<<"\n";
    system("pause");
}