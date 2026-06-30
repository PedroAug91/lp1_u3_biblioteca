#ifndef RESTRICTEDITEM_H
#define RESTRICTEDITEM_H
#include "Item.hpp"

class RestrictedItem final
    : public Item { // final para evitar que uma classe filha mude os métodos
                    // que restringem o acesso
public:
  void setStatus(Status s) override;

  void accessItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void RestrictedAccess();

  RestrictedItem(std::string n, uint32_t i);
};

#endif
