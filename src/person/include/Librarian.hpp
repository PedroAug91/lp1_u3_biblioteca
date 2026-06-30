#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "AcademicMember.hpp"
#include <cstdint>
#include <string>

class Librarian : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 30;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void registerUser(const std::string &type, const std::string &name);

  void registerLoanableItem(const std::string &name);

  void registerRestrictedItem(const std::string &name);

  void registerExhibitionItem(const std::string &name);

  void lendItem(AcademicMember *user, uint32_t itemId);

  void receiveReturn(AcademicMember *user, uint32_t itemId);

  void applyFine(AcademicMember *user, int daysLate);

  Librarian(std::string n, uint32_t m);
};

#endif
