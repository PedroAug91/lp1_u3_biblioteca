#include "include/Visit.hpp"
#include <ctime>
#include <iostream>

Visit::Visit()
  : dia(0), horario(Horarios::M56), attendeeName(""), attendeeMatricula(0),
    visitState(VisitStatus::AVAILABLE) {}

Visit::Visit(time_t d, Horarios h, const std::string &name, uint32_t mat, VisitStatus vs)
  : dia(d), horario(h), attendeeName(name), attendeeMatricula(mat), visitState(vs) {}

void Visit::print() const {
  char buf[64];
  struct tm *tm_info = localtime(&dia);
  strftime(buf, sizeof(buf), "%d/%m/%Y", tm_info);
  std::cout << "  Dia: " << buf
            << " | Horário: " << horariosToString(horario)
            << " | Status: " << visitState;
  if (visitState == VisitStatus::SCHEDULED && !attendeeName.empty())
    std::cout << " | Visitante: " << attendeeName << " (" << attendeeMatricula << ")";
  std::cout << "\n";
}
