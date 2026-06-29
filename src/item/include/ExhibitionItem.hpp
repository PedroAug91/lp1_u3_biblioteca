#ifndef EXHIBITIONITEM_H
#define EXHIBITIONITEM_H

#include "PublicItem.hpp"
#include "Status.hpp"
#include <string>

class ExhibitionItem : public PublicItem {
public:
  void setDisplayArea(std::string s) override;

  void accessItem() override;

  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  ExhibitionItem(std::string n, Status s, std::string i,
                 std::string Da = "Área de exposição01");
};

#endif
