#ifndef RESTRICTEDITEM_H
#define RESTRICTEDITEM_H

#include "Horarios.hpp"
#include "Item.hpp"
#include "Visit.hpp"
#include <cstdint>
#include <string>

class RestrictedItem final : public Item {
public:
  static const int NUM_DAYS = 5;
  static const int NUM_SLOTS = 3;

  Visit AccessAppointments[NUM_DAYS][NUM_SLOTS];

  void setStatus(Status s) override;

  void accessItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void getAvailableAppointments();
  bool ScheduleVisit(int day, int slot, const std::string &attendeeName, uint32_t attendeeMatricula);

  RestrictedItem(std::string n, uint32_t i);
};

#endif
