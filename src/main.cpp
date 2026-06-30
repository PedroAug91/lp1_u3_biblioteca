#include "item/include/ExhibitionItem.hpp"
#include "item/include/LoanableItem.hpp"
#include "item/include/RestrictedItem.hpp"
#include "item/include/Status.hpp"
#include "person/include/AcademicMember.hpp"
#include "person/include/Librarian.hpp"
#include "person/include/Professor.hpp"
#include "person/include/Student.hpp"

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

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
  if (!std::cin) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.get();
}

// ── role handler type ──────────────────────────────────────────────
using RoleHandler = std::function<void(AcademicMember *user)>;

// ── database helpers ───────────────────────────────────────────────

static std::string dbDir() { return "library_db"; }

static void ensureDbDir() { fs::create_directories(dbDir()); }

static std::vector<LoanableItem> loadAllLoanable() {
  std::vector<LoanableItem> items;
  if (!fs::exists(dbDir())) return items;
  for (auto &entry : fs::directory_iterator(dbDir())) {
    auto path = entry.path();
    if (path.extension() == ".lnb") {
      try {
        uint32_t id = std::stoul(path.stem().string());
        LoanableItem item("", Status::AVAILABLE, id);
        if (item.read(std::to_string(id)))
          items.push_back(std::move(item));
      } catch (...) {}
    }
  }
  return items;
}

static std::vector<RestrictedItem> loadAllRestricted() {
  std::vector<RestrictedItem> items;
  if (!fs::exists(dbDir())) return items;
  for (auto &entry : fs::directory_iterator(dbDir())) {
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

static std::vector<ExhibitionItem> loadAllExhibition() {
  std::vector<ExhibitionItem> items;
  if (!fs::exists(dbDir())) return items;
  for (auto &entry : fs::directory_iterator(dbDir())) {
    auto path = entry.path();
    if (path.extension() == ".exb") {
      try {
        uint32_t id = std::stoul(path.stem().string());
        ExhibitionItem item("", Status::AVAILABLE, id);
        if (item.read(std::to_string(id)))
          items.push_back(std::move(item));
      } catch (...) {}
    }
  }
  return items;
}

static std::string readTypeFromFile(const std::string &id) {
  std::string path = dbDir() + "/" + id + ".usr";
  std::ifstream file(path);
  if (!file.is_open()) return "";
  std::string line;
  while (std::getline(file, line)) {
    if (line.rfind("type=", 0) == 0)
      return line.substr(5);
  }
  return "";
}

static std::vector<std::string> listUserIds() {
  std::vector<std::string> ids;
  if (!fs::exists(dbDir())) return ids;
  for (auto &entry : fs::directory_iterator(dbDir())) {
    auto path = entry.path();
    if (path.extension() == ".usr")
      ids.push_back(path.stem().string());
  }
  return ids;
}

// ── helper: list users of a given type and let the user pick one ───
template <typename T>
static AcademicMember *pickUser() {
  auto ids = listUserIds();
  std::vector<AcademicMember *> filtered;
  for (auto &id : ids) {
    std::string type = readTypeFromFile(id);
    bool matches = false;
    if constexpr (std::is_same_v<T, Student>)
      matches = (type == "student");
    else if constexpr (std::is_same_v<T, Professor>)
      matches = (type == "professor");
    else if constexpr (std::is_same_v<T, Librarian>)
      matches = (type == "librarian");
    else
      matches = true;

    if (!matches) continue;

    uint32_t numId = std::stoul(id);
    AcademicMember *u = nullptr;
    if constexpr (std::is_same_v<T, Student>)
      u = new Student("", numId);
    else if constexpr (std::is_same_v<T, Professor>)
      u = new Professor("", numId);
    else if constexpr (std::is_same_v<T, Librarian>)
      u = new Librarian("", numId);
    else {
      if (type == "student")
        u = new Student("", numId);
      else if (type == "professor")
        u = new Professor("", numId);
      else if (type == "librarian")
        u = new Librarian("", numId);
    }

    if (u && u->read(id))
      filtered.push_back(u);
    else
      delete u;
  }

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
  if (choice < 1 || choice > (int)filtered.size()) {
    for (auto *u : filtered) delete u;
    return nullptr;
  }

  AcademicMember *result = filtered[choice - 1];
  for (size_t i = 0; i < filtered.size(); ++i)
    if (i != (size_t)(choice - 1)) delete filtered[i];
  return result;
}

// ── session helpers ────────────────────────────────────────────────
static void cmdBorrow(AcademicMember *user) {
  std::cout << "ID do item: ";
  uint32_t id;
  std::cin >> id;
  user->BorrowItem(id);
}

static void cmdReturn(AcademicMember *user) {
  std::cout << "ID do item: ";
  uint32_t id;
  std::cin >> id;
  user->ReturnItem(id);
}

static void cmdShowItems() {
  auto loanable = loadAllLoanable();
  auto restricted = loadAllRestricted();
  auto exhibition = loadAllExhibition();

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

static void librarianSession(AcademicMember *user) {
  clearScreen();
  std::cout << "Bem-vindo, bibliotecário " << user->name << "!\n";
  Librarian *lib = dynamic_cast<Librarian *>(user);
  if (!lib)
    return;

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
    if (!std::cin || choice == 0)
      break;

    switch (choice) {
    case 1: {
      std::string type, name;
      std::cout << "Tipo (student/professor): ";
      std::getline(std::cin, type);
      std::cout << "Nome: ";
      std::getline(std::cin, name);
      lib->registerUser(type, name);
      break;
    }
    case 2: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerLoanableItem(name);
      break;
    }
    case 3: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerRestrictedItem(name);
      break;
    }
    case 4: {
      std::string name;
      std::cout << "Nome do item: ";
      std::getline(std::cin, name);
      lib->registerExhibitionItem(name);
      break;
    }
    case 5: {
      AcademicMember *target = pickUser<AcademicMember>();
      if (target) {
        uint32_t itemId;
        std::cout << "ID do item: ";
        std::cin >> itemId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        lib->lendItem(target, itemId);
        delete target;
      }
      break;
    }
    case 6: {
      AcademicMember *target = pickUser<AcademicMember>();
      if (target) {
        int days;
        std::cout << "Dias em atraso: ";
        std::cin >> days;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        lib->applyFine(target, days);
        delete target;
      }
      break;
    }
    case 7:
      cmdShowItems();
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
  registerRole(3, "Login como Bibliotecário", librarianSession);
}

// ── database seeding ───────────────────────────────────────────────
static bool isDatabaseSeeded() {
  if (!fs::exists(dbDir())) return false;
  return fs::directory_iterator(dbDir()) != fs::directory_iterator();
}

static void seedDatabase() {
  ensureDbDir();

  LoanableItem("Dom Casmurro", Status::UNAVAILABLE, 1).create(nullptr);
  LoanableItem("Clean Code", Status::UNAVAILABLE, 2).create(nullptr);
  LoanableItem("Animal Farm", Status::UNAVAILABLE, 3).create(nullptr);
  LoanableItem("1984", Status::UNAVAILABLE, 4).create(nullptr);
  LoanableItem("Dom Casmurro", Status::AVAILABLE, 5).create(nullptr);
  LoanableItem("Clean Code", Status::AVAILABLE, 6).create(nullptr);
  LoanableItem("Animal Farm", Status::AVAILABLE, 7).create(nullptr);
  LoanableItem("1984", Status::AVAILABLE, 8).create(nullptr);
  LoanableItem("Dom Casmurro", Status::AVAILABLE, 9).create(nullptr);
  LoanableItem("Clean Code", Status::AVAILABLE, 10).create(nullptr);
  LoanableItem("Animal Farm", Status::AVAILABLE, 11).create(nullptr);
  LoanableItem("1984", Status::AVAILABLE, 12).create(nullptr);

  RestrictedItem("Enciclopédia Britânica", 13).create(nullptr);
  RestrictedItem("Atlas Mundial", 14).create(nullptr);
  RestrictedItem("Dicionário Oxford", 15).create(nullptr);
  RestrictedItem("Manuscritos Históricos", 16).create(nullptr);
  RestrictedItem("Coleção de Mapas Antigos", 17).create(nullptr);

  ExhibitionItem("Máscara Funerária Egípcia", Status::AVAILABLE, 18, "Sala Egito Antigo").create(nullptr);
  ExhibitionItem("Escultura Grega Clássica", Status::AVAILABLE, 19, "Galeria Grécia").create(nullptr);
  ExhibitionItem("Armadura Medieval", Status::AVAILABLE, 20, "Sala Idade Média").create(nullptr);
  ExhibitionItem("Pintura Renacentista", Status::AVAILABLE, 21, "Galeria Renascimento").create(nullptr);
  ExhibitionItem("Fóssil de Dinossauro", Status::AVAILABLE, 22, "Sala de Paleontologia").create(nullptr);

  auto s1 = Student("Ana", 1); s1.create(&s1);
  auto s2 = Student("João", 2); s2.create(&s2);
  auto s3 = Student("gustavo", 3); s3.create(&s3);
  auto s4 = Student("João", 4); s4.create(&s4);
  auto s5 = Student("Ana", 5); s5.create(&s5);
  auto s6 = Student("Carlos", 6); s6.create(&s6);
  auto p1 = Professor("gustavo", 7); p1.create(&p1);
  auto p2 = Professor("João", 8); p2.create(&p2);
  auto s7 = Student("Ana", 9); s7.create(&s7);
  auto s8 = Student("Carlos", 10); s8.create(&s8);
  auto p3 = Professor("Carlos", 11); p3.create(&p3);
  auto p4 = Professor("Mariana", 12); p4.create(&p4);
  auto p5 = Professor("Roberto", 13); p5.create(&p5);
  auto l1 = Librarian("Bibliotecário", 14); l1.create(&l1);
}

// ── main ───────────────────────────────────────────────────────────
int main() {
  initRoles();

  if (!isDatabaseSeeded())
    seedDatabase();

  // ── main loop ────────────────────────────────────────────────────
  while (true) {
    clearScreen();
    Menu loginMenu("Sistema da Biblioteca");
    for (auto &[id, entry] : registeredRoles)
      loginMenu.add(id, entry.first);
    loginMenu.add(0, "Sair");

    int roleChoice = loginMenu.show();
    if (!std::cin || roleChoice == 0)
      break;

    auto it = registeredRoles.find(roleChoice);
    if (it == registeredRoles.end()) {
      std::cout << "Opção inválida.\n";
      wait();
      if (!std::cin) std::cin.clear();
      continue;
    }

    AcademicMember *user = nullptr;
    if (roleChoice == 1)
      user = pickUser<Student>();
    else if (roleChoice == 2)
      user = pickUser<Professor>();
    else if (roleChoice == 3)
      user = pickUser<Librarian>();

    if (!user) {
      std::cout << "Operação cancelada.\n";
      wait();
      if (!std::cin) std::cin.clear();
      continue;
    }

    // Role-specific welcome
    it->second.second(user);

    // Shared user session menu (skip for librarian, which has its own menu)
    if (roleChoice == 3) {
      delete user;
      continue;
    }
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
      if (!std::cin || userChoice == 0)
        break;

      switch (userChoice) {
      case 1:
        user->searchItem();
        break;
      case 2:
        cmdBorrow(user);
        break;
      case 3:
        cmdReturn(user);
        break;
      case 4:
        cmdShowItems();
        break;
      case 5:
        user->print();
        break;
      default:
        std::cout << "Opção inválida.\n";
      }
    }

    delete user;
  }

  return 0;
}
