#include <iostream>
#include "../module05_functions/gxFunctions.h"
using namespace std;

class Location{
	private:
		string city, county;
		double latitude, longitude;
		int population;
		double density;
		Vector3D position;

		void updatePosition(){
			position=toCartesian(latitude,longitude);
		}

	public:
		//? empty constructor
		Location(){
			city="";county="";
			latitude=0.0;longitude=0.0;
			population=0;density=0.0;
			position=Vector3D();
		}

		//? parameterised
		Location(string city,string county,double latitude,double longitude,int population,double density){
			this->city=city;this->county=county;
			this->latitude=latitude;this->longitude=longitude;
			this->population=population;this->density=density;
			updatePosition();
		}

		//? setters
		void setCity(string city){this->city=city;}
		void setCounty(string county){this->county=county;}
		void setCoordinates(double latitude,double longitude){this->latitude=latitude;this->longitude=longitude;updatePosition();}
		void setPopulation(int population){this->population=population;}
		void setDensity(double density){this->density=density;}

		//? getters
		string getCity(){return city;}
		string getCounty(){return county;}
		double getLatitude(){return latitude;}
		double getLongitude(){return longitude;}
		int getPopulation(){return population;}
		double getDensity(){return density;}
		Vector3D getPosition(){return position;}

		//? loader
		bool load(string cityName){
			City *cities[5]={alamedaCities,contraCostaCities,sanFranciscoCities,sanMateoCities,santaClaraCities};
			int counts[5]={iAL,iCC,iSF,iSM,iSC};
			string counties[5]={"Alameda","Contra Costa","San Francisco","San Mateo","Santa Clara"};

			for (int c=0;c<5;c++){
				for (int i=0;i<counts[c];i++){
					if (cities[c][i].name==cityName){
						city=cities[c][i].name;
						county=counties[c];
						latitude=cities[c][i].latitude;
						longitude=cities[c][i].longitude;
						population=cities[c][i].population;
						density=cities[c][i].density;
						updatePosition();
						return true;
					}
				}
			}
			return false;
		}

		//? printer
		void print(string label){
			cout<<cH<<"  ["<<label<<"] "<<cWh<<city<<cD<<", "<<county<<" County\n";
			cout<<cD<<"    * Coordinates : "<<cWh<<latitude<<" N, "<<longitude<<" W\n";
			cout<<cD<<"    * Population  : "<<cC<<population<<" residents\n";
			cout<<cD<<"    * Density     : "<<cWh<<density<<" people/km^2"<<cR<<"\n";
		}

		//? vector arithmetic
		Vector3D displacementTo(Location target){return target.getPosition().subtract(position);}
		double distanceTo(Location target){return calculateDistance(position,target.getPosition());}
};

//? compare two cities by distance
void compareCities(){
    cout<<cH<<"Enter first city name: "<<cR;
    string name1;getline(cin,name1);
    capitalise(&name1);
    cout<<cH<<"Enter second city name: "<<cR;
    string name2;getline(cin,name2);
    capitalise(&name2);
    Location loc1,loc2;
    if (!loc1.load(name1)){cout<<cA<<"City \""<<name1<<"\" not found in records.\n"<<cR;system("pause");return;}
    if (!loc2.load(name2)){cout<<cA<<"City \""<<name2<<"\" not found in records.\n"<<cR;system("pause");return;}
    
    cout<<"\n"<<cB<<string(50,'=')<<cR<<"\n";
    cout<<cH<<"                  TRIP ANALYSIS"<<cR<<"\n";
    cout<<cB<<string(50,'=')<<cR<<"\n\n";

    loc1.print("Origin");
    cout<<"\n";
    loc2.print("Destination");
    cout<<"\n";

    // check if straight line crosses the SF Bay line
    bool crossBay=crossesBayWater(loc1.getLatitude(),loc1.getLongitude(),loc2.getLatitude(),loc2.getLongitude());

    double directDist=loc1.distanceTo(loc2);
    cout<<cD<<"Direct Distance : "<<cWh<<directDist<<" km"<<cR<<"\n\n";

    if (crossBay){
        // condition to check which path is quicker
        Location sj, rich, sf;
        sj.load("San Jose");
        rich.load("Richmond");
        sf.load("San Francisco");

        double southDist=loc1.distanceTo(sj)+sj.distanceTo(loc2);
        double northDist;
        if (loc1.getLongitude()>loc2.getLongitude())
            northDist=loc1.distanceTo(rich)+rich.distanceTo(sf)+sf.distanceTo(loc2);
        else
            northDist=loc1.distanceTo(sf)+sf.distanceTo(rich)+rich.distanceTo(loc2);

        double walkDist;
        string viaDesc;
        if (northDist<southDist){
            walkDist=northDist;
            viaDesc="North Bypass (San Francisco and Richmond)";
        } else {
            walkDist=southDist;
            viaDesc="South Bypass (San Jose)";
        }

        int walkHrs=(int)(walkDist/walkSpeed);
        int walkMins=(int)((walkDist/walkSpeed-walkHrs)*60);

        cout<<cD<<"Route           : "<<cW<<"Water Crossing (SF Bay)"<<cR<<"\n";
        cout<<cD<<"Optimal Bypass  : "<<cWh<<viaDesc<<cR<<"\n";
        cout<<cD<<"Walking Distance: "<<cWh<<walkDist<<" km"<<cR<<"\n";
        cout<<cD<<"Estimated Time  : "<<cC<<walkHrs<<" h "<<walkMins<<" min "<<cD<<"("<<walkSpeed<<" km/h)"<<cR<<"\n";
        cout<<cD<<"Detour Added    : "<<cT<<"+"<<(walkDist-directDist)<<" km "<<cD<<"(land bypass around water)"<<cR<<"\n\n";
    } else {
        int hrs=(int)(directDist/walkSpeed);
        int mins=(int)((directDist/walkSpeed-hrs)*60);
        cout<<cD<<"Route           : "<<cC<<"No Water Crossing"<<cR<<"\n";
        cout<<cD<<"Walking Distance: "<<cWh<<directDist<<" km"<<cR<<"\n";
        cout<<cD<<"Estimated Time  : "<<cC<<hrs<<" h "<<mins<<" min "<<cD<<"("<<walkSpeed<<" km/h)"<<cR<<"\n\n";
    }
    cout<<cB<<string(50,'=')<<cR<<"\n";
    system("pause");
}