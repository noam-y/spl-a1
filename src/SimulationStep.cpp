#include "../include/Simulation.h"

#include <iostream>

using namespace std;

Simulation::Simulation (const string &configFilePath){
    this->isRunning = true;
    this->planCounter = 0;
}
// Rule of Five
Simulation::~Simulation() {
    //Delete all settlements objects
     for (Settlement* s : settlements) {
        delete settlement;
    }
    settlements.clear();

    // Delete all BaseAction objects
    for (BaseAction* a : actionsLog) {
        delete action;
    }
    actionsLog.clear();
}

Simulation::Simulation(const Simulation& other): isRunning(other.isRunning),planCounter(other.planCounter),plans(other.plans),facilitiesOptions(other.facilitiesOptions) {
    // Deep copy settlements
    for (const Settlement* s : other.settlements) {
        settlements.push_back(new Settlement(*settlement));
    }
    // Deep copy actions
    for (const BaseAction* a : other.actionsLog) {
        actionsLog.push_back(action->clone());
    }
} 
Simulation::Simulation& operator=(const Simulation& other) {
    if (this!= other) {
        ~Simulation(this);
    }
    this.isRunning= other.isRunning;
    this.planCounter= other.planCounter;
    this.plans= other.plans;
    this.facilitiesOptions= other.facilitiesOptions;
    //deep dopy:
    for (const Settlement* s: other.Settlements){
        this.Settlements.push_back(new Settlement(*settlement));
    }
    for (const BaseAction a : other.BeseAction){
        this.BaseAction.push_back(action->clone());
    }
    return *this;
} 

Simulation::Simulation(Simulation&& other) noexcept: isRunning(other.isRunning), planCounter(other.planCounter), plans(std::move(other.plans)), facilitiesOptions(std::move(other.facilitiesOptions)), settlements(std::move(other.settlements)), actionsLog(std::move(other.actionsLog)) {
    // Clear other to leave it in a valid state
    other.isRunning = false;
    other.planCounter = 0;
}   

Simulation& Simulation::operator=(Simulation&& other) noexcept {
    if (this != &other) { 
        clearResources(); // Clean up existing resources

        // Transfer ownership
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        plans = std::move(other.plans);
        facilitiesOptions = std::move(other.facilitiesOptions);
        settlements = std::move(other.settlements);
        actionsLog = std::move(other.actionsLog);

        // Clear other to leave it in a valid state
        other.isRunning = false;
        other.planCounter = 0;
    }
    return *this;
}

       
void Simulation::start(){
    cout << "The simulation has started" << endl;
}

void Simulation::  addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
        int planID = planCounter;
        planCounter++;
        Plan p = Plan(planID, &settlement, *selectionPolicy, facilitiesOptions); 
        plans.push_back(p);
 }

void Simulation:: addAction(BaseAction *action){
    actionsLog.push_back(action);
}



bool Simulation:: addSettlement(Settlement *settlement){
        for (const *settlement s : settlements) {
            if (s->getName() == settlement->getName()) {
                return false;
                }
            }
            *settlement.push_back(settlement);
            return true;
        }


bool Simulation:: addFacility(FacilityType facility){
    // Check if the facility with the same name already exists
    for (const FacilityType& f : facilitiesOptions) {
        if (f.getName() == facility.getName()) {
            return false; 
        }
    }
    // If not found, add the facility to the vector
    facilitiesOptions.push_back(facility);
    return true; 
        }



bool Simulation:: isSettlementExists(const string &settlementName){
    for (Settlement* s : settlements) {
        if (s ->getName()== settlementName)
        return true;
    }
    return false;

}

Settlement &Simulation:: getSettlement(const string &settlementName){
    for (Settlement* s : settlements) {
        if (s ->getName()== settlementName)
         s->getName();
         return *s;
    }
    // If no settlement is found with the given name, throw an exception or handle the error.
    throw std::runtime_error("No such settlement exists");
}

Plan &Simulation:: getPlan(const int planID) {
    for (Plan p : plans){
        if (p.getID== planID){ //NEED EO IMPLEMENT GETID METHOD
            return p;
        }

    }
    // If no plan is found with the given ID, throw an exception or handle the error.
    throw std::runtime_error("No such plan exists");
}
void Simulation:: step(){
    for (int i = 0; i < planCounter; i++){
                plans[i].step();
            }
    }

void Simulation:: close(){
    isRunning = false;
}

void Simulation:: open() {
        isRunning = true;
}
