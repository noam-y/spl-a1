#pragma once
#include <vector>
#include "../include/Plan.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"
#include "../include/Facility.h"
#include <iostream>
using std::vector;
using namespace std;


Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions):
plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), facilityOptions(facilityOptions){
     status = PlanStatus::AVALIABLE;
    vector<Facility*> facilities; //TODO FIX
    vector<Facility*> underConstruction;
    life_quality_score = 0;
    economy_score = 0;
    environment_score = 0;
} 
//TODO: COPY CONSTRUCTOR destructor, copy constructor, copy assignment opreator HALF RULE OF FIVE- EXPLAINED IN FORUM
const int Plan::getlifeQualityScore() const{
    return life_quality_score;
}
const int Plan::getEconomyScore() const{
    return economy_score;
}
const int Plan::getEnvironmentScore() const{
    return environment_score;
}
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){ this->selectionPolicy = selectionPolicy;};// TODO destruct prev selection policy


void Plan::step(){
    for (Facility* facility : underConstruction) {
        FacilityStatus f1 = facility->step();
        if (f1 == FacilityStatus::OPERATIONAL){
            addFacility(facility);
        }
    }
}


void Plan::printStatus(){
    string s = getStatusString();
    cout << "status: " + s << endl;
}

const string Plan::getStatusString() const{
    string s;
    if (status == PlanStatus:: AVALIABLE){
        s = "AVALIABLE";
    }
    else{
        s = "UNDER CONSTRUCTION";
    }
    return s;
}

const vector<Facility*> &Plan::getFacilities() const{
    return facilities;
}

void Plan::addFacility(Facility* facility){
    facilities.push_back(facility);
}

const string Plan::toString() const{
    string s = "plan id: " + to_string(plan_id) + "settlementName: " + settlement.Settlement::getName()
    + "\n status: " + getStatusString() +  "scores- economy:" 
    + to_string(economy_score) + " enviroment:" + to_string(environment_score) +
    "life quality: " + to_string(life_quality_score);
    return s;
}

    // private:
    //     int plan_id;
    //     const Settlement &settlement;
    //     SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
    //     PlanStatus status;
    //     vector<Facility*> facilities;
    //     vector<Facility*> underConstruction;
    //     const vector<FacilityType> &facilityOptions;
    //     int life_quality_score, economy_score, environment_score;
