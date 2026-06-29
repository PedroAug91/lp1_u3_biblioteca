#include "include/RestrictedItem.hpp"
#include "include/Status.hpp"
#include <iostream>

void RestrictedItem::setStatus(Status s) {
  std::cout << "O status de um RestrictedItem não pode ser alterado.\n";
}

void RestrictedItem::accessItem() {
  std::cout << this->name << "\n";
  std::cout << "Esse item não está disponível ao acesso do público, agende uma "
               "consulta particular\n";
}

void RestrictedItem::RestrictedAccess() { // algo para horários disponíveis e
                                          // selecionar um
                                          // bibliotecário como curador
  std::cout << "algum texto de informações restritas";
}

RestrictedItem::RestrictedItem(std::string n, std::string i)
    : Item(n, Status::UNAVAILABLE, i) {}
