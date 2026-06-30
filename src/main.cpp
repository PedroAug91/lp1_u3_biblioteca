#include "item/include/ExhibitionItem.hpp"
#include "item/include/LoanableItem.hpp"
#include "item/include/RestrictedItem.hpp"
#include "item/include/Status.hpp"
#include "person/include/AcademicMember.hpp"
#include "person/include/Librarian.hpp"
#include "person/include/Professor.hpp"
#include "person/include/Student.hpp"

#include <functional>
#include <iostream>
#include <limits>
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
  }
};

// ── helpers ─────────────────────────────────────────────────────────
static void clearScreen() { std::cout << "\033[2J\033[1;1H"; }

static void wait() {
  std::cout << "\nPressione Enter para continuar...";
  std::cin.get();
}

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

  clearScreen();
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
  uint32_t id;
  std::cin >> id;
  user->BorrowItem(loanable, id);
}

static void cmdReturn(AcademicMember *user,
                      std::vector<LoanableItem> &loanable) {
  std::cout << "ID do item: ";
  uint32_t id;
  std::cin >> id;
  user->ReturnItem(loanable, id);
}

static void cmdShowItems(std::vector<LoanableItem> &loanable,
                         std::vector<RestrictedItem> &restricted,
                         std::vector<ExhibitionItem> &exhibition) {
  std::cout << "\n--- Itens para Empréstimo ---\n";
  for (auto &i : loanable) {
    std::cout << "  " << i.id << " - " << i.name << " [";
    switch (static_cast<char>(i.getStatus())) {
    case 'A':
      std::cout << "Disponível";
      break;
    case 'U':
      std::cout << "Indisponível";
      break;
    case 'B':
      std::cout << "Emprestado";
      break;
    }
    std::cout << "]\n";
  }
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
  clearScreen();
  std::cout << "Bem-vindo, estudante " << user->name << "!\n";
}

static void professorSession(AcademicMember *user) {
  clearScreen();
  std::cout << "Bem-vindo, professor " << user->name << "!\n";
  Professor *prof = dynamic_cast<Professor *>(user);
  if (prof)
    prof->RequestRestrictedAccess();
}

static void librarianSession(AcademicMember *user,
                             std::vector<LoanableItem> &loanable,
                             std::vector<RestrictedItem> &restricted,
                             std::vector<ExhibitionItem> &exhibition,
                             std::vector<AcademicMember *> &users) {
  clearScreen();
  std::cout << "Bem-vindo, bibliotecário " << user->name << "!\n";
  Librarian *lib = dynamic_cast<Librarian *>(user);
  if (!lib) return;

  bool firstAccess = true;
  while (true) {
    if (!firstAccess) {
      wait();
      clearScreen();
    }
    firstAccess = false;
    Menu libMenu("Menu do Bibliotecário");
    libMenu.add(1, "Registrar usuário");
    libMenu.add(2, "Registrar item emprestável");
    libMenu.add(3, "Registrar item restrito");
    libMenu.add(4, "Registrar item de exposição");
    libMenu.add(5, "Emprestar item a usuário");
    libMenu.add(6, "Aplicar multa");
    libMenu.add(7, "Listar itens");
    libMenu.add(8, "Ver meus dados");
    libMenu.add(0, "Sair");

    int choice = libMenu.show();
    if (choice == 0) break;

    switch (choice) {
    case 1: {
      std::string type, name;
      std::cout << "Tipo (student/professor): ";
      std::getline(std::cin, type);
      std::cout << "Nome: ";
      std::getline(std::cin, name);
      lib->registerUser(users, type, name);
      break;
    }
    case 2: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerLoanableItem(loanable, name);
      break;
    }
    case 3: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerRestrictedItem(restricted, name);
      break;
    }
    case 4: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerExhibitionItem(exhibition, name);
      break;
    }
    case 5: {
      AcademicMember *target = pickUser<AcademicMember>(users);
      if (target) {
        uint32_t itemId;
        std::cout << "ID do item: ";
        std::cin >> itemId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        lib->lendItem(target, loanable, itemId);
      }
      break;
    }
    case 6: {
      AcademicMember *target = pickUser<AcademicMember>(users);
      if (target) {
        int days;
        std::cout << "Dias em atraso: ";
        std::cin >> days;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        lib->applyFine(target, days);
      }
      break;
    }
    case 7:
      cmdShowItems(loanable, restricted, exhibition);
      break;
    case 8:
      lib->print();
      break;
    default:
      std::cout << "Opção inválida.\n";
    }
  }
}

// ── registered roles (extend here to add new roles) ────────────────
static std::map<int, std::pair<std::string, RoleHandler>> registeredRoles;

static void registerRole(int id, std::string label, RoleHandler handler) {
  registeredRoles[id] = {std::move(label), std::move(handler)};
}

static void initRoles() {
  registerRole(1, "Login como Aluno", studentSession);
  registerRole(2, "Login como Professor", professorSession);
}

// ── main ───────────────────────────────────────────────────────────
int main() {
  initRoles();

  // ── data initialisation ──────────────────────────────────────────
  std::vector<LoanableItem> LoanableList;
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::UNAVAILABLE, 1));
  LoanableList.push_back(
      LoanableItem("Clean Code", Status::UNAVAILABLE, 2));
  LoanableList.push_back(
      LoanableItem("Animal Farm", Status::UNAVAILABLE, 3));
  LoanableList.push_back(LoanableItem("1984", Status::UNAVAILABLE, 4));
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::AVAILABLE, 5));
  LoanableList.push_back(LoanableItem("Clean Code", Status::AVAILABLE, 6));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::AVAILABLE, 7));
  LoanableList.push_back(LoanableItem("1984", Status::AVAILABLE, 8));
  LoanableList.push_back(
      LoanableItem("Dom Casmurro", Status::AVAILABLE, 9));
  LoanableList.push_back(LoanableItem("Clean Code", Status::AVAILABLE, 10));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::AVAILABLE, 11));
  LoanableList.push_back(LoanableItem("1984", Status::AVAILABLE, 12));

  std::vector<RestrictedItem> restrictedList;
  restrictedList.push_back(RestrictedItem("Enciclopédia Britânica", 13));
  restrictedList.push_back(RestrictedItem("Atlas Mundial", 14));
  restrictedList.push_back(RestrictedItem("Dicionário Oxford", 15));
  restrictedList.push_back(RestrictedItem("Manuscritos Históricos", 16));
  restrictedList.push_back(RestrictedItem("Coleção de Mapas Antigos", 17));

  std::vector<ExhibitionItem> exhibitionList;
  exhibitionList.push_back(ExhibitionItem("Máscara Funerária Egípcia",
                                          Status::AVAILABLE, 18,
                                          "Sala Egito Antigo"));
  exhibitionList.push_back(ExhibitionItem(
      "Escultura Grega Clássica", Status::AVAILABLE, 19, "Galeria Grécia"));
  exhibitionList.push_back(ExhibitionItem(
      "Armadura Medieval", Status::AVAILABLE, 20, "Sala Idade Média"));
  exhibitionList.push_back(ExhibitionItem("Pintura Renacentista",
                                          Status::AVAILABLE, 21,
                                          "Galeria Renascimento"));
  exhibitionList.push_back(ExhibitionItem("Fóssil de Dinossauro",
                                          Status::AVAILABLE, 22,
                                          "Sala de Paleontologia"));

  std::vector<AcademicMember *> AcademicUsers;
  AcademicUsers.push_back(new Student("Ana", 1));
  AcademicUsers.push_back(new Student("João", 2));
  AcademicUsers.push_back(new Student("gustavo", 3));
  AcademicUsers.push_back(new Student("João", 4));
  AcademicUsers.push_back(new Student("Ana", 5));
  AcademicUsers.push_back(new Student("Carlos", 6));
  AcademicUsers.push_back(new Professor("gustavo", 7));
  AcademicUsers.push_back(new Professor("João", 8));
  AcademicUsers.push_back(new Student("Ana", 9));
  AcademicUsers.push_back(new Student("Carlos", 10));
  AcademicUsers.push_back(new Professor("Carlos", 11));
  AcademicUsers.push_back(new Professor("Mariana", 12));
  AcademicUsers.push_back(new Professor("Roberto", 13));
  AcademicUsers.push_back(new Librarian("Bibliotecário", 14));

  registeredRoles[3] = {"Login como Bibliotecário",
                        [&](AcademicMember *user) {
                          librarianSession(user, LoanableList, restrictedList,
                                           exhibitionList, AcademicUsers);
                        }};

  // ── main loop ────────────────────────────────────────────────────
  while (true) {
    clearScreen();
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
      wait();
      continue;
    }

    AcademicMember *user = nullptr;
    if (roleChoice == 1)
      user = pickUser<Student>(AcademicUsers);
    else if (roleChoice == 2)
      user = pickUser<Professor>(AcademicUsers);
    else if (roleChoice == 3)
      user = pickUser<Librarian>(AcademicUsers);

    if (!user) {
      std::cout << "Operação cancelada.\n";
      wait();
      continue;
    }

    // Role-specific welcome
    it->second.second(user);

    // Shared user session menu (skip for librarian, which has its own menu)
    if (roleChoice == 3) continue;
    bool firstAccess = true;
    while (true) {
      if (!firstAccess) {
        wait();
        clearScreen();
      }
      firstAccess = false;
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
