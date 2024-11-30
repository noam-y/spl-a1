#include <iostream>
using namespace std;
#include "../include/Action.h"
#include "../include/Plan.h"
#include "../include/Simulation.h"
#include "../include/selectionPolicy.h"

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

SimulateStep::SimulateStep(const int numOfSteps):numOfSteps(numOfSteps){}

// SimulateStep::act(Simulation &simulation) override{
//     simulation.
// }
AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName),selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement stl = simulation.getSettlement(settlementName);
    SelectionPolicy* selectP = nullptr;
    if (selectionPolicy == "bal"){
        selectP = new BalancedSelection(0,0,0);
    }
    else if (selectionPolicy == "nav"){
        selectP = new NaiveSelection();
    }
    else if(selectionPolicy == "eco"){
        selectP = new EconomySelection();
    }
    else{
        selectP = new SustainabilitySelection();
    }
    simulation.addPlan(stl, selectP);
}