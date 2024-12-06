#include "../include/Facility.h"
#include "../include/SelectionPolicy.h"
#include <algorithm>
#include <iostream>
using namespace std;

// naive selection.cpp
NaiveSelection::NaiveSelection() : lastSelectedIndex(-1) {}
NaiveSelection::NaiveSelection(const NaiveSelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}

// Destructor - use default

const FacilityType &NaiveSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    if (facilitiesOptions.empty())
    {
        throw std::out_of_range("No facility invalid for selection");
    }
    lastSelectedIndex++;
    // Make it cyclic
    if (lastSelectedIndex >= (int)facilitiesOptions.size())
    {
        lastSelectedIndex = 0; // Loop back to the first element
    }
    facilitiesList.push_back(facilitiesOptions[lastSelectedIndex]);
    return facilitiesOptions[lastSelectedIndex];
}

const string NaiveSelection::toString() const
{
    return "nve";
}

NaiveSelection *NaiveSelection::clone() const
{
    return new NaiveSelection(*this); // Create a new NaiveSelection that is a copy of the current one
}

// balanced selection:
BalancedSelection::BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore) : LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore) {}
BalancedSelection::BalancedSelection(const BalancedSelection &other) : LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore) {}

// Destructor - use default

int BalancedSelection::balanceDiff(int LifeQualityScore, int EconomyScore, int EnvironmentScore)
{
    int d1 = abs(LifeQualityScore - EconomyScore);
    int d2 = std::abs(EconomyScore - EnvironmentScore);
    int d3 = std::abs(LifeQualityScore - EnvironmentScore);
    return std::max({d1, d2, d3});
}

const FacilityType &BalancedSelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    int bestIndex = 0;
    int totalDifff = INT32_MAX; // max difference possible
    int currIndex=0;
    for (FacilityType facility : facilitiesOptions)
    {
        int curr = balanceDiff(LifeQualityScore + facility.getLifeQualityScore(),
        EconomyScore + facility.getEconomyScore(),
        EnvironmentScore + facility.getEnvironmentScore());
        if (curr < totalDifff)
        {
           totalDifff=curr;
           bestIndex=currIndex;
        }
        currIndex ++;
    }
    LifeQualityScore = LifeQualityScore + facilitiesOptions.at(bestIndex).getLifeQualityScore();
    EconomyScore = EconomyScore + facilitiesOptions.at(bestIndex).getEconomyScore();
    EnvironmentScore = EnvironmentScore + facilitiesOptions.at(bestIndex).getEnvironmentScore();
    const FacilityType& BestFacility = facilitiesOptions.at(bestIndex);
    return BestFacility;
}

// Implement with  3 scores
const string BalancedSelection::toString() const {
    return "bal";
}

BalancedSelection *BalancedSelection::clone() const
{
    return new BalancedSelection(LifeQualityScore, EconomyScore, EnvironmentScore); // Create a new NaiveSelection that is a copy of the current one
}

// EconomySelection
// constacturs:
EconomySelection::EconomySelection() : lastSelectedIndex(-1) {}
EconomySelection::EconomySelection(const EconomySelection &other) : lastSelectedIndex(other.lastSelectedIndex) {}

// Destructor - use default

const FacilityType &EconomySelection::selectFacility(const vector<FacilityType> &facilitiesOptions)
{
    bool facilityFound = false;
    while (!facilityFound){
        lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
        facilityFound = facilitiesOptions[lastSelectedIndex].getCategory() == FacilityCategory::ECONOMY;
    }
    return facilitiesOptions[lastSelectedIndex];
}

const string EconomySelection::toString() const
{
    return "eco";
}

EconomySelection *EconomySelection::clone() const
{
    return new EconomySelection(*this);
}

// SustainabilitySelection
// constructors
 SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection& other):lastSelectedIndex(other.lastSelectedIndex){}
 SustainabilitySelection:: SustainabilitySelection(): lastSelectedIndex(-1){}

// Destructor - use default

 const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions) {
     if (facilitiesOptions.empty()){
         throw std:: out_of_range ("No facility invalid for selection");
     }

      vector<int> indexesList;
      lastSelectedIndex++;
      int curr = 0;
      for (const FacilityType& facility : facilitiesOptions){
         if (facility.getCategory()== FacilityCategory::ENVIRONMENT){
             indexesList.push_back(curr);         }
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
     return  "env";
 }

 SustainabilitySelection *SustainabilitySelection::clone() const {
     return new SustainabilitySelection(*this);
 }

