#include "../include/Settlement.h"
#include <iostream>
using namespace std;




Settlement::Settlement(const string &name, SettlementType type)
    : name(name), type(type) {}

const string& Settlement::getName() const{return name;}

SettlementType Settlement::getType() const{return type;}

const string Settlement::toString() const{
  string val;
  switch (type)
  {
  case SettlementType::CITY:
    val = "City";
    break;
  case SettlementType::VILLAGE:
    val = "Village";
    break;
  case SettlementType::METROPOLIS:
    val = "Metropolis";
    break;
    default:
            throw std::invalid_argument("Unknown SettlementType encountered in toString");
  }

  return "Settlement Name:" + name + " Type: " + val;
}


