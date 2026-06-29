#include "include/PublicItem.hpp"
#include <iostream>
#include <string>

void PublicItem::setDisplayArea(std::string s) { this->displayArea = s; };
std::string PublicItem::getDisplayArea() const { return this->displayArea; };

void PublicItem::print() {
  Item::print();
  std::cout << "Localização: " << getDisplayArea() << "\n";
}

void PublicItem::accessItem() {
  std::cout << "DESCRIÇÃO DO ITEM: \n";
  std::cout << "nome: " << name << "\n";
  std::cout << "código de identificação: " << id << "\n";
  std::cout << "O item pode ser visto livremente em" << getDisplayArea()
            << "\n";
  std::cout
      << "ESTE ITEM É : Lorem Ipsum is simply dummy text of the printing "
         "and typesetting\name industry. Lorem Ipsum has been the "
         "industry's standard dummy text e\nver since 1966, when designers "
         "at Letraset and James Mosley, t\nhe librarian ";
  std::cout << "\n\n";
}

PublicItem::PublicItem(std::string n, Status s, std::string i, std::string da)
    : Item(n, s, i) {
  this->setDisplayArea(da);
}
