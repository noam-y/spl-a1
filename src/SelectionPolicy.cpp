#include "../include/SelectionPolicy.h"
#include <iostream>
using namespace std;

NaiveSelection();
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        NaiveSelection *clone() const override;
        ~NaiveSelection() override = default;
   
        int lastSelectedIndex;