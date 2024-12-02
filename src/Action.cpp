#include "../include/Action.h"
#include "../include/Simulation.h"
#include "../include/Plan.h"
#include "../include/SelectionPolicy.h"
#include <iostream>

using namespace std;

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

// SimulateStep::act(Simulation &simulation) {
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

AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
settlementName(settlementName), settlementType(settlementType){}

void AddSettlement::act(Simulation &simulation) {
    Settlement stl = Settlement(settlementName,settlementType);
    simulation.addSettlement(&stl);
}

AddSettlement* AddSettlement::clone() const {
     return new AddSettlement(*this); 
}

AddFacility::AddFacility(const string &facilityName,
 const FacilityCategory facilityCategory, 
 const int price, const int lifeQualityScore, 
 const int economyScore, const int environmentScore):facilityName(facilityName),
 facilityCategory(facilityCategory), price(price), lifeQualityScore(lifeQualityScore),
 economyScore(economyScore), environmentScore(environmentScore){}

void AddFacility::act(Simulation& simulation) {
    FacilityType f(facilityName, facilityCategory, price, lifeQualityScore,
                    economyScore, environmentScore);
    bool status = simulation.addFacility(f);
    // TODO
}

AddFacility* AddFacility::clone() const {
     return new AddFacility(*this); 
}



PrintPlanStatus::PrintPlanStatus(int planID):planId(planID){}

void PrintPlanStatus::act(Simulation &simulation){
    Plan plan = simulation.getPlan(planId);
    cout << plan.toString() <<endl;
}

PrintPlanStatus * PrintPlanStatus::clone() const{return new PrintPlanStatus(*this);}

 const string PrintPlanStatus::toString() const{
    return "print plan status for plan id:" + to_string(planId);
 }