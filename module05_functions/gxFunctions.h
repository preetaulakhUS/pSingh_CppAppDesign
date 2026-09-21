#include <iostream>
#include "../module04_database/gxDatabase.h"
using namespace std;

void printCities(City *cities,int *j){
    for (int i=0;i<*j;i++){
        cout<<"["<<(cities+i)->name<<","
        <<(cities+i)->latitude<<","
        <<(cities+i)->longitude<<","
        <<(cities+i)->population<<","
        <<(cities+i)->density<<"]"<<endl;
    }
}

void capitalise(string *text){
    for (int i=0;i<text->length();i++){
        if (i==0||(*text)[i-1]==' ')
            (*text)[i]=toupper((*text)[i]);
    }
}

void analyseCities(string *location){
    stringstream ss(*location);
    string city;
    string county;
    City *cities;
    int *count;

    getline(ss,city,',');getline(ss,county);
    if (county[0]==' ') county.erase(0,1);
    capitalise(&city);capitalise(&county);

    if (county=="Alameda"){cities=alamedaCities;count=&iAL;}
    else if (county=="Contra Costa"){cities=contraCostaCities;count=&iCC;}
    else if (county=="San Francisco"){cities=sanFranciscoCities;count=&iSF;}
    else if (county=="San Mateo"){cities=sanMateoCities;count=&iSM;}
    else if (county=="Santa Clara"){cities=santaClaraCities;count=&iSC;}

    
    for (int i=0;i<*count;i++){
        if ((cities+i)->name==city){
            int population=(cities+i)->population;
            double density=(cities+i)->density;
            double area=population/density;
            string classification;
            
            if (density<120) classification="Sparsely inhabited";
            else if (density<500) classification="Lightly populated";
            else if (density<1500) classification="Moderately crowded";
            else if (density<2500) classification="Densely packed";
            else if (density<3500) classification="Highly dense";
            else classification="Extremely congested";

            cout<<city<<endl<<"Population: "<<population<<endl<<
            "Density: "<<density<<" people/km^2"<<endl<<
            "Estimated area: "<<area<<" km^2"<<endl<<
            "Classification: "<<classification<<endl;
        }
    }
}