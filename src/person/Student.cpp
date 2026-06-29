#include "include/Student.hpp"
#include <string>

Student::Student(std::string n, std::string m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
