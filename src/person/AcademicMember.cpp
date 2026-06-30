#include "include/AcademicMember.hpp"

#include <ctime>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void AcademicMember::print() {
  std::cout << "Nome: " << name << '\n'
            << "Matrícula: " << matricula << '\n'
            << "Empréstimos ativos: " << ActiveLoans << '\n'
            << "Empréstimos restantes: " << (maxActiveLoans - ActiveLoans) << '\n';

  if (ActiveLoans > 0) {
    std::cout << "\n--- Itens emprestados ---\n";
    if (fs::exists("library_db")) {
      for (auto &entry : fs::directory_iterator("library_db")) {
        auto path = entry.path();
        if (path.extension() != ".lnb") continue;
        try {
          uint32_t lid = std::stoul(path.stem().string());
          LoanableItem li("", Status::AVAILABLE, lid);
          if (li.read(std::to_string(lid)) &&
              li.responsibleId == matricula && li.isBorrowed()) {
            int rem = li.daysRemaining();
            char buf[64];
            struct tm *tm_info = localtime(&li.dueDate);
            strftime(buf, sizeof(buf), "%d/%m/%Y", tm_info);
            std::cout << "  ID " << li.id << " - " << li.name
                      << " | Devolver até: " << buf;
            if (rem < 0)
              std::cout << " | ATRASADO (" << (-rem) << " dia(s))\n";
            else
              std::cout << " | " << rem << " dia(s) restante(s)\n";
          }
        } catch (...) {}
      }
    }
  }
}

void AcademicMember::searchItem() { std::cout << "procurando items\n\n"; }

AcademicMember::AcademicMember(std::string n, uint32_t m, int maxLoans,
                               int loans) {
  this->name = n;
  this->matricula = m;
  this->maxActiveLoans = maxLoans;
  this->ActiveLoans = loans;
}
