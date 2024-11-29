#include "../include/SelectionPolicy.h"
#include <iostream>
using namespace std;

//naive selection.cpp
NaiveSelection:: NaiveSelection() : lastSelectedIndex(-1) {}
NaiveSelection:: NaiveSelection (const NaiveSelection& other) : lastSelectedIndex(other.lastSelectedIndex) {}

const FacilityType& NaiveSelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()){
        throw std:: out_of_range ("No facility invalid for selection");
    }
     lastSelectedIndex++; 
     // Make it cyclic
    if (lastSelectedIndex >= facilitiesOptions.size()) {
        lastSelectedIndex = 0;  // Loop back to the first element
    }
    facilitiesList.push_back(facilitiesOptions[lastSelectedIndex]);
     return facilitiesOptions[lastSelectedIndex]; 
}


const string NaiveSelection:: toString() const {
    string s = "";
    //adding every name of the chosen facilities in the list
    for (int i= 0; i<facilitiesList.size(); i++ ) {
        s= s+ "," + facilitiesList[i].getName(); 

    }
    return s;
 }


NaiveSelection *NaiveSelection:: clone() const {
     return new NaiveSelection(*this);  // Create a new NaiveSelection that is a copy of the current one
}


NaiveSelection:: ~NaiveSelection() {} // defult destructor




// balanced selection:
BalancedSelection:: BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore),  EnvironmentScore( EnvironmentScore){}
BalancedSelection::BalancedSelection(const BalancedSelection& other) : LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore){}

int BalancedSelection::balanceDiff(int LifeQualityScore, int EconomyScore, int EnvironmentScore){
    int d1 = abs (LifeQualityScore- EconomyScore);
    int d2 = std::abs (EconomyScore- EnvironmentScore);
    int d3 = std::abs (LifeQualityScore- EnvironmentScore);
    return d1+d2+d3;
}

const FacilityType& BalancedSelection:: selectFacility(const vector<FacilityType>& facilitiesOptions)  {
    const FacilityType* bestFa = nullptr;
    int totalDifff=INT32_MAX; // max difference possible
    for (const FacilityType& facility : facilitiesOptions){
        int curr = balanceDiff(facility.getLifeQualityScore(), facility.getEconomyScore(), facility.getEnvironmentScore());
        if (curr < totalDifff){
           bestFa = &facility;
        }
    }
    return *bestFa;



const string BalancedSelection::toString() const {
    return "last selected index is: " + std::to_string(lastSelectedIndex);
}


BalancedSelection BalancedSelection:: *clone() const  {
    return new BalancedSelection(LifeQualityScore, EconomyScore, EnvironmentScore);  // Create a new NaiveSelection that is a copy of the current one
}


BalancedSelection:: ~BalancedSelection() {} // defule destructor




//EconomySelection
//constacturs:
EconomySelection:: EconomySelection(): lastSelectedIndex(-1) {}
EconomySelection::EconomySelection(const EconomySelection& other):lastSelectedIndex(other.lastSelectedIndex){}
//copy assigmnet
//EconomySelection& EconomySelection::operator=(const EconomySelection& other){
  //  if(this != &other){
    //    lastSelectedIndex = other.lastSelectedIndex;
    //}

    //return *this;
//}


const FacilityType& EconomySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()){
        throw std:: out_of_range ("No facility invalid for selection");
    }
    
     vector<int> indexesList;
     lastSelectedIndex++; 
     int curr = 0;
     for (const FacilityType& facility : facilitiesOptions){
        if (facility.getCategory()== FacilityCategory::ECONOMY){
            indexesList.push_back(curr);
        }
        curr ++;
     }
     if (indexesList.empty()) {
        throw std::out_of_range("No ECONOMY facilities for selection");
    }

    // Update the lastSelectedIndex to the next valid index in a circular manner
    lastSelectedIndex = (lastSelectedIndex + 1) % indexesList.size();

    // Return the facility at the selected index
    return facilitiesOptions.at(indexesList[lastSelectedIndex]);
    

} 

const string EconomySelection::toString() const {
    return "last selected index is: " + std::to_string(lastSelectedIndex);
}


EconomySelection *EconomySelection::clone() const {
    return new EconomySelection(*this);
}


EconomySelection:: ~EconomySelection(){}



// SustainabilitySelection
//constructors  
SustainabilitySelection:: SustainabilitySelection(): lastSelectedIndex(-1){}
SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection& other):lastSelectedIndex(other.lastSelectedIndex){}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
    if (facilitiesOptions.empty()){
        throw std:: out_of_range ("No facility invalid for selection");
    }
    
     vector<int> indexesList;
     lastSelectedIndex++; 
     int curr = 0;
     for (const FacilityType& facility : facilitiesOptions){
        if (facility.getCategory()== FacilityCategory::ENVIRONMENT){
            indexesList.push_back(curr);
        }
        curr ++;
     }
     if (indexesList.empty()) {
        throw std::out_of_range("No ENVIRONMENT facilities for selection");
    }

    // Update the lastSelectedIndex to the next valid index in a circular manner
    lastSelectedIndex = (lastSelectedIndex + 1) % indexesList.size();

    // Return the facility at the selected index
    return facilitiesOptions.at(indexesList[lastSelectedIndex]);
    


}

const string SustainabilitySelection::toString() const {
    return  "last selected index is" + to_string(lastSelectedIndex);
}

SustainabilitySelection *SustainabilitySelection::clone() const {
    return new SustainabilitySelection(*this);
}

SustainabilitySelection:: ~SustainabilitySelection() {}




