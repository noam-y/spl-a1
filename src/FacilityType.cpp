#include <iostream>
using namespace std;
#include "../include/Facility.h"



class FacilityType {
  private:
    std::string name;
    int price;
    enum FacilityCategory{
        LifeQuality,
        Economy,
        Sustainability
    };
  public:
    //T functionName(T arg);
    //... .. ...
};