#ifndef LOANABLEITEM_H
#define LOANABLEITEM_H

#include "PublicItem.hpp"

class LoanableItem : public PublicItem {
public:
  std::string responsibleId;

  void accessItem() override;

  LoanableItem(std::string n, Status s, std::string i,
               std::string Da = "depósito01", std::string rid = "0");
};

#endif
