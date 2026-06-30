#include "include/Librarian.hpp"
#include "include/Professor.hpp"
#include "include/Student.hpp"
#include "../item/include/ExhibitionItem.hpp"
#include "../item/include/LoanableItem.hpp"
#include "../item/include/RestrictedItem.hpp"
#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void Librarian::print() {
  std::cout << "--- Bibliotecário ---\n";
  std::cout << "Nome: " << name << '\n' << "Matrícula: " << matricula << '\n';
}

static uint32_t getNextUserId() {
  uint32_t maxId = 0;
  if (!fs::exists("library_db")) return 1;
  for (auto &entry : fs::directory_iterator("library_db")) {
    auto path = entry.path();
    if (path.extension() == ".usr") {
      try {
        uint32_t id = std::stoul(path.stem().string());
        if (id > maxId) maxId = id;
      } catch (...) {}
    }
  }
  return maxId + 1;
}

static uint32_t getNextItemId(const std::string &ext) {
  uint32_t maxId = 0;
  if (!fs::exists("library_db")) return 1;
  for (auto &entry : fs::directory_iterator("library_db")) {
    auto path = entry.path();
    if (path.extension() == ext) {
      try {
        uint32_t id = std::stoul(path.stem().string());
        if (id > maxId) maxId = id;
      } catch (...) {}
    }
  }
  return maxId + 1;
}

void Librarian::registerUser(const std::string &type,
                              const std::string &name) {
  uint32_t newMat = getNextUserId();

  if (type == "student") {
    Student s(name, newMat);
    s.create(&s);
    std::cout << "Estudante " << name << " registrado com matrícula " << newMat << "\n";
  } else if (type == "professor") {
    Professor p(name, newMat);
    p.create(&p);
    std::cout << "Professor " << name << " registrado com matrícula " << newMat << "\n";
  } else {
    std::cout << "Tipo de usuário desconhecido: " << type << "\n";
  }
}

void Librarian::registerLoanableItem(const std::string &name) {
  uint32_t newId = getNextItemId(".lnb");
  LoanableItem item(name, Status::AVAILABLE, newId);
  item.create(nullptr);
  std::cout << "Item emprestável " << name << " registrado com ID " << newId << "\n";
}

void Librarian::registerRestrictedItem(const std::string &name) {
  uint32_t newId = getNextItemId(".rst");
  RestrictedItem item(name, newId);
  item.create(nullptr);
  std::cout << "Item restrito " << name << " registrado com ID " << newId << "\n";
}

void Librarian::registerExhibitionItem(const std::string &name) {
  uint32_t newId = getNextItemId(".exb");
  ExhibitionItem item(name, Status::AVAILABLE, newId);
  item.create(nullptr);
  std::cout << "Item de exposição " << name << " registrado com ID " << newId << "\n";
}

void Librarian::lendItem(AcademicMember *user, uint32_t itemId) {
  LoanableItem item("", Status::AVAILABLE, itemId);
  if (!item.read(std::to_string(itemId))) {
    std::cout << "Item com ID " << itemId << " não encontrado.\n";
    return;
  }

  if (item.getStatus() == Status::AVAILABLE) {
    if (user->ActiveLoans < user->maxActiveLoans) {
      item.setStatus(Status::BORROWED);
      item.responsibleId = user->matricula;
      item.setDisplayArea("não está na biblioteca");
      item.borrowedAt = time(nullptr);
      item.dueDate = item.borrowedAt + 14 * 24 * 60 * 60;
      user->ActiveLoans++;
      item.update(std::to_string(itemId));
      user->update(std::to_string(user->matricula));
      std::cout << "Item " << item.name << " emprestado para " << user->name
                << " (" << user->matricula << ")\n";
    } else {
      std::cout << "Usuário " << user->name << " atingiu o limite de "
                << user->maxActiveLoans << " empréstimos.\n";
    }
  } else {
    std::cout << "Item " << item.name << " não está disponível.\n";
  }
}

void Librarian::receiveReturn(AcademicMember *user, uint32_t itemId) {
  LoanableItem item("", Status::AVAILABLE, itemId);
  if (!item.read(std::to_string(itemId))) {
    std::cout << "Item com ID " << itemId << " não encontrado.\n";
    return;
  }

  if (item.isBorrowed() && item.responsibleId == user->matricula) {
    item.responsibleId = 0;
    item.borrowedAt = 0;
    item.dueDate = 0;
    item.setStatus(Status::AVAILABLE);
    item.setDisplayArea("depósito de devoluções");
    user->ActiveLoans--;
    item.update(std::to_string(itemId));
    user->update(std::to_string(user->matricula));
    std::cout << "Item " << item.name << " devolvido por " << user->name
              << " (" << user->matricula << ")\n";
  } else {
    std::cout << "Este item não está emprestado a " << user->name << ".\n";
  }
}

void Librarian::applyFine(AcademicMember *user, int daysLate) {
  const double finePerDay = 1.50;
  double totalFine = daysLate * finePerDay;
  std::cout << "--- Aplicação de Multa ---\n";
  std::cout << "Usuário: " << user->name << " (" << user->matricula << ")\n";
  std::cout << "Dias em atraso: " << daysLate << "\n";
  std::cout << "Valor por dia: R$ " << finePerDay << "\n";
  std::cout << "Total da multa: R$ " << totalFine << "\n";
}

Librarian::Librarian(std::string n, uint32_t m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
