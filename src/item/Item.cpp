#include "include/Item.hpp"
#include <string>

Status Item::getStatus() const { return this->status; }

void Item::setStatus(Status s) { status = s; }

Item::Item(std::string n, Status s, std::string i) {
  this->name = n;
  this->id = i;
  this->setStatus(s);
}

Item::~Item() {};
