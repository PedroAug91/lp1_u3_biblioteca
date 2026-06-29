#include "include/Student.hpp"
#include <string>

#define MAX_ACTIVE_LOANS_STUDENT 3;


Student::Student(std::string n, std::string m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
