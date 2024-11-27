#include "../include/Settlement.h"
#include <iostream>
using namespace std;




Settlement::Settlement(const string &otherName, SettlementType otherType): name(otherName), type(type) {}
//copy constractor
Settlement::Settlement(const Settlement &other)  : name(other.name), type(other.type){}
// destructor
Settlement::  ~Settlement(){} // defult destructor
// copy assigment
 Settlement& Settlement::operator = (const Settlement& other){
  if (this!= &other)
      type = other.type;
  return *this;
 }

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

