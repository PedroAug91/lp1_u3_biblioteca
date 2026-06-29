#include "item/include/ExhibitionItem.hpp"
#include "item/include/LoanableItem.hpp"
#include "item/include/RestrictedItem.hpp"
#include "item/include/Status.hpp"
#include "person/include/AcademicMember.hpp"
#include "person/include/Professor.hpp"
#include "person/include/Student.hpp"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Menu {
  std::string title_;
  std::vector<std::pair<int, std::string>> options_;

public:
  Menu(std::string title) : title_(std::move(title)) {}

  void add(int id, std::string label) {
    options_.push_back({id, std::move(label)});
  }

  int show() const {
    std::cout << "\n=== " << title_ << " ===\n";
    for (auto &opt : options_)
      std::cout << opt.first << ". " << opt.second << "\n";
    std::cout << "Escolha: ";
    int choice;
    std::cin >> choice;
    return choice;
  }
};

// ── role handler type ──────────────────────────────────────────────
using RoleHandler = std::function<void(AcademicMember *user)>;

// ── helper: list users of a given type and let the user pick one ───
template <typename T>
AcademicMember *pickUser(std::vector<AcademicMember *> &allUsers) {
  std::vector<AcademicMember *> filtered;
  for (auto *u : allUsers)
    if (dynamic_cast<T *>(u))
      filtered.push_back(u);

  if (filtered.empty()) {
    std::cout << "Nenhum usuário disponível.\n";
    return nullptr;
  }

  std::cout << "\n--- Selecione um usuário ---\n";
  for (size_t i = 0; i < filtered.size(); ++i)
    std::cout << (i + 1) << ". " << filtered[i]->name << " ("
              << filtered[i]->matricula << ")\n";
  std::cout << "0. Voltar\nEscolha: ";

  int choice;
  std::cin >> choice;
  if (choice < 1 || choice > (int)filtered.size())
    return nullptr;
  return filtered[choice - 1];
}

// ── session helpers ────────────────────────────────────────────────
static void cmdBorrow(AcademicMember *user,
                      std::vector<LoanableItem> &loanable) {
  std::cout << "ID do item: ";
  std::string id;
  std::cin >> id;
  user->BorrowItem(loanable, id);
}

static void cmdReturn(AcademicMember *user,
                      std::vector<LoanableItem> &loanable) {
  std::cout << "ID do item: ";
  std::string id;
  std::cin >> id;
  user->ReturnItem(loanable, id);
}

static void cmdShowItems(std::vector<LoanableItem> &loanable,
                         std::vector<RestrictedItem> &restricted,
                         std::vector<ExhibitionItem> &exhibition) {
  std::cout << "\n--- Itens para Empréstimo ---\n";
  for (auto &i : loanable)
    std::cout << "  " << i.id << " - " << i.name << " ["
              << static_cast<char>(i.getStatus()) << "]\n";
  std::cout << "\n--- Itens Restritos ---\n";
  for (auto &i : restricted)
    std::cout << "  " << i.id << " - " << i.name << "\n";
  std::cout << "\n--- Itens de Exposição ---\n";
  for (auto &i : exhibition)
    std::cout << "  " << i.id << " - " << i.name << " [" << i.getDisplayArea()
              << "]\n";
}

// ── role sessions ──────────────────────────────────────────────────
static void studentSession(AcademicMember *user) {
  std::cout << "\nBem-vindo, estudante " << user->name << "!\n";
}

static void professorSession(AcademicMember *user) {
  std::cout << "\nBem-vindo, professor " << user->name << "!\n";
  Professor *prof = dynamic_cast<Professor *>(user);
  if (prof)
    prof->RequestRestrictedAccess();
}

// ── registered roles (extend here to add new roles) ────────────────
static std::map<int, std::pair<std::string, RoleHandler>> registeredRoles;

static void registerRole(int id, std::string label, RoleHandler handler) {
  registeredRoles[id] = {std::move(label), std::move(handler)};
}

static void initRoles() {
  registerRole(1, "Login como Aluno", studentSession);
  registerRole(2, "Login como Professor", professorSession);
  // Exemplo futura expansão:
  // registerRole(3, "Login como Bibliotecário", librarianSession);
}

// ── main ───────────────────────────────────────────────────────────
int main() {
  initRoles();

  // ── data initialisation ──────────────────────────────────────────
  std::vector<LoanableItem> LoanableList;
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::UNAVAILABLE, "002"));
  LoanableList.push_back(
      LoanableItem("Clean Code", Status::UNAVAILABLE, "003"));
  LoanableList.push_back(
      LoanableItem("Animal Farm", Status::UNAVAILABLE, "004"));
  LoanableList.push_back(LoanableItem("1984", Status::UNAVAILABLE, "005"));
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::AVAILABLE, "006"));
  LoanableList.push_back(LoanableItem("Clean Code", Status::AVAILABLE, "007"));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::AVAILABLE, "008"));
  LoanableList.push_back(LoanableItem("1984", Status::AVAILABLE, "009"));
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::AVAILABLE, "010"));
  LoanableList.push_back(LoanableItem("Clean Code", Status::AVAILABLE, "011"));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::AVAILABLE, "012"));
  LoanableList.push_back(LoanableItem("1984", Status::AVAILABLE, "013"));

  std::vector<RestrictedItem> restrictedList;
  restrictedList.push_back(RestrictedItem("Enciclopédia Britânica", "R001"));
  restrictedList.push_back(RestrictedItem("Atlas Mundial", "R002"));
  restrictedList.push_back(RestrictedItem("Dicionário Oxford", "R003"));
  restrictedList.push_back(RestrictedItem("Manuscritos Históricos", "R004"));
  restrictedList.push_back(RestrictedItem("Coleção de Mapas Antigos", "R005"));

  std::vector<ExhibitionItem> exhibitionList;
  exhibitionList.push_back(ExhibitionItem("Máscara Funerária Egípcia",
                                          Status::AVAILABLE, "E001",
                                          "Sala Egito Antigo"));
  exhibitionList.push_back(ExhibitionItem(
      "Escultura Grega Clássica", Status::AVAILABLE, "E002", "Galeria Grécia"));
  exhibitionList.push_back(ExhibitionItem(
      "Armadura Medieval", Status::AVAILABLE, "E003", "Sala Idade Média"));
  exhibitionList.push_back(ExhibitionItem("Pintura Renacentista",
                                          Status::AVAILABLE, "E004",
                                          "Galeria Renascimento"));
  exhibitionList.push_back(ExhibitionItem("Fóssil de Dinossauro",
                                          Status::AVAILABLE, "E005",
                                          "Sala de Paleontologia"));

  std::vector<AcademicMember *> AcademicUsers;
  AcademicUsers.push_back(new Student("Ana", "002"));
  AcademicUsers.push_back(new Student("João", "003"));
  AcademicUsers.push_back(new Student("gustavo", "004"));
  AcademicUsers.push_back(new Student("João", "005"));
  AcademicUsers.push_back(new Student("Ana", "006"));
  AcademicUsers.push_back(new Student("Carlos", "007"));
  AcademicUsers.push_back(new Professor("gustavo", "008"));
  AcademicUsers.push_back(new Professor("João", "009"));
  AcademicUsers.push_back(new Student("Ana", "010"));
  AcademicUsers.push_back(new Student("Carlos", "011"));
  AcademicUsers.push_back(new Professor("Carlos", "012"));
  AcademicUsers.push_back(new Professor("Mariana", "013"));
  AcademicUsers.push_back(new Professor("Roberto", "014"));

  // ── main loop ────────────────────────────────────────────────────
  while (true) {
    Menu loginMenu("Sistema da Biblioteca");
    for (auto &[id, entry] : registeredRoles)
      loginMenu.add(id, entry.first);
    loginMenu.add(0, "Sair");

    int roleChoice = loginMenu.show();
    if (roleChoice == 0)
      break;

    auto it = registeredRoles.find(roleChoice);
    if (it == registeredRoles.end()) {
      std::cout << "Opção inválida.\n";
      continue;
    }

    AcademicMember *user = nullptr;
    if (roleChoice == 1)
      user = pickUser<Student>(AcademicUsers);
    else if (roleChoice == 2)
      user = pickUser<Professor>(AcademicUsers);

    if (!user) {
      std::cout << "Operação cancelada.\n";
      continue;
    }

    // Role-specific welcome
    it->second.second(user);

    // Shared user session menu
    while (true) {
      Menu userMenu("Menu do Usuário");
      userMenu.add(1, "Buscar item");
      userMenu.add(2, "Pegar item emprestado");
      userMenu.add(3, "Devolver item");
      userMenu.add(4, "Listar itens");
      userMenu.add(5, "Ver meus dados");
      userMenu.add(0, "Sair");

      int userChoice = userMenu.show();
      if (userChoice == 0)
        break;

      switch (userChoice) {
      case 1:
        user->searchItem();
        break;
      case 2:
        cmdBorrow(user, LoanableList);
        break;
      case 3:
        cmdReturn(user, LoanableList);
        break;
      case 4:
        cmdShowItems(LoanableList, restrictedList, exhibitionList);
        break;
      case 5:
        user->print();
        break;
      default:
        std::cout << "Opção inválida.\n";
      }
    }
  }

  for (auto *u : AcademicUsers)
    delete u;

  return 0;
}
