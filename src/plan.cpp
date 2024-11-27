#pragma once
#include <vector>
#include "../include/Plan.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"
using std::vector;


Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(), facilities(), underConstruction(), facilityOptions(facilityOptions){
    life_quality_score = 0;
    economy_score = 0;
    environment_score = 0;
} 

const int Plan::getlifeQualityScore() const{
    return life_quality_score;
}
const int Plan::getEconomyScore() const{
    return economy_score;
}
const int Plan::getEnvironmentScore() const{
    return environment_score;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){ this->selectionPolicy = selectionPolicy;};
        // void step(); //TODO
        // void printStatus();
        // const vector<Facility*> &getFacilities() const;
        // void addFacility(Facility* facility);
        // const string toString() const;

    // private:
    //     int plan_id;
    //     const Settlement &settlement;
    //     SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
    //     PlanStatus status;
    //     vector<Facility*> facilities;
    //     vector<Facility*> underConstruction;
    //     const vector<FacilityType> &facilityOptions;
    //     int life_quality_score, economy_score, environment_score;
