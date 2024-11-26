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
          
        Facility(const FacilityType &type, const string &settlementName); // TODO

        const string &getSettlementName() const{
            return settlementName;
        }
        const int getTimeLeft() const{
            return timeLeft;
        }
        FacilityStatus step(){
            if (timeLeft > 1){
                setStatus(FacilityStatus::OPERATIONAL);
            }
            else{
                timeLeft = timeLeft - 1;
            }

            // TODO  ADD TO FACILITY LIST
        }
        void setStatus(FacilityStatus status){
            this->status = status;
        }
        const FacilityStatus& getStatus() const{
            return status;
        }
        const string toString() const{
            cout << "Facility Name: " << getName() << "\n";
            cout << "Settlement Name: " << getSettlementName() << "\n";
        }

    private:
        const string settlementName;
        FacilityStatus status;
        int timeLeft;
};