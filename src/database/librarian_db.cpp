#include "../person/include/Librarian.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool Librarian::create(Person *p_person) {
  Librarian *lib = dynamic_cast<Librarian *>(p_person);
  if (!lib) return false;
  std::string path = "library_db/" + std::to_string(lib->matricula) + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << lib->name << "\n";
  file << "matricula=" << lib->matricula << "\n";
  file << "maxActiveLoans=" << lib->maxActiveLoans << "\n";
  file << "ActiveLoans=" << lib->ActiveLoans << "\n";
  file << "type=librarian\n";
  return true;
}

bool Librarian::read(std::string person_id) {
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

bool Librarian::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "maxActiveLoans=" << this->maxActiveLoans << "\n";
  file << "ActiveLoans=" << this->ActiveLoans << "\n";
  file << "type=librarian\n";
  return true;
}

bool Librarian::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".usr";
  return std::remove(path.c_str()) == 0;
}
