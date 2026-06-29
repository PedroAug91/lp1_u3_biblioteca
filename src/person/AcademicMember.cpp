#include "include/AcademicMember.hpp"

#include <iostream>
#include <string>

void AcademicMember::print() {
  std::cout << "Nome: " << name << '\n'
            << "Matrícula: " << matricula << '\n'
            << "Empréstimos ativos: " << ActiveLoans << '\n'
            << "Empréstimos restantes: " << (maxActiveLoans - ActiveLoans) << '\n';
}

void AcademicMember::searchItem() { std::cout << "procurando items\n\n"; }

void AcademicMember::BorrowItem(std::vector<LoanableItem> &loanableList,
                                std::string itemId) {

  for (int i = 0; i < loanableList.size(); i++) {

    if (loanableList[i].id == itemId) {

      if (loanableList[i].getStatus() == Status::AVAILABLE) {
        if (ActiveLoans < maxActiveLoans) {
          loanableList[i].setStatus(Status::BORROWED);
          loanableList[i].responsibleId = matricula;
          loanableList[i].setDisplayArea("não está na biblioteca");
          ActiveLoans++;
          std::cout << "Item " << loanableList[i].name << " emprestado para "
                    << name << "que tem " << ActiveLoans
                    << " empréstimo(s) ativos" << std::endl;

        } else {
          std::cout << "usuário atingiu quantidade máxima de empréstimos: "
                    << ActiveLoans << "\n\n";
        }
      } else {

        std::cout << "Item indisponível." << std::endl;
      }

      return;
    }
  }

  std::cout << "Item não encontrado." << std::endl;
}

void AcademicMember::ReturnItem(std::vector<LoanableItem> &loanableList,
                                std::string itemId) {

  for (int c = 0; c < loanableList.size(); c++) {

    if (loanableList[c].id == itemId) {

      if (loanableList[c].getStatus() == Status::BORROWED) {

        if (loanableList[c].responsibleId == matricula) {

          loanableList[c].responsibleId = "0";
          loanableList[c].setStatus(Status::AVAILABLE);
          loanableList[c].setDisplayArea("depósito de devoluções");
          ActiveLoans--;
          std::cout << "Item " << loanableList[c].name << " ("
                    << loanableList[c].id << ") devolvido por " << name
                    << " que tem " << ActiveLoans << " empréstimo(s) ativos"
                    << std::endl;

        } else {

          std::cout << "Esse usuário não pegou esse item emprestado.\n\n";
        }

      } else {

        std::cout << "O item não está emprestado.\n\n";
      }

      return;
    }
  }

  std::cout << "Item não encontrado.\n\n";
}

AcademicMember::AcademicMember(std::string n, std::string m, int maxLoans,
                               int loans) {
  this->name = n;
  this->matricula = m;
  this->maxActiveLoans = maxLoans;
  this->ActiveLoans = loans;
}
