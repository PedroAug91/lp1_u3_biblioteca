#include "item/include/LoanableItem.hpp"
#include "item/include/RestrictedItem.hpp"
#include "item/include/ExhibitionItem.hpp"
#include "item/include/Status.hpp"
#include "person/include/AcademicMember.hpp"
#include "person/include/Professor.hpp"
#include "person/include/Student.hpp"

#include <vector>

int maxActiveLoansProfessor = 60;
int maxActiveLoansStudent = 3;

int main() {

  std::vector<LoanableItem> LoanableList;

  LoanableList.push_back(LoanableItem("Dom Casmurro", Status::UNAVAILABLE, "002"));
  LoanableList.push_back(LoanableItem("Clean Code", Status::UNAVAILABLE, "003"));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::UNAVAILABLE, "004"));
  LoanableList.push_back(LoanableItem("1984", Status::UNAVAILABLE, "005"));
  LoanableList.push_back(LoanableItem("Dom Casmurro", Status::AVAILABLE, "006"));
  LoanableList.push_back(LoanableItem("Clean Code", Status::AVAILABLE, "007"));
  LoanableList.push_back(LoanableItem("Animal Farm", Status::AVAILABLE, "008"));
  LoanableList.push_back(LoanableItem("1984", Status::AVAILABLE, "009"));
  LoanableList.push_back(LoanableItem("Dom Casmurro", Status::AVAILABLE, "010"));
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

  exhibitionList.push_back(ExhibitionItem(
      "Máscara Funerária Egípcia", Status::AVAILABLE, "E001", "Sala Egito Antigo"));
  exhibitionList.push_back(ExhibitionItem("Escultura Grega Clássica", Status::AVAILABLE,
                                          "E002", "Galeria Grécia"));
  exhibitionList.push_back(ExhibitionItem("Armadura Medieval", Status::AVAILABLE,
                                          "E003", "Sala Idade Média"));
  exhibitionList.push_back(ExhibitionItem("Pintura Renacentista", Status::AVAILABLE,
                                          "E004", "Galeria Renascimento"));
  exhibitionList.push_back(ExhibitionItem("Fóssil de Dinossauro", Status::AVAILABLE,
                                          "E005", "Sala de Paleontologia"));

  std::vector<AcademicMember *>
      AcademicUsers; // Mesmo vector para alunos e professores

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

  ///////////////////////////////////////  AÇÕES DE TESTE
  ////////////////////////////////////////////////////////
  AcademicUsers[0]->BorrowItem(LoanableList, "007");
  AcademicUsers[1]->BorrowItem(LoanableList,
                               "007"); // Livro já emprestado por outra pessoa
  AcademicUsers[1]->BorrowItem(LoanableList, "009");
  AcademicUsers[0]->ReturnItem(LoanableList, "007");
  AcademicUsers[1]->ReturnItem(LoanableList, "009");

  AcademicUsers[0]->BorrowItem(LoanableList,
                               "010"); // Limite de emprestimo por aluno
  AcademicUsers[0]->BorrowItem(LoanableList, "011");
  AcademicUsers[0]->BorrowItem(LoanableList, "012");
  AcademicUsers[0]->BorrowItem(LoanableList, "013");

  AcademicUsers[12]->BorrowItem(
      LoanableList,
      "007"); // Limite de emprestimo por professor maior que aluno
  AcademicUsers[12]->BorrowItem(LoanableList, "006");
  AcademicUsers[12]->BorrowItem(LoanableList, "008");
  AcademicUsers[12]->BorrowItem(LoanableList, "009");

  return 0;
}
