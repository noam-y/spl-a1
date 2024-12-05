#include "../include/Action.h"
#include "../include/Simulation.h"
#include "../include/Plan.h"
#include "../include/SelectionPolicy.h"
#include <iostream>
extern Simulation* backup;
using namespace std;

BaseAction::BaseAction():errorMsg(), status(){}

ActionStatus BaseAction::getStatus() const{
    return status;
}

string BaseAction::getStatusString() const{
    string s;
    if (status == ActionStatus::COMPLETED){
        s= "COMPLETED";

    }
    else{
        s= "ERROR";
    }
    return s;
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
    complete();
 }

const string SimulateStep::toString() const{return "moving " + to_string(numOfSteps) + " steps";}
SimulateStep *SimulateStep::clone() const{return new SimulateStep(*this);}



AddPlan::AddPlan(const string &settlementName, const string &selectionPolicy):
settlementName(settlementName),selectionPolicy(selectionPolicy){}

void AddPlan::act(Simulation &simulation){
    Settlement& stl = simulation.getSettlement(settlementName);
    SelectionPolicy* selectP = nullptr;
    if (selectionPolicy == "bal"){
        selectP = new BalancedSelection(0,0,0);
    }
    else if (selectionPolicy == "nve"){
        selectP = new NaiveSelection();
    }
    else if(selectionPolicy == "eco"){
        selectP = new EconomySelection();
    }
    else if(selectionPolicy == "env"){
        selectP = new SustainabilitySelection();
    }
    else{
        error("selectionPolicyDoes not exist");
    }
    simulation.addPlan(stl, selectP);
    complete();
}

const string AddPlan::toString() const{
    return "adding plan of " + selectionPolicy + " to settlement: " + settlementName;
}

AddPlan *AddPlan::clone() const{
    return new AddPlan(*this);
}


AddSettlement::AddSettlement(const string &settlementName,SettlementType settlementType):
settlementName(settlementName), settlementType(settlementType){}

void AddSettlement::act(Simulation &simulation) {
    Settlement *stl = new Settlement(settlementName,settlementType);
    bool status = simulation.addSettlement(stl);
    if (status){complete();}
    else{error("action AddSettlement not complete");}
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
    const FacilityType& f = FacilityType(facilityName, facilityCategory, price, lifeQualityScore,
                    economyScore, environmentScore);
    bool status = simulation.addFacility(f);
    if (status){complete();}
    else{error("action AddFacility not complete");}
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
    if (simulation.getPlanCount() - 1 < planId)  {
        error ("Plan doesn't exist");
    }
    else{
        Plan plan = simulation.getPlan(planId);
        cout << plan.toString() <<endl;
    
        complete();
    }

}

PrintPlanStatus * PrintPlanStatus::clone() const{return new PrintPlanStatus(*this);}

 const string PrintPlanStatus::toString() const{
    return "print plan status for plan id:" + to_string(planId);
 }



BackupSimulation:: BackupSimulation() {}

void BackupSimulation:: act(Simulation &simulation) {
    // Delete the previous backup if exists
    if (backup == nullptr) {
        backup = new Simulation(simulation); 
    }
    else{
        *backup = simulation;
    }


    complete();
}


BackupSimulation *BackupSimulation::clone() const {
    return new BackupSimulation();
}

const  string BackupSimulation:: toString() const {
      return "backup: COMPLETED";

}


RestoreSimulation:: RestoreSimulation(){}

void RestoreSimulation:: act(Simulation &simulation) {
    if (backup == nullptr) {
        error("No backup available");
        cout << getErrorMsg() << endl;
    }
    else {
        simulation = *backup;
        complete();

    }

}

RestoreSimulation *RestoreSimulation::clone() const {
    return new RestoreSimulation(*this);
}

const string RestoreSimulation:: toString() const {
    
}


 ChangePlanPolicy::ChangePlanPolicy(const int planId, const string &newPolicy):
 planId(planId), newPolicy(newPolicy){}
 void ChangePlanPolicy::act(Simulation &simulation){
    Plan& p = simulation.getPlan(planId);
    cout << "plan id: "  + to_string(planId) + "\n old policy: " + p.getSelectionPolicy()->toString() << endl;
    if (newPolicy == "bal"){
        if (p.getSelectionPolicy()->toString() == "balance"){
            p.setSelectionPolicy(new BalancedSelection(simulation.getPlan(planId).getlifeQualityScore(),
            simulation.getPlan(planId).getEconomyScore(),
            simulation.getPlan(planId).getEnvironmentScore()));
        }
        
    }
    else if (newPolicy == "nve"){
        p.setSelectionPolicy( new NaiveSelection());
    }
    else if(newPolicy == "eco"){
        p.setSelectionPolicy(new EconomySelection());
    }
    else if(newPolicy == "env"){
        p.setSelectionPolicy(new SustainabilitySelection());
    }
    else{
        error( "no selection given- ERROR" );
    }
    cout << "\n new policy:" + p.getSelectionPolicy()->toString() <<endl;
    complete();
 }
ChangePlanPolicy *ChangePlanPolicy::clone() const{return new ChangePlanPolicy(*this);}
const string ChangePlanPolicy::toString() const{return "Change policy for id" + to_string(planId) 
+ "\n policy" + newPolicy;}

  

PrintActionsLog::PrintActionsLog(){}
void PrintActionsLog::act(Simulation &simulation){
    for (BaseAction* a : simulation.getActionsLog()){
        cout << a->toString() + " : " + a->getStatusString() << endl;
    }
    complete();
}
PrintActionsLog *PrintActionsLog::clone() const{return new PrintActionsLog(*this);}
const string PrintActionsLog::toString() const{return "printing action log";}



Close::Close(){}
void Close::act(Simulation &simulation){
    simulation.close();
    complete();
}
Close *Close::clone() const{return new Close(*this);}
const string Close::toString() const{return "Closing Program, goodbye!";}

