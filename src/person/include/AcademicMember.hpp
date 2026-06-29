#ifndef ACADEMICMEMBER_H
#define ACADEMICMEMBER_H

#include "../../item/include/LoanableItem.hpp"
#include "Person.hpp"
#include <string>
#include <vector>

class AcademicMember : public Person { // classe abstrata
public:
  std::string name;
  std::string matricula;
  int maxActiveLoans;
  int ActiveLoans;

  void searchItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void BorrowItem(std::vector<LoanableItem> &loanableList, std::string itemId);

  void ReturnItem(std::vector<LoanableItem> &loanableList, std::string itemId);

  AcademicMember(std::string n, std::string m, int maxLoans, int loans);
};

#endif
