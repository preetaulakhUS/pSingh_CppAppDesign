#include <iostream>
#include <cmath>
#include "../module04_database/gxDatabase.h"
using namespace std;

//? constants
double earthRadius=6371.0; // km
double pi=3.141592653589793;

//? 3D vector space
struct Vector3D{
	double x,y,z;

	Vector3D(double x=0.0,double y=0.0,double z=0.0){this->x=x;this->y=y;this->z=z;}

	double norm(){return sqrt(x*x+y*y+z*z);}
	double dot(Vector3D v){return x*v.x+y*v.y+z*v.z;}
	Vector3D subtract(Vector3D v){return Vector3D(x-v.x,y-v.y,z-v.z);}
};

Vector3D toCartesian(double latitude,double longitude){
	double eR=earthRadius;
	double latitudeRadian=latitude*(pi/180.0);              // convert to radians
	double longitudeRadian=longitude*(pi/180.0);            // convert to radians
	double x=eR*cos(latitudeRadian)*cos(longitudeRadian);   // x=Rcos(phi)cos(theta)
	double y=eR*cos(latitudeRadian)*sin(longitudeRadian);   // y=Rcos(phi)sin(theta)
	double z=eR*sin(latitudeRadian);                        // z=Rsin(phi)
	return Vector3D(x,y,z);
}

double calculateDistance(Vector3D pos1,Vector3D pos2){
	double eR=earthRadius;
	double dotProduct=pos1.dot(pos2);
	double cosAlpha=dotProduct/(eR*eR);
	if (cosAlpha>1.0) cosAlpha=1.0;
	if (cosAlpha<-1.0) cosAlpha=-1.0;
	double alpha=acos(cosAlpha);                            // theta=arccos((A.B)/(|A||B|)), where A and B are vectors.
	return eR*alpha;                                        // distance=R*theta
}

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