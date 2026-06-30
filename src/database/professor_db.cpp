#include "../person/include/Professor.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool Professor::create(Person *p_person) {
  Professor *prof = dynamic_cast<Professor *>(p_person);
  if (!prof) return false;
  std::string path = "library_db/" + std::to_string(prof->matricula) + ".data";
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

bool Professor::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
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
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}
