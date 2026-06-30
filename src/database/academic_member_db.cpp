#include "../person/include/AcademicMember.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool AcademicMember::create(Person *p_person) {
  AcademicMember *member = dynamic_cast<AcademicMember *>(p_person);
  if (!member) return false;
  std::string path = "library_db/" + std::to_string(member->matricula) + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << member->name << "\n";
  file << "matricula=" << member->matricula << "\n";
  file << "maxActiveLoans=" << member->maxActiveLoans << "\n";
  file << "ActiveLoans=" << member->ActiveLoans << "\n";
  return true;
}

bool AcademicMember::read(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Arquivo não encontrado: " << path << "\n";
    return false;
  }
  std::string line;
  while (std::getline(file, line))
    std::cout << line << "\n";
  return true;
}

bool AcademicMember::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "maxActiveLoans=" << this->maxActiveLoans << "\n";
  file << "ActiveLoans=" << this->ActiveLoans << "\n";
  return true;
}

bool AcademicMember::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}
