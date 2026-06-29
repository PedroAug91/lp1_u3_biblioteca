#ifndef EXHIBITIONITEM_H
#define EXHIBITIONITEM_H

#include "PublicItem.hpp"
#include "Status.hpp"
#include <string>

class ExhibitionItem : public PublicItem {
public:
  void setDisplayArea(std::string s) override;

  void accessItem() override;

  ExhibitionItem(std::string n, Status s, std::string i,
                 std::string Da = "Área de exposição01");
};

#endif
