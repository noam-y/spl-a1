#include "../include/Simulation.h"

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

Simulation::Simulation(const std::string &configFilePath) : isRunning(false), planCounter(0) {
    std::ifstream configFile(configFilePath);
    initializeFile(configFilePath) //using helper function
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
            SettlementType sType = static_cast<SettlementType>(settlementTypeInt);  // Convert int to enum
            if (isSettlementExists(sName),sType){
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
            for (int i =0; i < facilitiesOptions.size(); i++){
                if (fName == facilitiesOptions[i].getName){
                    isExist = true;
                }
            }
            if (!isExist){
                <<cout "Facility already exist"<< endl;
            }
            facilitiesOptions.push_back(FacilityType(fName, fCategory, fPrice, lifeQualityScore, economyScore, environmentScore));
        }
        //Parsing plan
        else if (parsedArgs[0] == "plan") {
        SelectionPolicy* policy = nullptr;
            if (parsedArgs[2] == "bal") {
                policy = new BalancedSelection(0,0,0);  
            } 
            else if (parsedArgs[2]== "env") {
                policy = new SustainabilitySelection ();
            }
            else if (parsedArgs[2] == "eco") {
                policy = new EconomySelection();  
            } 
            else {
                    policy = new NaiveSelection();  
            }
            Settlement* sName = nullptr;
            for (auto& s : settlements) {
                if (s->getName() == parsedArgs[1]) { 
                    sName = s;
                    break;
                }
            }
            plans.push_back(Plan(planCounter, *sName, policy, facilitiesOptions));
            planCounter++;
        }
                
    }
configFile.close();  // Close the file
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


void Simulation::start(){
    open();
    cout << "The simulation has started";
    while (isRunning) {
        BaseAction *action;
        string command;
        getline(cin, command);
        vector<string> arguments = Auxiliary:: parseArguments(command);
                const string &requestedAction = arguments[0];
                // checking commands
                if(requestedAction == "plan"){                    
                    const string& settlementName = arguments[1];
                    const string& selectionPolicy = arguments[2];
                    action = new AddPlan(settlementName, selectionPolicy);                    
                }
                else if(requestedAction == "step"){
                    action = new SimulateStep(std::stoi(arguments[1]));
                }
                else if(requestedAction == "settlement")
                {
                    const string& settlementName = arguments[1];
                    switch (std:: stoi(arguments[2])){
                        case 0: action = new AddSettlement(settlementName, SettlementType::VILLAGE );
                            break;
                        case 1: action = new AddSettlement(settlementName, SettlementType::CITY );
                            break;
                        case 2: action = new AddSettlement(settlementName, SettlementType::METROPOLIS );
                            break;
                        default: throw std::runtime_error("Settlement not found");
                    }                    
                }
                else if(requestedAction == "facility")
                {
                    string facilityName = arguments[1];
                    int categoryInt = std::stoi(arguments[2]);  // Convert string to integer
                    FacilityCategory category = static_cast<FacilityCategory>(categoryInt);
                    int price = std::stoi(arguments[3]);
                    int lifeQualityScore = std::stoi(arguments[4]);
                    int economyScore = std::stoi(arguments[5]);
                    int environmentScore = std::stoi(arguments[6]);
                    action = new AddFacility(facilityName, category, price, lifeQualityScore, economyScore,environmentScore);
                }
                else if(requestedAction == "planstatus")
                {
                    action = new PrintPlanStatus(std::stoi(arguments[1]));
                }
                else if(requestedAction == "changeplanpolicy")
                {
                    ChangePlanPolicy* change = new ChangePlanPolicy(std::stoi(arguments[1]),arguments[2]);
                    action = change;
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
