#include "../include/Facility.h"
#include <iostream>
using namespace std;


 Facility::Facility(const string &name, const string &settlementName,
        const FacilityCategory category, const int price,
         const int lifeQuality_score, const int economy_score,
          const int environment_score)
          :FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), // Pass to base class constructor
          settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS) {
            timeLeft = price;
          }
          
         Facility::Facility(const FacilityType &type, const string &settlementName):
         Facility(settlementName,settlementName,type.getCategory(), type.getCost(), type.getLifeQualityScore(),
         type.getEconomyScore(), type.getEnvironmentScore()){}


        const string &Facility::getSettlementName() const{
            return settlementName;
        }
        const int Facility::getTimeLeft() const{
            return timeLeft;
        }
        FacilityStatus Facility::step(){
            if (timeLeft =0 ){
                setStatus(FacilityStatus::OPERATIONAL);
                //Plan::addFacility(*this); TODO
            }
            else{
                timeLeft = timeLeft - 1;
            }

            
        }
        void Facility::setStatus(FacilityStatus status){
            this->status = status;
        }
        const FacilityStatus& Facility::getStatus() const{
            return status;
        }
        const string Facility::toString() const{
            cout << "Facility Name: " << getName() << "\n";
            cout << "Settlement Name: " << getSettlementName() << "\n";
        }

