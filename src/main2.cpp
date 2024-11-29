#include <iostream>
#include <vector>
#include "Facility.h"
#include "SelectionPolicy.h"

using namespace std;

int main2() {
    try {
        // Step 1: Create some FacilityType objects
        vector<FacilityType> facilities = {
            FacilityType("Park", FacilityCategory::LIFE_QUALITY, 100, 90, 70, 80),
            FacilityType("Factory", FacilityCategory::ECONOMY, 300, 50, 90, 60),
            FacilityType("Farm", FacilityCategory::ECONOMY, 200, 60, 85, 70),
            FacilityType("Solar Plant", FacilityCategory::ENVIRONMENT, 400, 70, 60, 95)
        };

        // Step 2: Test NaiveSelection
        cout << "Testing NaiveSelection:" << endl;
        NaiveSelection naive;
        const FacilityType& naiveSelected = naive.selectFacility(facilities);
        cout << "Naive Selection result: " << naiveSelected.getName() << endl;
        cout << naive.toString() << endl;

        // Step 3: Test BalancedSelection
        cout << "\nTesting BalancedSelection:" << endl;
        BalancedSelection balanced(1, 1, 1); // Assign weights for balance
        const FacilityType& balancedSelected = balanced.selectFacility(facilities);
        cout << "Balanced Selection result: " << balancedSelected.getName() << endl;
        cout << balanced.toString() << endl;

        // Step 4: Test EconomySelection
        cout << "\nTesting EconomySelection:" << endl;
        EconomySelection economy;
        const FacilityType& economySelected = economy.selectFacility(facilities);
        cout << "Economy Selection result: " << economySelected.getName() << endl;
        cout << economy.toString() << endl;

        // Step 5: Test SustainabilitySelection
        cout << "\nTesting SustainabilitySelection:" << endl;
        SustainabilitySelection sustainability;
        const FacilityType& sustainabilitySelected = sustainability.selectFacility(facilities);
        cout << "Sustainability Selection result: " << sustainabilitySelected.getName() << endl;
        cout << sustainability.toString() << endl;

        // Step 6: Test clone functionality
        cout << "\nTesting clone functionality:" << endl;
        SelectionPolicy* clonedBalanced = balanced.clone();
        cout << "Cloned BalancedSelection toString(): " << clonedBalanced->toString() << endl;
        delete clonedBalanced;

    } catch (const std::out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}
