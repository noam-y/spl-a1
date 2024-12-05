
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
life_quality_score(0), 
economy_score(0), 
environment_score(0){
    vector<Facility*> facilities; //TODO FIX
    vector<Facility*> underConstruction;
    constructionLimit = settlement.getConstructionLimit();
}

Plan::Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions, int LifeScore, int EconomyScore, int EnviromentScore) 
: plan_id(planId), settlement(settlement), selectionPolicy(selectionPolicy), status(PlanStatus::AVALIABLE), facilities(), underConstruction(), facilityOptions(facilityOptions), life_quality_score(0), economy_score(0), environment_score(0){}


Plan::Plan(const Plan& other):plan_id(other.plan_id),
settlement(other.settlement),
status(other.status),
facilityOptions(other.facilityOptions),
life_quality_score(other.life_quality_score),
economy_score(other.economy_score),
environment_score(other.environment_score), constructionLimit(other.constructionLimit){
    selectionPolicy = other.selectionPolicy->clone(); // TODO IF OTHER.SELPOLICY IS NULL
    vector<Facility*> facilities; 
    vector<Facility*> underConstruction;
    
    for (std::size_t i = 0; i < other.facilities.size(); i++) {
    facilities.push_back(other.facilities.at(i)->clone());
    }
    for (std::size_t i = 0; i < other.underConstruction.size(); i++) {
    underConstruction.push_back(other.underConstruction.at(i)->clone());
    }
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
        other.facilities.at(i) = nullptr;
    }
    for (int i = 0;  static_cast<std::size_t>(i) <other.underConstruction.size() ; i++){
        other.underConstruction.at(i) = nullptr;
    }
    selectionPolicy=other.selectionPolicy;
    other.selectionPolicy = nullptr;
}


//TODO: COPY CONSTRUCTOR destructor, copy constructor, HALF RULE OF FIVE- EXPLAINED IN FORUM

const Settlement& Plan::getSettlement() const{
    return settlement;
}

const PlanStatus Plan::getStatus() const{
    return status;
}

const SelectionPolicy* Plan::getSelectionPolicy() const{
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
    if (selectionPolicy != nullptr){
        delete this->selectionPolicy;
    }
     this->selectionPolicy = selectionPolicy;
     };// TODO destruct prev selection policy


void Plan::step(){
    while (status == PlanStatus::AVALIABLE){
        if (selectionPolicy == nullptr) {
        std::cerr << "Error: selectionPolicy is nullptr!" << std::endl;
        return;
        }

        if (facilityOptions.empty()) {
        std::cerr << "Error: facilityOptions is empty!" << std::endl;
        return;
        }
        FacilityType typeBuild = selectionPolicy->selectFacility(facilityOptions);
        Facility* toBuild = new Facility(typeBuild, settlement.getName());
        addFacility(toBuild);
        constructionLimit = constructionLimit -1;
        if (constructionLimit == 0){
            status = PlanStatus::BUSY;
        }
    }
    for (std::size_t i = underConstruction.size(); i-- > 0;){
        FacilityStatus f1 = underConstruction.at(i)->step();
        if (f1 == FacilityStatus::OPERATIONAL){
            addFacility(underConstruction.at(i));
            underConstruction.erase(underConstruction.begin() + i);
            // we now have more space availiable to construction
            constructionLimit = constructionLimit + 1;
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
    string s = "planID: " + to_string(this->plan_id) + "\n" + "Settlement Name: " + this->getSettlement().getName() +
    "\n planStatus " + this->getStatusString() + "\n selectionPolicy: "
    + this->getSelectionPolicy()->toString() + "\n life quality: " + to_string(this->getlifeQualityScore()) +
    "\n economy score: " + to_string(this->getEconomyScore()) + "\n enviroment Score:" + to_string (this->getEnvironmentScore());
    //TODO
    for (int i = 0; static_cast<std::size_t>(i) <this->underConstruction.size() ; i++){
        s = s + "\n Facility name: " + underConstruction.at(i)->getName() + " status: UNDERCONSTRUCTION";
    }
    for (int i = 0; static_cast<std::size_t>(i) <this->getFacilities().size() ; i++){
        s = s + "\n Facility name: " + getFacilities().at(i)->getName() + " status: OPERATIONAL";
    }
    return s;
}


Plan::~Plan() {
    delete selectionPolicy;
    selectionPolicy = nullptr;
    for (int i = 0; static_cast<std::size_t>(i) <facilities.size() ; i++){
        delete facilities.at(i);
    }

    for (int i = 0; static_cast<std::size_t>(i) <underConstruction.size() ; i++){
        delete underConstruction.at(i);
    }

}


