#include "include/ExhibitionItem.hpp"
#include <iostream>
#include <string>

void ExhibitionItem::setDisplayArea(std::string s) {
  std::cout << "Essa exposiçao não pode ser retirada de seu local:"
            << this->getDisplayArea();
}

void ExhibitionItem::print() {
  Item::print();
  std::cout << "Localização: " << getDisplayArea() << "\n";
}

void ExhibitionItem::accessItem() {
  std::cout << "DESCRIÇÃO DO ITEM: \n";
  std::cout << "nome: " << this->name << "\n";
  std::cout << "código de identificação: " << this->id << "\n";
  std::cout << "O item pode ser visto livremente em" << this->getDisplayArea()
            << "\n";
  std::cout
      << "ESTE ITEM É : informações sobre a exposiçãoinformações sobre a "
         "exposição\ninformações sobre a exposiçãotandard dummy text e\nver "
         "since 1informações sobre a exposiçãoet and James Mosley, t\nhe "
         "librarian ";
  std::cout << "\n\n";
}

ExhibitionItem::ExhibitionItem(std::string n, Status s, uint32_t i,
                               std::string Da)
    : PublicItem(n, s, i, Da) {}
