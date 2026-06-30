
#include "include/Professor.hpp"
#include <iostream>

#define MAX_ACTIVE_LOANS_PROFESSOR 60;

void Professor::print() {
  std::cout << "Nome: " << this->name << '\n'
            << "Matrícula: " << this->matricula << '\n'
            << "Empréstimos ativos: " << this->ActiveLoans << '\n'
            << "Empréstimos restantes: "
            << (this->maxActiveLoans - this->ActiveLoans) << '\n';
}

void Professor::RequestRestrictedAccess() {
  std::cout
      << "\n\nprimeiro mostra ao professor a tabela de horários disponíveis, "
         "depois o professor escolhe o horário.\n";
  std::cout
      << "depois opcionalmente o professor pode inserir até 5 outros objetos "
         "academic member para participarem da visita\n";
  std::cout << "Depois é emitido comprovante de agendamento \n\n";
}

Professor::Professor(std::string n, uint32_t m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
