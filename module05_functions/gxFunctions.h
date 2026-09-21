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