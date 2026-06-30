#include "include/Item.hpp"
#include <iostream>
#include <string>

Status Item::getStatus() const { return this->status; }

void Item::setStatus(Status s) { status = s; }

void Item::print() {
  std::cout << "ID: " << id << "\n";
  std::cout << "Nome: " << name << "\n";
  std::cout << "Status: " << static_cast<char>(getStatus()) << "\n";
}

Item::Item(std::string n, Status s, uint32_t i) {
  this->name = n;
  this->id = i;
  this->setStatus(s);
}

Item::~Item() {};
