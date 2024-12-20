#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions, int LifeScore, int EconomyScore, int EnviromentScore);
        Plan(const Plan &other);
        Plan(Plan&& other) noexcept; // move constructor
        Plan& operator=(const Plan &other)=delete;
        ~Plan();
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        const string getStatusString() const;
        const Settlement& getSettlement() const;
        const PlanStatus getStatus() const;
        const SelectionPolicy* getSelectionPolicy() const;
        vector<Facility*> getUnderConstruction();
        const int getID() const;
        const vector<FacilityType> getFacilityOptions() const;
    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
        int constructionLimit;
};