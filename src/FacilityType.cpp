#include <iostream>
using namespace std;
#include "../include/Facility.h"



class FacilityType {
  protected:
    enum FacilityCategory{
        LifeQuality,
        Economy,
        Sustainability
    };
      const string name;
      const FacilityCategory category;
      const int price;
      const int lifeQuality_score;
      const int economy_score;
      const int environment_score;

  public:
      FacilityType(const string &name, const FacilityCategory category, const int price, const int lifeQuality_score, const int economy_score, const int environment_score)
      :name(name), category(category), price(price), lifeQuality_score(lifeQuality_score), economy_score(economy_score), environment_score(environment_score){};
      const string &getName() const;
      int getCost() const{
        return price;
      }
      int getLifeQualityScore() const{
        return lifeQuality_score;
      }
      int getEnvironmentScore() const{
        return environment_score;
      }
      int getEconomyScore() const{
        return economy_score;
      }
      FacilityCategory getCategory() const{
        return category;
      }

};