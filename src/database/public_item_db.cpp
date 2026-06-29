#include "../item/include/PublicItem.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool PublicItem::create(Person *p_person) {
  std::string path = "library_db/" + this->id + ".data";
  std::ofstream file(path);
  if (!file.is_open())
    return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  file << "displayArea=" << this->getDisplayArea() << "\n";
  return true;
}

bool PublicItem::read(std::string person_id) {
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

bool PublicItem::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ofstream file(path);
  if (!file.is_open())
    return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  file << "displayArea=" << this->getDisplayArea() << "\n";
  return true;
}

bool PublicItem::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}
