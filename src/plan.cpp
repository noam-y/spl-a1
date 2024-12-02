
#include <vector>
#include "../include/Plan.h"
#include "../include/Settlement.h"
#include "../include/SelectionPolicy.h"
#include "../include/Facility.h"
#include <iostream>
using std::vector;
using namespace std;


Plan::Plan(const int planId,
const Settlement &settlement,
SelectionPolicy *selectionPolicy, 
const vector<FacilityType> &facilityOptions):
plan_id(planId),
settlement(settlement), 
selectionPolicy(selectionPolicy), 
status(PlanStatus::AVALIABLE),
facilityOptions(facilityOptions),
life_quality_score(), 
economy_score(0), 
environment_score(0) 
{
    vector<Facility*> facilities; //TODO FIX
    vector<Facility*> underConstruction;
}


Plan::Plan(const Plan& other):plan_id(other.plan_id),
settlement(other.settlement),
status(other.status),
facilityOptions(other.facilityOptions),
life_quality_score(other.life_quality_score),
economy_score(other.economy_score),
environment_score(other.environment_score){
    selectionPolicy = other.selectionPolicy->clone(); // TODO IF OTHER.SELPOLICY IS NULL
    vector<Facility*> facilities; 
    vector<Facility*> underConstruction;
    vector<FacilityType> facilityOptions;
    
    for (int i = 0;  static_cast<std::size_t>(i) <other.facilities.size() ; i++){
        this->facilities.push_back(other.facilities.at(i)->clone());
    }
    for (int i = 0;  static_cast<std::size_t>(i) <other.underConstruction.size() ; i++){
        this->underConstruction.push_back(other.underConstruction.at(i)->clone());
    }
    // TODO facilityOptions
 }

Plan::Plan(Plan&& other) noexcept:plan_id(other.plan_id),
settlement(other.settlement),
status(other.status),
facilityOptions(other.facilityOptions),
life_quality_score(other.life_quality_score),
economy_score(other.economy_score),
environment_score(other.environment_score){
    for (int i = 0;  static_cast<std::size_t>(i) <other.facilities.size() ; i++){
        other.facilities.at(i) = nullptr;
    }
    for (int i = 0;  static_cast<std::size_t>(i) <other.underConstruction.size() ; i++){
        other.underConstruction.at(i) = nullptr;
    }
    other.selectionPolicy = nullptr;

}


//TODO: COPY CONSTRUCTOR destructor, copy constructor, HALF RULE OF FIVE- EXPLAINED IN FORUM

const int Plan::getID() const{
    return plan_id;
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
void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
     delete this->selectionPolicy;
     this->selectionPolicy = selectionPolicy;
     };// TODO destruct prev selection policy


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
    if ((facility->getStatus()) == FacilityStatus::OPERATIONAL){
        facilities.push_back(facility);
        this->economy_score = this->economy_score + facility->getEconomyScore();
        this->environment_score = this->environment_score + facility->getEnvironmentScore();
        this->life_quality_score = this->life_quality_score + facility->getLifeQualityScore();
        // TODO update balance
    }
    else{
        underConstruction.push_back(facility);
    }
    
}

const string Plan::toString() const{
    string s = "plan id: " + to_string(plan_id) + "settlementName: " + settlement.Settlement::getName()
    + "\n status: " + getStatusString() +  "scores- economy:" 
    + to_string(economy_score) + " enviroment:" + to_string(environment_score) +
    "life quality: " + to_string(life_quality_score);
    return s;
}


Plan::~Plan() {
    delete selectionPolicy;
    
    for (int i = 0; static_cast<std::size_t>(i) <facilities.size() ; i++){
        delete facilities.at(i);
    }

    for (int i = 0; static_cast<std::size_t>(i) <underConstruction.size() ; i++){
        delete underConstruction.at(i);
    }

}


