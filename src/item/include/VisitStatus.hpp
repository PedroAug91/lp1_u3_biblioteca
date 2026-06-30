#ifndef VISITSTATUS_H
#define VISITSTATUS_H

#include <iostream>

enum class VisitStatus : char {
  AVAILABLE = 'A',
  SCHEDULED = 'S',
  UNAVAILABLE = 'U'
};

inline std::ostream &operator<<(std::ostream &os, VisitStatus vs) {
  switch (vs) {
    case VisitStatus::AVAILABLE:   os << "Disponível"; break;
    case VisitStatus::SCHEDULED:   os << "Agendado";   break;
    case VisitStatus::UNAVAILABLE: os << "Indisponível"; break;
  }
  return os;
}

#endif
