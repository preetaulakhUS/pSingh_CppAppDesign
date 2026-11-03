#include <iostream>
#include "../module02_menu/gxMap.h"
using namespace std;

//? manual and documentation
void showHelp(){
	system("cls");
	cout<<cB<<string(66,'=')<<cR<<"\n";
	cout<<cH<<"                               HELP"<<cR<<"\n";
	cout<<cB<<string(66,'=')<<cR<<"\n\n";

	cout<<cT<<"[1. APPLICATION PURPOSE]"<<cR<<"\n";
	cout<<cWh<<"Azimuth GX is an offline geographic information explorer for the\n"
	    <<"San Francisco Bay Area. It is built entirely in C++ without external\n"
	    <<"GIS libraries, web APIs, or background telemetry. Everything you see\n"
	    <<"(the map canvas, coordinate projections, distance calculations,\n"
	    <<"and demographic summaries) runs strictly on local data parsed from 127\n"
	    <<"municipalities across 5 counties (Alameda, Contra Costa, SF,\n"
	    <<"San Mateo, Santa Clara).\n\n"<<cR;

	cout<<cT<<"[2. MAP NAVIGATION]"<<cR<<"\n";
	cout<<cWh<<"The map is a 26x75 terminal grid projected from geographic\n"
	    <<"coordinates (37.00N to 38.05N, 122.50W to 121.58W). It uses linear\n"
	    <<"character projection to fit your console.\n"
	    <<"  * "<<cC<<"o"<<cWh<<"       : City location point\n"
	    <<"  * "<<cW<<"~"<<cWh<<"       : San Francisco Bay water body\n"
	    <<"  * "<<cT<<"[Name]"<<cWh<<"  : Revealed city label\n"
	    <<"To reveal cities on the map, enter their names separated by commas\n"
	    <<"(such as 'Oakland, Berkeley, San Jose'). Type "<<cT<<"'r'"<<cWh<<" to reset labels,\n"
	    <<"or "<<cT<<"'0'"<<cWh<<" to return to the main menu.\n\n"<<cR;

	cout<<cT<<"[3. DENSITY TIERS]"<<cR<<"\n";
	cout<<cWh<<"City density is calculated as residents per square kilometre\n"
	    <<"and categorised into 6 demographic tiers:\n"
	    <<"  * "<<cD<<"Tier 1: Sparsely Inhabited   "<<cWh<<"(<120 /km^2)\n"
	    <<"  * "<<cC<<"Tier 2: Lightly Populated    "<<cWh<<"(<500 /km^2)\n"
	    <<"  * "<<cW<<"Tier 3: Moderately Crowded   "<<cWh<<"(<1500 /km^2)\n"
	    <<"  * "<<cT<<"Tier 4: Densely Packed       "<<cWh<<"(<2500 /km^2)\n"
	    <<"  * "<<cM<<"Tier 5: Highly Dense          "<<cWh<<"(<3500 /km^2)\n"
	    <<"  * "<<cA<<"Tier 6: Extremely Congested  "<<cWh<<"(>=3500 /km^2)\n\n"<<cR;

	cout<<cT<<"[4. DISTANCE AND BAY BYPASS]"<<cR<<"\n";
	cout<<cWh<<"Direct distances use 3D Cartesian coordinates on a spherical Earth\n"
	    <<"model (radius R = 6371 km) with central angles from vector dot products:\n"
	    <<"    "<<cA<<"theta = arccos((A . B) / (|A| * |B|))"<<cWh<<",   "<<cM<<"distance = R * theta"<<cWh<<"\n"
	    <<"However, straight lines across the Bay cut across water. Since people\n"
	    <<"cannot walk on water and this program doesn't assume you own a hydrofoil or\n"
	    <<"are jesus's descendent, the system tests travel vectors against the geometric\n"
	    <<"spine of the Bay. When an intersection is detected, it compares the South route\n"
	    <<"(via San Jose) against the North route (via SF and Richmond) and routes you through\n"
	    <<"whichever land path is shorter at a steady 4.5 km/h walk speed.\n\n"<<cR;

	cout<<cT<<"[5. SECURITY ROLES]"<<cR<<"\n";
	cout<<cWh<<"  * "<<cC<<"Guest: "<<cWh<<"Unrestricted access to city analysis, pairwise comparison,\n"
	    <<"          county directories, and the interactive map.\n"
	    <<"  * "<<cA<<"Admin: "<<cWh<<"More access including full dataset regional diagnostics,\n"
	    <<"          population sums, and extreme value audits.\n"
	    <<"Security policy: 3 consecutive wrong passwords locks the Admin\n"
	    <<"credential for the session. When locked, you can either continue as\n"
	    <<"Guest or exit. Don't brute force it.\n\n"<<cR;

	cout<<cB<<string(66,'=')<<cR<<"\n";
	system("pause");
}