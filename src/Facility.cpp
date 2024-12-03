#include <iostream>
using namespace std;
#include "../include/Facility.h"
#include "../include/Plan.h"


        Facility::Facility(const string &name, const string &settlementName,
        const FacilityCategory category, const int price,
         const int lifeQuality_score, const int economy_score,
          const int environment_score)
          :FacilityType(name, category, price, lifeQuality_score, economy_score, environment_score), // Pass to base class constructor
          settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS) {
            timeLeft = price;
          };
          
         Facility::Facility(const FacilityType &type, const string &settlementName):
         FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price){}
        //  Facility(settlementName ,settlementName,type.getCategory(), type.getCost(), type.getLifeQualityScore(),
        //  type.getEconomyScore(), type.getEnvironmentScore()){};

        Facility* Facility::clone(){
            return new Facility(*this);
        }
        const string &Facility::getSettlementName() const{
            return settlementName;
        }
        const int Facility::getTimeLeft() const{
            return timeLeft;
        }
        FacilityStatus Facility::step(){
            if (timeLeft == 0){
                setStatus(FacilityStatus::OPERATIONAL);
                return FacilityStatus::OPERATIONAL;
                //Plan::addFacility(*this); TODO
            }
            else{
                timeLeft = timeLeft - 1;
                return FacilityStatus::UNDER_CONSTRUCTIONS;
            }
        }


        void Facility::setStatus(FacilityStatus status){
            this->status = status;
        }
        const FacilityStatus& Facility::getStatus() const{
            return status;
        }
        const string Facility::toString() const{
            string s = "Facility Name: " + getName() + "\n" +
            "Settlement Name: " + getSettlementName() + "\n";
            return s;

            //TODO check official tostring guide
        }

        const string settlementName;
        FacilityStatus status;
        int timeLeft;
