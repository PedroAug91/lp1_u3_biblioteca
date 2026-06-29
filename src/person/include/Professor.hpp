#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "AcademicMember.hpp"
#include <string>

class Professor : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 10;

  void RequestRestrictedAccess();

  Professor(std::string n, std::string m);
};

#endif
