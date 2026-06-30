#ifndef ACADEMICMEMBER_H
#define ACADEMICMEMBER_H

#include "../../item/include/LoanableItem.hpp"
#include "Person.hpp"
#include <cstdint>
#include <string>

class AcademicMember : public Person {
public:
  std::string name;
  uint32_t matricula;
  int maxActiveLoans;
  int ActiveLoans;

  void searchItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  AcademicMember(std::string n, uint32_t m, int maxLoans, int loans);
};

#endif
