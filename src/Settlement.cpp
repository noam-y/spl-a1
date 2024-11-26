#include "../include/Settlement.h"
#include <iostream>
using namespace std;


class Settlement {
  private:
    std::string name;
    SettlementType settlementType;
    enum SettlementType {
        Village,
        City,
        Metropolice
    };
  public:
    Settlement(const string &name, SettlementType type); //name(name),settlementType((SettlementType)type){}
    const string &getName() const;
    SettlementType getType() const;
    const string toString() const;
};