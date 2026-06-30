#include "../item/include/RestrictedItem.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool RestrictedItem::create(Person *p_person) {
  std::string path = "library_db/" + std::to_string(this->id) + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  return true;
}

bool RestrictedItem::read(std::string person_id) {
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

bool RestrictedItem::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  return true;
}

bool RestrictedItem::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}
