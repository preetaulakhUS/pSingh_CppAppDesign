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
			cout<<label<<": "<<city<<", "<<county<<" County\n";
			cout<<"\tLatitude: "<<latitude<<"\n";
			cout<<"\tLongitude: "<<longitude<<"\n";
			cout<<"\tPopulation: "<<population<<"\n";
			cout<<"\tDensity: "<<density<<" people/km^2"<<endl;
		}

		//? vector arithmetic
		Vector3D displacementTo(Location target){return target.getPosition().subtract(position);}
		double distanceTo(Location target){return calculateDistance(position,target.getPosition());}
};