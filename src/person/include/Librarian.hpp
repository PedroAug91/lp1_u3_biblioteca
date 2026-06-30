#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "AcademicMember.hpp"
#include "../../item/include/ExhibitionItem.hpp"
#include "../../item/include/LoanableItem.hpp"
#include "../../item/include/RestrictedItem.hpp"
#include <string>
#include <vector>

class Librarian : public AcademicMember {
public:
  static const int DefaultMaxActiveLoans = 30;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  void registerUser(std::vector<AcademicMember *> &users, const std::string &type,
                    const std::string &name, const std::string &matricula);

  void registerLoanableItem(std::vector<LoanableItem> &items, const std::string &name,
                            const std::string &id);

  void registerRestrictedItem(std::vector<RestrictedItem> &items, const std::string &name,
                              const std::string &id);

  void registerExhibitionItem(std::vector<ExhibitionItem> &items, const std::string &name,
                              const std::string &id);

  void lendItem(AcademicMember *user, std::vector<LoanableItem> &items,
                const std::string &itemId);

  void applyFine(AcademicMember *user, int daysLate);

  Librarian(std::string n, std::string m);
};

#endif
