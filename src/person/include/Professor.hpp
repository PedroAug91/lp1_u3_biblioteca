#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "AcademicMember.hpp"
#include <string>

class Professor : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 10;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void RequestRestrictedAccess();

  Professor(std::string n, uint32_t m);
};

#endif
