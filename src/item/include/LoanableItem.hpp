#ifndef LOANABLEITEM_H
#define LOANABLEITEM_H

#include "PublicItem.hpp"
#include <ctime>

class LoanableItem : public PublicItem {
public:
  uint32_t responsibleId;
  time_t borrowedAt;
  time_t dueDate;

  bool isBorrowed() const { return borrowedAt != 0; }
  int daysRemaining() const;

  void accessItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  LoanableItem(std::string n, Status s, uint32_t i,
               std::string Da = "depósito01", uint32_t rid = 0);
};

#endif
