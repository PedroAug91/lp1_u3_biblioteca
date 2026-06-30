#include "include/Professor.hpp"
#include "../item/include/RestrictedItem.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

namespace fs = std::filesystem;

void Professor::print() {
  std::cout << "Nome: " << this->name << '\n'
            << "Matrícula: " << this->matricula << '\n'
            << "Empréstimos ativos: " << this->ActiveLoans << '\n'
            << "Empréstimos restantes: "
            << (this->maxActiveLoans - this->ActiveLoans) << '\n';
}

static std::vector<RestrictedItem> loadRestrictedItems() {
  std::vector<RestrictedItem> items;
  if (!fs::exists("library_db")) return items;
  for (auto &entry : fs::directory_iterator("library_db")) {
    auto path = entry.path();
    if (path.extension() == ".rst") {
      try {
        uint32_t id = std::stoul(path.stem().string());
        RestrictedItem item("", id);
        if (item.read(std::to_string(id)))
          items.push_back(std::move(item));
      } catch (...) {}
    }
  }
  return items;
}

void Professor::RequestRestrictedAccess() {
  auto items = loadRestrictedItems();
  if (items.empty()) {
    std::cout << "Nenhum item restrito disponível.\n";
    return;
  }

  std::cout << "\n--- Itens Restritos Disponíveis ---\n";
  for (size_t i = 0; i < items.size(); ++i)
    std::cout << (i + 1) << ". " << items[i].name << " (ID: " << items[i].id << ")\n";

  std::cout << "Escolha um item (0 para cancelar): ";
  int itemChoice;
  std::cin >> itemChoice;
  if (itemChoice < 1 || itemChoice > (int)items.size()) {
    std::cout << "Operação cancelada.\n";
    return;
  }

  RestrictedItem &selected = items[itemChoice - 1];
  std::cout << "\nItem selecionado: " << selected.name << "\n";

  selected.getAvailableAppointments();

  std::cout << "\nEscolha o dia (1-" << RestrictedItem::NUM_DAYS << "): ";
  int day;
  std::cin >> day;
  if (day < 1 || day > RestrictedItem::NUM_DAYS) {
    std::cout << "Dia inválido.\n";
    return;
  }

  std::cout << "Escolha o horário (1-3): ";
  int slot;
  std::cin >> slot;
  if (slot < 1 || slot > RestrictedItem::NUM_SLOTS) {
    std::cout << "Horário inválido.\n";
    return;
  }

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Adicionar acompanhantes? (s/n): ";
  std::string addGuests;
  std::getline(std::cin, addGuests);

  if (addGuests == "s" || addGuests == "S") {
    std::cout << "Você pode adicionar até 5 acompanhantes.\n";
    std::cout << "Insira as matrículas separadas por espaço (0 para finalizar): ";

    std::string line;
    std::getline(std::cin, line);
    std::cout << "Acompanhantes adicionados ao agendamento.\n";
  }

  if (selected.ScheduleVisit(day - 1, slot - 1, this->name, this->matricula)) {
    selected.update(std::to_string(selected.id));
    std::cout << "\n--- Comprovante de Agendamento ---\n";
    std::cout << "Professor: " << this->name << " (" << this->matricula << ")\n";
    std::cout << "Item: " << selected.name << "\n";
  }
}

Professor::Professor(std::string n, uint32_t m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
