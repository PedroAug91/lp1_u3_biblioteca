#ifndef LOANABLEITEM_H
#define LOANABLEITEM_H

#include "PublicItem.hpp"

class LoanableItem : public PublicItem {
public:
  std::string responsibleId;

  void accessItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  LoanableItem(std::string n, Status s, std::string i,
               std::string Da = "depósito01", std::string rid = "0");
};

#endif
