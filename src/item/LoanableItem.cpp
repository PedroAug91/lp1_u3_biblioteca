#include "include/LoanableItem.hpp"
#include <iomanip>
#include <iostream>

int LoanableItem::daysRemaining() const {
  if (borrowedAt == 0) return 0;
  return static_cast<int>(difftime(dueDate, time(nullptr)) / (24 * 60 * 60));
}

void LoanableItem::print() {
  PublicItem::print();
  std::cout << "Responsável: " << responsibleId << "\n";
  if (isBorrowed()) {
    char buf[64];
    struct tm *tm_info = localtime(&dueDate);
    strftime(buf, sizeof(buf), "%d/%m/%Y", tm_info);
    std::cout << "Devolver até: " << buf << "\n";
    int rem = daysRemaining();
    if (rem < 0)
      std::cout << "Status: ATRASADO (" << (-rem) << " dia(s))\n";
    else
      std::cout << "Status: " << rem << " dia(s) restante(s)\n";
  }
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
    : PublicItem(n, s, i, da), borrowedAt(0), dueDate(0) {
  responsibleId = rid;
}
