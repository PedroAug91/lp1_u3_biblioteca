#ifndef VISIT_H
#define VISIT_H

#include "Horarios.hpp"
#include "VisitStatus.hpp"
#include <cstdint>
#include <ctime>
#include <string>

class Visit {
public:
  time_t dia;
  Horarios horario;
  std::string attendeeName;
  uint32_t attendeeMatricula;
  VisitStatus visitState;

  Visit();
  Visit(time_t d, Horarios h, const std::string &name, uint32_t mat, VisitStatus vs);
  void print() const;
};

#endif
