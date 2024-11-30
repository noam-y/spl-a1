#include <iostream>
using namespace std;
#include "../include/Action.h"
#include "../include/Plan.h"
#include "../include/Simulation.h"
#include <string>

BaseAction::BaseAction():errorMsg(), status(){}

ActionStatus BaseAction::getStatus() const{
    return status;
}

void BaseAction::complete(){status = ActionStatus::COMPLETED;}
void BaseAction::error(string errorMsg){
    status = ActionStatus::ERROR;
    cout << errorMsg << endl;
} // TODO
const string& BaseAction::getErrorMsg() const{
    return errorMsg;
}

AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy){
    vector<FacilityType> f1;

    //Plan p1 = Plan(Simulation::genPlanID, settlement, selectionPolicy, f1&);
}
