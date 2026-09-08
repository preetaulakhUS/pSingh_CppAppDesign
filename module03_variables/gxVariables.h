#include <iostream>
using namespace std;

class EssentialVariables{
    protected:
        double latitude, longitude, distance;
        unsigned int streetNumber, zipCode;
        string street, city;
    //? means of transportation
    public:
        bool drive, bus, walk;
}; using EssVar=EssentialVariables;

class Location:protected EssVar{
    public:
        //? get Initial Location
        tuple<unsigned int, string, string, unsigned int> getIL(){
            cout<<"Please enter your location.\n";
            cout<<"Street Number: ";cin>>streetNumber;
            cin.ignore();
            cout<<"Street Name: ";getline(cin, street);
            cout<<"City: ";getline(cin, city);
            cout<<"Zip Code: ";cin>>zipCode;
            system("pause");system("cls");
            return {streetNumber, street, city, zipCode};
        };

        void printIL(){
            auto loc=getIL();
            cout<<"Your location is "<<get<0>(loc)<<" "<<get<1>(loc)<<", "<<get<2>(loc)<<", "<<get<3>(loc)<<"."<<endl;system("pause");system("cls");
        };

        //? get Destination Location
        tuple<unsigned int, string, string, unsigned int> getDL(){
            cout<<"Please enter the destination.\n";
            cout<<"Street Number: ";cin>>streetNumber;
            cin.ignore();
            cout<<"Street Name: ";getline(cin, street);
            cout<<"City: ";getline(cin, city);
            cout<<"Zip Code: ";cin>>zipCode;
            system("pause");system("cls");
            return {streetNumber, street, city, zipCode};
        };

        void printDL(){
            auto loc=getDL();
            cout<<"The destination is "<<get<0>(loc)<<" "<<get<1>(loc)<<", "<<get<2>(loc)<<", "<<get<3>(loc)<<"."<<endl;system("pause");system("cls");
        }
};

// class KowalskiAnalysis:protected EssVar{
    
//     // todo: check database to find latitude and longitude to calculate disantce.

//     // todo: check means of transportation to calculate ETA.
// };