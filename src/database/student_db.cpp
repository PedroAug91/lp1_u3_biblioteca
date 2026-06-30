#include "../person/include/Student.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool Student::create(Person *p_person) {
  Student *stud = dynamic_cast<Student *>(p_person);
  if (!stud) return false;
  std::string path = "library_db/" + std::to_string(stud->matricula) + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << stud->name << "\n";
  file << "matricula=" << stud->matricula << "\n";
  file << "maxActiveLoans=" << stud->maxActiveLoans << "\n";
  file << "ActiveLoans=" << stud->ActiveLoans << "\n";
  file << "type=student\n";
  return true;
}

bool Student::read(std::string person_id) {
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

bool Student::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "maxActiveLoans=" << this->maxActiveLoans << "\n";
  file << "ActiveLoans=" << this->ActiveLoans << "\n";
  file << "type=student\n";
  return true;
}

bool Student::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}
