#include "Simulation.h"
#include "Settlement.h"
#include "SelectionPolicy.h"


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

    Settlement s = Settlement("BS", SettlementType::CITY);
    vector<FacilityType> facilities = {
    FacilityType("Facility1", FacilityCategory::LIFE_QUALITY, 100, 80, 70, 90),
    FacilityType("Facility2", FacilityCategory::ECONOMY, 200, 60, 85, 75),
    FacilityType("Facility3", FacilityCategory::ECONOMY, 150, 65, 80, 70)
};

EconomySelection selection;
cout << selection.toString() << endl;
    

    //cout << s.toString() << endl;
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }


   
    return 0;
}

