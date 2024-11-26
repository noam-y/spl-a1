#include "../include/Settlement.h"
#include <iostream>
using namespace std;


class Settlement {
  private:
    std::string name;
    SettlementType _settlementType;
  public:
    Settlement(const string &name, SettlementType type) :name(name),_settlementType(type){}
    const string &getName() const{
        return name;
    }
    SettlementType getType() const{
        return _settlementType;
    }
    const string toString() const{
        cout << "new settlement " + name << endl;
    };
};