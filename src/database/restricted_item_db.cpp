#include "../item/include/RestrictedItem.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

bool RestrictedItem::create(Person *) {
  std::string path = "library_db/" + std::to_string(this->id) + ".rst";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  return true;
}

bool RestrictedItem::read(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
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
  }
  return true;
}

bool RestrictedItem::update(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "id=" << this->id << "\n";
  file << "name=" << this->name << "\n";
  file << "status=" << static_cast<char>(this->getStatus()) << "\n";
  return true;
}

bool RestrictedItem::remove(std::string item_id) {
  std::string path = "library_db/" + item_id + ".rst";
  return std::remove(path.c_str()) == 0;
}
