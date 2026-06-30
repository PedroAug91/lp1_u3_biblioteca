#include "include/Student.hpp"

#define MAX_ACTIVE_LOANS_STUDENT 3;

Student::Student(std::string n, uint32_t m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
