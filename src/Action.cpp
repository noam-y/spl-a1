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

 void SimulateStep::act(Simulation &simulation) {
    for (int i = 0; i < numOfSteps; i++){
        simulation.step();
    }
 }

const string SimulateStep::toString() const{return "moving " + to_string(numOfSteps) + " steps";}
SimulateStep *SimulateStep::clone() const{return new SimulateStep(*this);}



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
const string AddSettlement::toString() const{ return "adding settlement" + settlementName + "to simulation"; }



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

const string AddFacility::toString() const {
        string s= "Facility Name: " + facilityName + "\n" +
               "Category: " + std::to_string(static_cast<int>(facilityCategory)) + "\n" +
               "Price: " + std::to_string(price) + "\n" +
               "Life Quality Score: " + std::to_string(lifeQualityScore) + "\n" +
               "Economy Score: " + std::to_string(economyScore) + "\n" +
               "Environment Score: " + std::to_string(environmentScore);
        return s;
}


PrintPlanStatus::PrintPlanStatus(int planID):planId(planID){}

void PrintPlanStatus::act(Simulation &simulation){
    Plan plan = simulation.getPlan(planId);
    cout << plan.toString() <<endl;
}

PrintPlanStatus * PrintPlanStatus::clone() const{return new PrintPlanStatus(*this);}

 const string PrintPlanStatus::toString() const{
<<<<<<< HEAD
    return "print plan status for plan id:" + to_string(planId);
 }
=======
    cout << "print plan status for plan id:" + to_string(planId) << endl;
 }



 ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):planId(planId), newPolicy(newPolicy){}

void ChangePlanPolicy::act(Simulation &simulation){
    Plan plan = simulation.getPlan(planId);
    if(newPolicy == "nve"){plan.setSelectionPolicy(new NaiveSelection());}
    else if (newPolicy == "eco"){plan.setSelectionPolicy(new EconomySelection());        }
    else if (newPolicy == "env"){plan.setSelectionPolicy(new SustainabilitySelection());}
    else if (newPolicy == "bal"){
        plan.setSelectionPolicy(new BalancedSelection(plan.getlifeQualityScore(),
        plan.getEconomyScore(),
        plan.getEnvironmentScore()));
    }

}
ChangePlanPolicy *ChangePlanPolicy:: clone() const{return new ChangePlanPolicy(*this);}
const string ChangePlanPolicy::toString() const{
    string s = "changing planID" + to_string(planId) + "to policy" + newPolicy;
}


PrintActionsLog::PrintActionsLog(){}
void act(Simulation &simulation) {
    //TODO
}
PrintActionsLog *PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}
const string PrintActionsLog::toString() const{return "actions log";} //TODO

Close::Close(){}
void Close::act(Simulation &simulation){
    simulation.close();
}

Close *Close::clone() const{return new Close(*this);}
const string Close::toString() const{return "closing simulation ";}

BackupSimulation::BackupSimulation(){}
 void BackupSimulation::act(Simulation &simulation){
 }
>>>>>>> 950d9e2afbcc9bcddb99364dd009ef878ac9d73d
