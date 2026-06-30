#ifndef HORARIOS_H
#define HORARIOS_H

#include <string>

enum class Horarios : char {
  M56 = 'M',
  T34 = 'T',
  N12 = 'N'
};

inline std::string horariosToString(Horarios h) {
  switch (h) {
    case Horarios::M56: return "Manhã (5-6)";
    case Horarios::T34: return "Tarde (3-4)";
    case Horarios::N12: return "Noite (1-2)";
  }
  return "";
}

#endif
