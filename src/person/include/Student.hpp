#ifndef STUDENT_H
#define STUDENT_H

#include "AcademicMember.hpp"

class Student : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 3;

  // O que um estudante pode fazer que um professor não
  Student(std::string n, std::string m);
};

#endif
