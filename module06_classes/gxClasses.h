#include <iostream>
#include "../module04_database/gxDatabase.h"
using namespace std;

class Location{
	private:
		string city, county;
		double latitude, longitude;
		int population;
		double density;

	public:
		//? empty constructor
		Location(){
			city="";county="";
			latitude=0.0;longitude=0.0;
			population=0;density=0.0;
		}

		//? parameterised
		Location(string city,string county,double latitude,double longitude,int population,double density){
			this->city=city;this->county=county;
			this->latitude=latitude;this->longitude=longitude;
			this->population=population;this->density=density;
		}

		//? setters
		void setCity(string city){this->city=city;}
		void setCounty(string county){this->county=county;}
		void setCoordinates(double latitude,double longitude){this->latitude=latitude;this->longitude=longitude;}
		void setPopulation(int population){this->population=population;}
		void setDensity(double density){this->density=density;}

		//? getters
		string getCity(){return city;}
		string getCounty(){return county;}
		double getLatitude(){return latitude;}
		double getLongitude(){return longitude;}
		int getPopulation(){return population;}
		double getDensity(){return density;}

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

		// todo implementation of vector space operations. (lat, lon) will be the position of the object.
};
