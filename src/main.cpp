#include "../include/Simulation.h"
#include "../include/Facility.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"


#include <iostream>

using namespace std;

Simulation* backup = nullptr;




int main(int argc, char** argv){
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }

    string configurationFile = argv[1];
    // Simulation simulation(configurationFile);
    // simulation.start();
    vector<FacilityType> ft = vector<FacilityType>();
    ft.push_back(FacilityType("Desalination Plant",FacilityCategory::ECONOMY,2,2,1,2));
    ft.push_back(FacilityType("Kindergarten",FacilityCategory::ECONOMY,12,1,0,0));
    ft.push_back(FacilityType("Hospital",FacilityCategory::ECONOMY,6,3,1,2));
    ft.push_back(FacilityType("1",FacilityCategory::ECONOMY,12,1,0,0));
    ft.push_back(FacilityType("2",FacilityCategory::ECONOMY,12,1,0,0));
    ft.push_back(FacilityType("3",FacilityCategory::ECONOMY,12,1,0,0));
    NaiveSelection ns = NaiveSelection();

    cout<< ns.selectFacility(ft).getName() << endl;
    cout<< ns.selectFacility(ft).getName() << endl;
    cout<< ns.selectFacility(ft).getName() << endl;

    

    //cout << s.toString() << endl;
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }


   
    return 0;
}

