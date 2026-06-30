#include "include/LoanableItem.hpp"
#include <iostream>

void LoanableItem::print() {
  PublicItem::print();
  std::cout << "Responsável: " << responsibleId << "\n";
}

void LoanableItem::accessItem() {
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

LoanableItem::LoanableItem(std::string n, Status s, uint32_t i,
                           std::string da, uint32_t rid)
    : PublicItem(n, s, i, da) {
  responsibleId = rid;
}
