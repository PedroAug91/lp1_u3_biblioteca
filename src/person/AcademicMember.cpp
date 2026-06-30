#include "include/AcademicMember.hpp"

#include <iostream>

void AcademicMember::print() {
  std::cout << "Nome: " << name << '\n'
            << "Matrícula: " << matricula << '\n'
            << "Empréstimos ativos: " << ActiveLoans << '\n'
            << "Empréstimos restantes: " << (maxActiveLoans - ActiveLoans) << '\n';
}

void AcademicMember::searchItem() { std::cout << "procurando items\n\n"; }

void AcademicMember::BorrowItem(uint32_t itemId) {
  LoanableItem item("", Status::AVAILABLE, itemId);
  if (!item.read(std::to_string(itemId))) {
    std::cout << "Item não encontrado.\n";
    return;
  }

  if (item.getStatus() == Status::AVAILABLE) {
    if (ActiveLoans < maxActiveLoans) {
      item.setStatus(Status::BORROWED);
      item.responsibleId = matricula;
      item.setDisplayArea("não está na biblioteca");
      ActiveLoans++;
      item.update(std::to_string(itemId));
      this->update(std::to_string(this->matricula));
      std::cout << "Item " << item.name << " emprestado para " << name
                << " que tem " << ActiveLoans
                << " empréstimo(s) ativos" << std::endl;
    } else {
      std::cout << "usuário atingiu quantidade máxima de empréstimos: "
                << ActiveLoans << "\n\n";
    }
  } else {
    std::cout << "Item indisponível." << std::endl;
  }
}

void AcademicMember::ReturnItem(uint32_t itemId) {
  LoanableItem item("", Status::AVAILABLE, itemId);
  if (!item.read(std::to_string(itemId))) {
    std::cout << "Item não encontrado.\n\n";
    return;
  }

  if (item.getStatus() == Status::BORROWED) {
    if (item.responsibleId == matricula) {
      item.responsibleId = 0;
      item.setStatus(Status::AVAILABLE);
      item.setDisplayArea("depósito de devoluções");
      ActiveLoans--;
      item.update(std::to_string(itemId));
      this->update(std::to_string(this->matricula));
      std::cout << "Item " << item.name << " (" << item.id
                << ") devolvido por " << name
                << " que tem " << ActiveLoans << " empréstimo(s) ativos"
                << std::endl;
    } else {
      std::cout << "Esse usuário não pegou esse item emprestado.\n\n";
    }
  } else {
    std::cout << "O item não está emprestado.\n\n";
  }
}

AcademicMember::AcademicMember(std::string n, uint32_t m, int maxLoans,
                               int loans) {
  this->name = n;
  this->matricula = m;
  this->maxActiveLoans = maxLoans;
  this->ActiveLoans = loans;
}
