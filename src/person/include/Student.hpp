#ifndef STUDENT_H
#define STUDENT_H

#include "AcademicMember.hpp"

class Student : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 3;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  // O que um estudante pode fazer que um professor não
  Student(std::string n, uint32_t m);
};

#endif
