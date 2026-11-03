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
	double alpha=acos(cosAlpha);                            // theta=arccos((A.B)/(|A||B|)), A and B are vectors.
	return eR*alpha;                                        // distance=R*theta
}

//? line intersection for SF Bay
bool segmentsIntersect(double x1,double y1,double x2,double y2,double x3,double y3,double x4,double y4){
	double c1=(x2-x1)*(y3-y1)-(y2-y1)*(x3-x1);
	double c2=(x2-x1)*(y4-y1)-(y2-y1)*(x4-x1);
	double c3=(x4-x3)*(y1-y3)-(y4-y3)*(x1-x3);
	double c4=(x4-x3)*(y2-y3)-(y4-y3)*(x2-x3);
	return ((c1>0&&c2<0)||(c1<0&&c2>0))&&((c3>0&&c4<0)||(c3<0&&c4>0));
}

//? check if line between two coordinates crosses the SF Bay line
bool crossesBayWater(double lat1,double lng1,double lat2,double lng2){
	// segments are the centreline of the bay from south to north
	double bayLng[4]={-121.97, -122.25, -122.42, -122.46};
	double bayLat[4]={  37.42,   37.65,   37.95,   38.05};
	for (int i=0;i<3;i++){
		if (segmentsIntersect(lng1,lat1,lng2,lat2,bayLng[i],bayLat[i],bayLng[i+1],bayLat[i+1]))
			return true;
	}
	return false;
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
            
            if (density<120) classification="Tier 1: Sparsely Inhabited";
            else if (density<500) classification="Tier 2: Lightly Populated";
            else if (density<1500) classification="Tier 3: Moderately Crowded";
            else if (density<2500) classification="Tier 4: Densely Packed";
            else if (density<3500) classification="Tier 5: Highly Dense";
            else classification="Tier 6: Extremely Congested";

            cout<<city<<endl<<"Population: "<<population<<endl<<
            "Density: "<<density<<" people/km^2"<<endl<<
            "Estimated area: "<<area<<" km^2"<<endl<<
            "Classification: "<<classification<<endl;
        }
    }
}

//? analyse a city
void analyseCity(){
    cout<<cH<<"Enter city name: "<<cR;
    string cityName;getline(cin,cityName);
    capitalise(&cityName);
    City *counties[5]={alamedaCities,contraCostaCities,sanFranciscoCities,sanMateoCities,santaClaraCities};
    int counts[5]={iAL,iCC,iSF,iSM,iSC};
    string countyNames[5]={"Alameda","Contra Costa","San Francisco","San Mateo","Santa Clara"};
    for (int c=0;c<5;c++){
        for (int i=0;i<counts[c];i++){
            if (counties[c][i].name==cityName){
                int population=counties[c][i].population;
                double density=counties[c][i].density;
                double area=population/density;
                string classification;
                string classColor=cC;

                if (density<120) {classification="Sparsely Inhabited";classColor=cD;}
                else if (density<500) {classification="Lightly Populated";classColor=cC;}
                else if (density<1500) {classification="Moderately Crowded";classColor=cW;}
                else if (density<2500) {classification="Densely Packed";classColor=cT;}
                else if (density<3500) {classification="Highly Dense";classColor=cM;}
                else {classification="Extremely Congested";classColor=cA;}

                //? additional calculations
                double radius=sqrt(area/pi); // radius assuming circular boundary
                double diameter=2.0*radius;
                double walkAcrossHours=diameter/walkSpeed;
                int walkHrs=(int)walkAcrossHours;
                int walkMins=(int)((walkAcrossHours-walkHrs)*60);
                double livingSpace=(area*1000000.0)/population; // square metres per person

                cout<<"\n"<<cB<<string(50,'=')<<cR<<"\n";
                cout<<cH<<"                  CITY ANALYSIS"<<cR<<"\n";
                cout<<cB<<string(50,'=')<<cR<<"\n\n";

                cout<<cH<<"  ["<<cityName<<"] "<<cD<<countyNames[c]<<" County\n";
                cout<<cD<<"  Coordinates     : "<<cWh<<counties[c][i].latitude<<" N, "<<counties[c][i].longitude<<" W\n\n";

                cout<<cD<<"  Population      : "<<cC<<population<<" residents\n";
                cout<<cD<<"  Density         : "<<cWh<<density<<" people/km^2\n";
                cout<<cD<<"  Classification  : "<<classColor<<classification<<cR<<"\n\n";

                cout<<cD<<"  Estimated Area  : "<<cWh<<(int)area<<" km^2\n";
                cout<<cD<<"  Living Space    : "<<cWh<<(int)livingSpace<<" m^2/person\n";
                cout<<cD<<"  Diameter        : "<<cWh<<diameter<<" km\n";
                cout<<cD<<"  Walk Time Span  : "<<cC<<walkHrs<<" h "<<walkMins<<" min "<<cD<<"("<<walkSpeed<<" km/h)"<<cR<<"\n\n";

                cout<<cB<<string(50,'=')<<cR<<"\n";
                system("pause");return;
            }
        }
    }
    cout<<cA<<"City \""<<cityName<<"\" was not found in records.\n"<<cR;
    system("pause");
}