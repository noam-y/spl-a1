#include <iostream>
using namespace std;
#include "../include/Facility.h"



class Facility: public FacilityType{
    public:
        Facility(const string &name, const string &settlementName,
        const FacilityCategory category, const int price,
         const int lifeQuality_score, const int economy_score,
          const int environment_score)
          :FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), // Pass to base class constructor
          settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS) {};
          
          
        Facility(const FacilityType &type, const string &settlementName);
        const string &getSettlementName() const;
        const int getTimeLeft() const;
        FacilityStatus step();
        void setStatus(FacilityStatus status);
        const FacilityStatus& getStatus() const;
        const string toString() const;

    private:
        const string settlementName;
        FacilityStatus status;
        int timeLeft;
};