#include <iostream>
#include <sstream>
#include "../module06_classes/gxClasses.h"
using namespace std;

//? variables and abbreviations
int mapHeight=26;	int mH=mapHeight;
int mapWidth=75;	int mW=mapWidth;

double minimumLatitude=37.0046;		double minLat=minimumLatitude;
double maximumLatitude=38.0519;		double maxLat=maximumLatitude;
double minimumLongitude=-122.5036;	double minLng=minimumLongitude;
double maximumLongitude=-121.5854;	double maxLng=maximumLongitude;

//? ANSI colours
string colorReset="\033[0m";	string cR=colorReset;	// default
string colorWater="\033[94m";	string cW=colorWater;	// blue
string colorCity="\033[92m";	string cC=colorCity;	// green
string colorTag="\033[1;93m";	string cT=colorTag;		// yellow
string colorBorder="\033[36m";	string cB=colorBorder;	// cyan

void projectCoordinates(double lat,double lng,int *r,int *c){
	*r=(int)((maxLat-lat)/(maxLat-minLat)*(mH-1));
	*c=(int)((lng-minLng)/(maxLng-minLng)*(mW-1));
	if (*r<0) *r=0; if (*r>=mH) *r=mH-1;
	if (*c<0) *c=0; if (*c>=mW) *c=mW-1;
}

void renderMap(string revealedList[],int revealedCount){
	char grid[mH][mW];
	int labelMask[mH][mW]={};
	for (int r=0;r<mH;r++){
		for (int c=0;c<mW;c++){
			grid[r][c]=' ';
		}
	}
	City *counties[5]={alamedaCities,contraCostaCities,sanFranciscoCities,sanMateoCities,santaClaraCities};
	int counts[5]={iAL,iCC,iSF,iSM,iSC};
	string countyNames[5]={"Alameda","Contra Costa","San Francisco","San Mateo","Santa Clara"};

	//? 127 cities plotter
	for (int i=0;i<5;i++){
		for (int j=0;j<counts[i];j++){
			int r,c;
			projectCoordinates(counties[i][j].latitude,counties[i][j].longitude,&r,&c);
			grid[r][c]='o';
		}
	}

	//? water generator
	for (int r=4;r<18;r++){
		int penMax=-1, eastMin=999;
		for (int i=0;i<5;i++){
			for (int j=0;j<counts[i];j++){
				int cr,cc;
				projectCoordinates(counties[i][j].latitude,counties[i][j].longitude,&cr,&cc);
				if (abs(cr-r)<=1){
					bool isWestSide=(countyNames[i]=="San Francisco"||countyNames[i]=="San Mateo"||(countyNames[i]=="Santa Clara"&&counties[i][j].longitude<=-122.01));
					bool isEastSide=(countyNames[i]=="Alameda"||countyNames[i]=="Contra Costa"||(countyNames[i]=="Santa Clara"&&counties[i][j].longitude>=-121.93));
					if (isWestSide&&cc>penMax) penMax=cc;
					if (isEastSide&&cc<eastMin) eastMin=cc;
				}
			}
		}
		if (penMax!=-1&&eastMin!=999&&penMax<eastMin){
			for (int c=penMax+1;c<eastMin;c++){
				if (grid[r][c]==' ') grid[r][c]='~';
			}
		}
	}

	//? city marker
	for (int i=0;i<revealedCount;i++){
		if (revealedList[i].empty()) continue;
		Location targetLocation;
		if (targetLocation.load(revealedList[i])){
			int targetRow,targetCol;
			projectCoordinates(targetLocation.getLatitude(),targetLocation.getLongitude(),&targetRow,&targetCol);
			string cityTag="["+targetLocation.getCity()+"]";
			int startCol=targetCol;
			if (startCol+(int)cityTag.length()>=mW) startCol=mW-(int)cityTag.length()-1;
			for (int charIndex=0;charIndex<(int)cityTag.length();charIndex++){
				grid[targetRow][startCol+charIndex]=cityTag[charIndex];
				labelMask[targetRow][startCol+charIndex]=1;
			}
		}
	}

	//? display map
	cout<<cB<<string(mW+4,'=')<<cR<<"\n";
	cout<<cB<<"|\t\t"<<cR<<"AZIMUTH GX - BAY AREA GEOGRAPHIC MAP ("<<loadedCityCount<<" CITIES)"<<cB<<"\t\t|\n"<<cR;
	cout<<cB<<string(mW+4,'=')<<cR<<"\n";

	for (int r=0;r<mH;r++){
		cout<<cB<<"| "<<cR;
		for (int c=0;c<mW;c++){
			if (labelMask[r][c]==1) cout<<cT<<grid[r][c]<<cR;
			else if (grid[r][c]=='~') cout<<cW<<grid[r][c]<<cR;
			else if (grid[r][c]=='o') cout<<cC<<grid[r][c]<<cR;
			else cout<<grid[r][c];
		}
		cout<<cB<<" |\n"<<cR;
	}
	cout<<cB<<string(mW+4,'=')<<cR<<"\n";
	cout<<"Legend: "<<cC<<"o"<<cR<<" City  "<<cW<<"~"<<cR<<" SF Bay  "<<cT<<"[City]"<<cR<<" Revealed\n";
}

void viewMap(){
	if (cin.peek()=='\n') cin.ignore();
	string revealedCities[30];
	int revealedCount=0;

	do {
		system("cls");
		renderMap(revealedCities,revealedCount);

		if (revealedCount>0){
			cout<<"\n--- REVEALED LOCATIONS ("<<revealedCount<<") ---\n";
			for (int i=0;i<revealedCount;i++){
				Location loc;
				if (loc.load(revealedCities[i])){
					cout<<(i+1)<<") "<<loc.getCity()<<", "<<loc.getCounty()<<" County | Pop: "<<loc.getPopulation()<<" | Density: "<<loc.getDensity()<<" people/km^2\n";
				}
			}
		}

		cout<<"\nEnter city name to reveal (or comma separated list, 'r' to reset, '0' to exit):\n==> ";
		string userInput;
		if (!getline(cin,userInput)||userInput=="0") break;

		if (tolower(userInput[0])=='r'){
			revealedCount=0;
			continue;
		}

		stringstream ss(userInput);
		string singleCity;
		while (getline(ss,singleCity,',')){
			while (!singleCity.empty()&&singleCity[0]==' ') singleCity.erase(0,1);
			while (!singleCity.empty()&&singleCity.back()==' ') singleCity.pop_back();
			if (singleCity.empty()) continue;
			capitalise(&singleCity);

			Location checkLocation;
			if (checkLocation.load(singleCity)){
				bool alreadyRevealed=false;
				for (int i=0;i<revealedCount;i++){
					if (revealedCities[i]==singleCity) alreadyRevealed=true;
				}
				if (!alreadyRevealed&&revealedCount<30){
					revealedCities[revealedCount]=singleCity;
					revealedCount++;
				}
			} else {
				cout<<"City \""<<singleCity<<"\" not found in records.\n";
			}
		}
	} while (true);
}