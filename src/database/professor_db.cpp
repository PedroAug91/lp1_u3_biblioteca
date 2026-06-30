#include "../person/include/Professor.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool Professor::create(Person *p_person) {
  Professor *prof = dynamic_cast<Professor *>(p_person);
  if (!prof) return false;
  std::string path = "library_db/" + std::to_string(prof->matricula) + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << prof->name << "\n";
  file << "matricula=" << prof->matricula << "\n";
  file << "maxActiveLoans=" << prof->maxActiveLoans << "\n";
  file << "ActiveLoans=" << prof->ActiveLoans << "\n";
  file << "type=professor\n";
  return true;
}

bool Professor::read(std::string person_id) {
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

bool Professor::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "maxActiveLoans=" << this->maxActiveLoans << "\n";
  file << "ActiveLoans=" << this->ActiveLoans << "\n";
  file << "type=professor\n";
  return true;
}

bool Professor::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  return std::remove(path.c_str()) == 0;
}
