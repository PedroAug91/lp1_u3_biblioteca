
#include "include/Professor.hpp"
#include <iostream>

void Professor::RequestRestrictedAccess() {
  std::cout
      << "\n\nprimeiro mostra ao professor a tabela de horários disponíveis, "
         "depois o professor escolhe o horário.\n";
  std::cout
      << "depois opcionalmente o professor pode inserir até 5 outros objetos "
         "academic member para participarem da visita\n";
  std::cout << "Depois é emitido comprovante de agendamento \n\n";
}

Professor::Professor(std::string n, std::string m)
    : AcademicMember(n, m, DefaultMaxActiveLoans, 0) {}
