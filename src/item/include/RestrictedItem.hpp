#ifndef RESTRICTEDITEM_H
#define RESTRICTEDITEM_H
#include "Item.hpp"

class RestrictedItem final
    : public Item { // final para evitar que uma classe filha mude os métodos
                    // que restringem o acesso
public:
  void setStatus(Status s) override;

  void accessItem() override;

  void RestrictedAccess();

  RestrictedItem(std::string n, std::string i);
};

#endif
