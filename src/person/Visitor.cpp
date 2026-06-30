#include "include/Visitor.hpp"
#include <iostream>

void Visitor::searchItem() {
  std::cout << "Procurando itens disponíveis na biblioteca...\n\n";
}

void Visitor::print() {
  std::cout << "Visitante: " << name << "\n";
}

bool Visitor::create(Person *) { return false; }
bool Visitor::read(std::string) { return false; }
bool Visitor::update(std::string) { return false; }
bool Visitor::remove(std::string) { return false; }

Visitor::Visitor(std::string n) : name(std::move(n)) {}
