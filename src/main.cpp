#include "Simulation.h"
#include "Settlement.h"
#include "Action.h"
#include <iostream>

using namespace std;

Simulation* backup = nullptr;




int main(int argc, char** argv){
    if(argc!=2){
        cout << "usage: simulation <config_path>" << endl;
        return 0;
    }

    string configurationFile = argv[1];
    Simulation simulation(configurationFile);
    simulation.start();

    Settlement s = Settlement("BS", SettlementType::CITY);
    cout << s.toString() << endl;
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }


   
    return 0;
}

