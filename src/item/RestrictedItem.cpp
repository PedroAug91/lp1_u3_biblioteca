#include "include/RestrictedItem.hpp"
#include "include/Status.hpp"
#include "include/VisitStatus.hpp"
#include <ctime>
#include <iostream>

void RestrictedItem::setStatus(Status) {
  std::cout << "O status de um RestrictedItem não pode ser alterado.\n";
}

void RestrictedItem::print() {
  Item::print();
  std::cout << "Este item é de acesso restrito.\n";
  std::cout << "Agendamentos disponíveis:\n";
  getAvailableAppointments();
}

void RestrictedItem::accessItem() {
  std::cout << this->name << "\n";
  std::cout << "Esse item não está disponível ao acesso do público, agende uma "
               "consulta particular\n";
}

static time_t getDayOffset(int daysFromNow) {
  time_t now = time(nullptr);
  return now + (daysFromNow * 86400);
}

void RestrictedItem::getAvailableAppointments() {
  std::cout << "--- Horários Disponíveis para: " << name << " ---\n";
  const char *slotLabels[NUM_SLOTS] = {"Manhã (5-6)", "Tarde (3-4)", "Noite (1-2)"};
  for (int d = 0; d < NUM_DAYS; ++d) {
    char buf[16];
    struct tm *tm_info = localtime(&AccessAppointments[d][0].dia);
    strftime(buf, sizeof(buf), "%d/%m", tm_info);
    std::cout << "  Dia " << (d + 1) << " (" << buf << "):\n";
    for (int s = 0; s < NUM_SLOTS; ++s) {
      std::cout << "    " << (s + 1) << ". " << slotLabels[s] << " - "
                << AccessAppointments[d][s].visitState << "\n";
    }
  }
}

bool RestrictedItem::ScheduleVisit(int day, int slot,
                                   const std::string &attendeeName,
                                   uint32_t attendeeMatricula) {
  if (day < 0 || day >= NUM_DAYS || slot < 0 || slot >= NUM_SLOTS)
    return false;

  Visit &v = AccessAppointments[day][slot];
  if (v.visitState != VisitStatus::AVAILABLE) {
    std::cout << "Este horário não está disponível.\n";
    return false;
  }

  v.visitState = VisitStatus::SCHEDULED;
  v.attendeeName = attendeeName;
  v.attendeeMatricula = attendeeMatricula;

  std::cout << "Visita agendada com sucesso!\n";
  v.print();
  return true;
}

RestrictedItem::RestrictedItem(std::string n, uint32_t i)
    : Item(n, Status::UNAVAILABLE, i) {
  for (int d = 0; d < NUM_DAYS; ++d) {
    for (int s = 0; s < NUM_SLOTS; ++s) {
      Horarios h = (s == 0) ? Horarios::M56
                  : (s == 1) ? Horarios::T34
                  : Horarios::N12;
      AccessAppointments[d][s] = Visit(getDayOffset(d), h, "", 0, VisitStatus::AVAILABLE);
    }
  }
}
