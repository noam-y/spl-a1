
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
selectionPolicy(selectionPolicy->clone()), 
status(PlanStatus::AVALIABLE),
facilities(),
underConstruction(),
facilityOptions(facilityOptions),
life_quality_score(0), 
economy_score(0), 
environment_score(0)
 {
    constructionLimit = settlement.getConstructionLimit();
}

Plan::Plan(const int planId, const Settlement &settlement,
SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions,
int LifeScore, int EconomyScore, int EnviromentScore) 
: plan_id(planId),
settlement(settlement),
selectionPolicy(selectionPolicy->clone()),
status(PlanStatus::AVALIABLE), facilities(), underConstruction(),
facilityOptions(facilityOptions), life_quality_score(0),
 economy_score(0), environment_score(0){

 }


Plan::Plan(const Plan& other):plan_id(other.plan_id),
settlement(other.settlement),
status(other.status),
facilities(), underConstruction(),
facilityOptions(other.facilityOptions),
life_quality_score(other.life_quality_score),
economy_score(other.economy_score),
environment_score(other.environment_score),
constructionLimit(other.constructionLimit){
    selectionPolicy = other.selectionPolicy->clone(); 
    
    for (std::size_t i = 0; i < other.facilities.size(); i++) {
    facilities.push_back(other.facilities.at(i)->clone());
    }
    for (std::size_t i = 0; i < other.underConstruction.size(); i++) {
    underConstruction.push_back(other.underConstruction.at(i)->clone());}
}

Plan::Plan(Plan&& other) noexcept:plan_id(other.plan_id),
settlement(other.settlement),
status(other.status),
facilityOptions(other.facilityOptions),
life_quality_score(other.life_quality_score),
economy_score(other.economy_score),
environment_score(other.environment_score),
constructionLimit(other.constructionLimit){
    for (int i = 0;  static_cast<std::size_t>(i) <other.facilities.size() ; i++){
        facilities.push_back(other.facilities[i]);
        other.facilities.at(i) = nullptr;
    }
    for (int i = 0;  static_cast<std::size_t>(i) <other.underConstruction.size() ; i++){
        underConstruction.push_back(other.underConstruction[i]);
        other.underConstruction.at(i) = nullptr;
    }
    other.underConstruction.clear();
    other.facilities.clear();
    selectionPolicy=other.selectionPolicy;
    other.selectionPolicy = nullptr;
}




const Settlement& Plan::getSettlement() const{
    return settlement;
}

const PlanStatus Plan::getStatus() const{
    return status;
}

SelectionPolicy* Plan::getSelectionPolicy() const{
    return selectionPolicy;

}

vector<Facility*> Plan:: getUnderConstruction(){
    return underConstruction;
}

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
    if (this->selectionPolicy != nullptr){
        delete this->selectionPolicy;
    }
     this->selectionPolicy = selectionPolicy;
     };


void Plan::step(){

    while (constructionLimit > 0){
            Facility* toBuild = new Facility(selectionPolicy->selectFacility(facilityOptions), settlement.getName());
            addFacility(toBuild);
            constructionLimit = constructionLimit -1;
    }
        
    for (size_t i = 0; i < underConstruction.size();){
        FacilityStatus f1 = underConstruction.at(i)->step();
        if (f1 == FacilityStatus::OPERATIONAL){
            addFacility(underConstruction.at(i));
            underConstruction.erase(underConstruction.begin() + i);
            // we now have more space availiable to construction
            constructionLimit = constructionLimit + 1;
        }
        else{
            i++;
        }
    }

    if (constructionLimit == 0){status = PlanStatus::BUSY;}
    else{status = PlanStatus::AVALIABLE;}
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
        s = "BUSY";
    }
    return s;
}

const vector<Facility*> &Plan::getFacilities() const{
    return facilities;
}

void Plan::addFacility(Facility* facility){
    if (!facility) {
    std::cerr << "Error: Null pointer passed to addFacility!" << std::endl;
    return; // Do not proceed
    }
    if ((facility->getStatus()) == FacilityStatus::OPERATIONAL){
        facilities.push_back(facility);
        this->economy_score = this->economy_score + facility->getEconomyScore();
        this->environment_score = this->environment_score + facility->getEnvironmentScore();
        this->life_quality_score = this->life_quality_score + facility->getLifeQualityScore();
    }
    else{
        underConstruction.push_back(facility);
    }
    
}

const string Plan::toString() const{
  
string s = "planID: " + to_string(this->plan_id) + "\n" + "Settlement Name: " + this->getSettlement().getName() +
"\nplanStatus " + this->getStatusString() + "\nselectionPolicy: "
+ this->getSelectionPolicy()->toString() + "\nlife quality: " + to_string(this->getlifeQualityScore()) +
"\neconomy score: " + to_string(this->getEconomyScore()) + "\nenviroment Score:" + to_string (this->getEnvironmentScore());
for (std::size_t i = 0; i < this->underConstruction.size(); ++i) {
    s += "\n" + underConstruction.at(i)->toString() + "status: UNDERCONSTRUCTION";
}

for (std::size_t i = 0; i <this->getFacilities().size() ; i++){
    s += "\n" + getFacilities().at(i)->toString() + "status: OPERATIONAL";
}

return s;

}

void Plan::addInfo(const Plan& other){
    // this func adds info about facilities, facilities underconsruction, and scores.
    // mainly for restore action
    status = other.status;
    // copying facilites- 
for (auto facility : facilities) {
    delete facility;
}
facilities.clear();

for (auto facility : underConstruction) {
    delete facility;
}
underConstruction.clear();

    for (int i = 0;  static_cast<std::size_t>(i) <other.facilities.size() ; i++){
        facilities.push_back(new Facility(*other.facilities.at(i)));
    }

    //copying underconstruction
    underConstruction.clear();
    for (int i = 0;  static_cast<std::size_t>(i) <other.underConstruction.size() ; i++){
        underConstruction.push_back(new Facility(*other.underConstruction.at(i)));
    }
}


Plan::~Plan() {
    if (selectionPolicy){
        delete selectionPolicy;
    }
    for (int i = 0; static_cast<std::size_t>(i) <facilities.size() ; i++){
        if (facilities.at(i) != nullptr)
        delete facilities.at(i);
        facilities.at(i) = nullptr;
    }

    for (int i = 0; static_cast<std::size_t>(i) <underConstruction.size() ; i++){
        delete underConstruction.at(i);
        underConstruction.at(i)= nullptr;
    }

}


