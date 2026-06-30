#include "include/Librarian.hpp"
#include "include/Professor.hpp"
#include "include/Student.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

void Librarian::print() {
  std::cout << "--- Bibliotecário ---\n";
  std::cout << "Nome: " << name << '\n' << "Matrícula: " << matricula << '\n';
}

bool Librarian::create(Person *p_person) {
  Librarian *lib = dynamic_cast<Librarian *>(p_person);
  if (!lib) return false;
  std::string path = "library_db/" + std::to_string(lib->matricula) + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << lib->name << "\n";
  file << "matricula=" << lib->matricula << "\n";
  file << "type=librarian\n";
  return true;
}

bool Librarian::read(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cout << "Arquivo não encontrado: " << path << "\n";
    return false;
  }
  std::string line;
  while (std::getline(file, line))
    std::cout << line << "\n";
  return true;
}

bool Librarian::update(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  std::ofstream file(path);
  if (!file.is_open()) return false;
  file << "name=" << this->name << "\n";
  file << "matricula=" << this->matricula << "\n";
  file << "type=librarian\n";
  return true;
}

bool Librarian::remove(std::string person_id) {
  std::string path = "library_db/" + person_id + ".data";
  return std::remove(path.c_str()) == 0;
}

void Librarian::registerUser(std::vector<AcademicMember *> &users,
                              const std::string &type,
                              const std::string &name) {
  uint32_t newMat = 1;
  for (auto *u : users)
    if (u->matricula >= newMat) newMat = u->matricula + 1;

  if (type == "student") {
    users.push_back(new Student(name, newMat));
    std::cout << "Estudante " << name << " registrado com matrícula " << newMat << "\n";
  } else if (type == "professor") {
    users.push_back(new Professor(name, newMat));
    std::cout << "Professor " << name << " registrado com matrícula " << newMat << "\n";
  } else {
    std::cout << "Tipo de usuário desconhecido: " << type << "\n";
  }
}

void Librarian::registerLoanableItem(std::vector<LoanableItem> &items,
                                      const std::string &name) {
  uint32_t newId = 1;
  for (auto &item : items)
    if (item.id >= newId) newId = item.id + 1;

  items.push_back(LoanableItem(name, Status::AVAILABLE, newId));
  std::cout << "Item emprestável " << name << " registrado com ID " << newId << "\n";
}

void Librarian::registerRestrictedItem(std::vector<RestrictedItem> &items,
                                        const std::string &name) {
  uint32_t newId = 1;
  for (auto &item : items)
    if (item.id >= newId) newId = item.id + 1;

  items.push_back(RestrictedItem(name, newId));
  std::cout << "Item restrito " << name << " registrado com ID " << newId << "\n";
}

void Librarian::registerExhibitionItem(std::vector<ExhibitionItem> &items,
                                        const std::string &name) {
  uint32_t newId = 1;
  for (auto &item : items)
    if (item.id >= newId) newId = item.id + 1;

  items.push_back(ExhibitionItem(name, Status::AVAILABLE, newId));
  std::cout << "Item de exposição " << name << " registrado com ID " << newId << "\n";
}

void Librarian::lendItem(AcademicMember *user, std::vector<LoanableItem> &items,
                          uint32_t itemId) {
  for (auto &item : items) {
    if (item.id == itemId) {
      if (item.getStatus() == Status::AVAILABLE) {
        if (user->ActiveLoans < user->maxActiveLoans) {
          item.setStatus(Status::BORROWED);
          item.responsibleId = user->matricula;
          item.setDisplayArea("não está na biblioteca");
          user->ActiveLoans++;
          std::cout << "Item " << item.name << " emprestado para " << user->name
                    << " (" << user->matricula << ")\n";
        } else {
          std::cout << "Usuário " << user->name << " atingiu o limite de "
                    << user->maxActiveLoans << " empréstimos.\n";
        }
      } else {
        std::cout << "Item " << item.name << " não está disponível.\n";
      }
      return;
    }
  }
  std::cout << "Item com ID " << itemId << " não encontrado.\n";
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
