#include "../person/include/AcademicMember.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool AcademicMember::create(Person *p_person) {
  AcademicMember *member = dynamic_cast<AcademicMember *>(p_person);
  if (!member) return false;
  std::string path = "library_db/" + std::to_string(member->matricula) + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << member->name << "\n";
  file << "matricula=" << member->matricula << "\n";
  file << "maxActiveLoans=" << member->maxActiveLoans << "\n";
  file << "ActiveLoans=" << member->ActiveLoans << "\n";
  return true;
}

bool AcademicMember::read(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  std::ifstream file(path);
  if (!file.is_open()) return false;
  std::string line;
  while (std::getline(file, line)) {
    auto eq = line.find('=');
    if (eq == std::string::npos) continue;
    std::string key = line.substr(0, eq);
    std::string value = line.substr(eq + 1);
    if (key == "name") name = value;
    else if (key == "matricula") matricula = std::stoul(value);
    else if (key == "maxActiveLoans") maxActiveLoans = std::stoi(value);
    else if (key == "ActiveLoans") ActiveLoans = std::stoi(value);
  }
  return true;
}

bool AcademicMember::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "maxActiveLoans=" << this->maxActiveLoans << "\n";
  file << "ActiveLoans=" << this->ActiveLoans << "\n";
  return true;
}

bool AcademicMember::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  return std::remove(path.c_str()) == 0;
}
