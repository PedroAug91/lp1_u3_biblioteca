#include "../item/include/LoanableItem.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool LoanableItem::create(Person *) {
  std::string path = "library_db/" + std::to_string(this->id) + ".lnb";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  file << "displayArea=" << this->getDisplayArea() << "\n";
  file << "responsibleId=" << this->responsibleId << "\n";
  return true;
}

bool LoanableItem::read(std::string item_id) {
  std::string path = "library_db/" + item_id + ".lnb";
  std::ifstream file(path);
  if (!file.is_open()) return false;
  std::string line;
  while (std::getline(file, line)) {
    auto eq = line.find('=');
    if (eq == std::string::npos) continue;
    std::string key = line.substr(0, eq);
    std::string value = line.substr(eq + 1);
    if (key == "id") id = std::stoul(value);
    else if (key == "name") name = value;
    else if (key == "status") setStatus(static_cast<Status>(value[0]));
    else if (key == "displayArea") setDisplayArea(value);
    else if (key == "responsibleId") responsibleId = std::stoul(value);
  }
  return true;
}

bool LoanableItem::update(std::string item_id) {
  std::string path = "library_db/" + item_id + ".lnb";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  file << "displayArea=" << this->getDisplayArea() << "\n";
  file << "responsibleId=" << this->responsibleId << "\n";
  return true;
}

bool LoanableItem::remove(std::string item_id) {
  std::string path = "library_db/" + item_id + ".lnb";
  return std::remove(path.c_str()) == 0;
}
