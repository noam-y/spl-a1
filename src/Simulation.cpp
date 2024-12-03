#include "../include/Simulation.h"
#include "../include/Plan.h"
#include "../include/Action.h"
#include "../include/Facility.h"
#include "../include/SelectionPolicy.h"
#include "../include/Auxiliary.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Simulation::Simulation(const std::string &configFilePath) : isRunning(false), planCounter(0) {
    std::ifstream configFile(configFilePath);
    initializeFile(configFilePath); //using helper function
}

void Simulation::initializeFile(const std::string &configFilePath) {
    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
            throw std::runtime_error("Error: Unable to open config file: " + configFilePath);
        }

        std:: string line; 
        while (std::getline(configFile, line)) {
            vector<string> parsedArgs = Auxiliary::parseArguments(line);
            if (parsedArgs.empty()) continue; //avoid unnecessary computations or potential errors.
            //Parsing settlements
            if (parsedArgs[0] == "settlement") {  
            string sName = parsedArgs[1];
            int sTypeInt = std::stoi(parsedArgs[2]);  
            SettlementType sType = static_cast<SettlementType>(sTypeInt);  // Convert int to enum
            if (isSettlementExists(sName)){
                cout <<"Settlement already exist"<< endl;
            }
            settlements.push_back(new Settlement(sName, sType));
        }
        //Parsing facility
        else if (parsedArgs[0] == "facility") {
            string fName = parsedArgs[1]; 
            int categoryInt = std::stoi(parsedArgs[2]);  // Convert string to integer
            FacilityCategory fCategory = static_cast<FacilityCategory>(categoryInt);
            int fPrice = std::stoi(parsedArgs[3]);
            int lifeQualityScore = std::stoi(parsedArgs[4]);
            int economyScore = std::stoi(parsedArgs[5]);
            int environmentScore = std::stoi(parsedArgs[6]);
            //checks if the facility allready exist
            bool isExist = false;
            for (std::size_t i = 0; i < facilitiesOptions.size(); i++){ // TODO UNDERSTAND
                if (fName == facilitiesOptions[i].getName()){
                    isExist = true;
                }
            }
            if (!isExist){
                cout << "Facility is being created"<< endl;
                facilitiesOptions.push_back(FacilityType(fName, fCategory, fPrice, lifeQualityScore, economyScore, environmentScore));
            }
            else{
                cout << "facility exists" <<endl;
            }
            
        }
        //Parsing plan
        else if (parsedArgs[0] == "plan") {
        Settlement* sName = nullptr;
        for (int i = 0;  static_cast<std::size_t>(i) < settlements.size() ; i++){
            if (settlements.at(i)->getName() == parsedArgs[1] ){
                sName = settlements.at(i);
                break;
                }
        }
         
        string policyName = parsedArgs[2];

            if (policyName == "bal") {
                SelectionPolicy* bal = new BalancedSelection(0,0,0); 
                plans.push_back(Plan(planCounter,*sName,bal,facilitiesOptions));  
            } 
            else if (policyName== "eco") {
                SelectionPolicy* eco = new EconomySelection ();
                plans.push_back(Plan(planCounter,*sName,eco,facilitiesOptions));  
            }
            else if (policyName == "env") {
                SelectionPolicy* env = new SustainabilitySelection();  
                plans.push_back(Plan(planCounter,*sName,env,facilitiesOptions));  
            } 
            else if (policyName == "nve") {
                SelectionPolicy* nav = new NaiveSelection();
                plans.push_back(Plan(planCounter,*sName,nav,facilitiesOptions));  
            }
            else {
                throw std::runtime_error("non existent selection policy");
            }
            
            planCounter++;
        }
                
    }
configFile.close();  // Close the file
std::cout << "Simulation constructed, this = " << this << std::endl;

}


// Rule of Five
Simulation::~Simulation() {
    //Delete all settlements objects
     for (Settlement* s : settlements) {
        delete s;
    }
    settlements.clear();

    // Delete all BaseAction objects
    for (BaseAction* a : actionsLog) {
        delete a;
    }
    actionsLog.clear();
}




Simulation::Simulation(const Simulation& other): isRunning(other.isRunning),                   
      planCounter(other.planCounter),               
      actionsLog(),                                                        
      settlements(),                                
      facilitiesOptions(other.facilitiesOptions.begin(), other.facilitiesOptions.end()) {  
    vector<Plan> plans;
    // Deep copy settlements
    for (const Settlement* s : other.settlements) {
        settlements.push_back(new Settlement(*s)); // Deep copy each settlement
    }

    // Deep copy plan, since it has resources.
    for (int i = 0;  static_cast<std::size_t>(i) <other.plans.size(); i++){
        plans.push_back(Plan(other.plans.at(i)));
    }

    // Deep copy actions
    for (const BaseAction* a : other.actionsLog) {
        actionsLog.push_back(a->clone()); // Clone each action
    }
}


Simulation& Simulation::operator=(const Simulation& other) {
        if (this!= &other) {
            // Clean the existing resources
            for (Settlement* s : settlements) {
                delete s;
            }
            settlements.clear();

            for (BaseAction* a : actionsLog) {
                delete a;
            }
            actionsLog.clear();

        isRunning= other.isRunning;
        planCounter= other.planCounter;
        vector<Plan> plans;
        for (int i = 0;  static_cast<std::size_t>(i) <other.plans.size(); i++){
            plans.push_back(Plan(other.plans.at(i)));
        }
        facilitiesOptions = std::vector<FacilityType>(other.facilitiesOptions.begin(), other.facilitiesOptions.end()) ;
        //deep dopy:
        for (const Settlement* s: other.settlements){
            settlements.push_back(new Settlement(*s));
        }
        for (const BaseAction* a : other.actionsLog){
            this->actionsLog.push_back(a->clone());
        }
   
    }
     return *this;

} 

Simulation::Simulation(Simulation&& other) noexcept : isRunning(other.isRunning),
      planCounter(other.planCounter),
      actionsLog(std::move(other.actionsLog)),
      settlements(std::move(other.settlements)),
      facilitiesOptions(std::move(other.facilitiesOptions)) {
    vector<Plan> plans;
    for (int i = 0;  static_cast<std::size_t>(i) <other.plans.size(); i++){
        plans.push_back(Plan(other.plans.at(i)));
    }
    // Leave the moved-from object in a valid state
    other.isRunning = false;
    other.planCounter = 0;

    // Clear moved-from object's pointers to prevent accidental deletions
    other.settlements.clear();
    other.actionsLog.clear();

}   

Simulation& Simulation::operator=(Simulation&& other) noexcept {
    if (this!= &other) {
        // Clean the existing resources
        for (Settlement* s : settlements) {
            delete s;
        }
        settlements.clear();

        for (BaseAction* a : actionsLog) {
            delete a;
        }
        actionsLog.clear();
    
        // Transfer ownership
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        settlements = other.settlements;
        actionsLog = other.actionsLog;
        vector<Plan> plans;
        for (int i = 0;  static_cast<std::size_t>(i) <other.plans.size(); i++){
            plans.push_back(Plan(other.plans.at(i)));
        }
        vector<FacilityType> facilitiesOptions;
        for (int i = 0;  static_cast<std::size_t>(i) <other.facilitiesOptions.size() ; i++){
             facilitiesOptions.push_back(other.facilitiesOptions.at(i));
        }
        facilitiesOptions = std::move(other.facilitiesOptions);
        for (int i = 0;  static_cast<std::size_t>(i) <other.actionsLog.size() ; i++){
            other.actionsLog.at(i) = nullptr;
        }


        // Clear other to leave it in a valid state
        other.isRunning = false;
        other.planCounter = 0;
    }
    return *this;
}

       

void Simulation::start(){
    open();
    cout << "The simulation has started";
    std::cout << "Simulation::start() called, this = " << this << std::endl;
    while (isRunning) {
        BaseAction *action;
        string command;
        getline(cin, command);
        vector<string> arguments = Auxiliary:: parseArguments(command);
                const string &requestedAction = arguments[0];
                // checking commands
                if(requestedAction == "step"){
                    action = new SimulateStep(std::stoi(arguments[1]));
                    action->act(*this);
                    addAction(action);
                }
                else if (requestedAction == "settlement"){
                const string& sName = arguments[1];
                static const SettlementType settlementTypesArray[] = {
                    SettlementType::VILLAGE, SettlementType::CITY, SettlementType::METROPOLIS
                };

                int sIndex = std::stoi(arguments[2]);
                int s = sizeof(settlementTypesArray) / sizeof(settlementTypesArray[0]);
                if (sIndex >= 0 && sIndex < s) {
                    action = new AddSettlement(sName, settlementTypesArray[sIndex]);
                } else {
                    throw std::runtime_error("Invalid settlement type");
    }
                }
                else if(requestedAction == "facility")
                {
                    string fName = arguments[1];
                    int categoryInt = std::stoi(arguments[2]);  // Convert string to integer
                    FacilityCategory category = static_cast<FacilityCategory>(categoryInt);
                    int price = std::stoi(arguments[3]);
                    int lifeQualityScore = std::stoi(arguments[4]);
                    int economyScore = std::stoi(arguments[5]);
                    int environmentScore = std::stoi(arguments[6]);
                    action = new AddFacility(fName, category, price, lifeQualityScore, economyScore,environmentScore);
                }
                else if(requestedAction == "plan"){                    
                    const string& sName = arguments[1];
                    const string& selectionPolicy = arguments[2];
                    action = new AddPlan(sName, selectionPolicy);                    
                }
                
                else if(requestedAction == "planstatus")
                {
                    action = new PrintPlanStatus(std::stoi(arguments[1]));
                }
                else if(requestedAction == "changeplanpolicy")
                {
                    ChangePlanPolicy* planPolicyChange = new ChangePlanPolicy(std::stoi(arguments[1]),arguments[2]);
                    action = planPolicyChange;
                }
                else if(requestedAction == "log")
                {
                    action = new PrintActionsLog();
                }
                else if(requestedAction == "close")
                {
                    action = new Close();
                }
                else if(requestedAction == "backup")
                {
                    action = new BackupSimulation();
                }
                else if(requestedAction == "restoresimulation")
                {
                    action = new RestoreSimulation();
                }
                action->act(*this);
                actionsLog.push_back(action);
            } 
        }


void Simulation::open()
{
    isRunning = true;
}


void Simulation::  addPlan(const Settlement &settlement, SelectionPolicy *selectionPolicy){
        int planID = planCounter;
        planCounter++;
        Plan p = Plan(planID, settlement, selectionPolicy, facilitiesOptions);
        plans.push_back(p);
 }

void Simulation:: addAction(BaseAction *action){
    actionsLog.push_back(action);
}



bool Simulation:: addSettlement(Settlement *settlement){
        for (const Settlement* s : settlements) {
            if (s->getName() == settlement->getName()) {
                return false;
                }
            }

        settlements.push_back(settlement);
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
        if (s ->getName()== settlementName){
            s->getName();
            return *s;
        }

    }
    // If no settlement is found with the given name, throw an exception or handle the error.
    throw std::runtime_error("No such settlement exists");
}

Plan &Simulation:: getPlan(const int planID) {
    for (Plan& p : plans){
        if (p.getID() == planID){ //NEED EO IMPLEMENT GETID METHOD
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

vector<BaseAction*> Simulation::getActionsLog(){return actionsLog;}
