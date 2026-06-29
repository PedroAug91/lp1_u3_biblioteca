#ifndef PUBLICITEM_H
#define PUBLICITEM_H

#include "Item.hpp"

class PublicItem : public Item {
private:
  std::string displayArea; // Código que indica local de exposição  do livro
public:
  std::string getDisplayArea() const;

  virtual void setDisplayArea(std::string s);

  void accessItem() override;

  PublicItem(std::string n, Status s, std::string i,
             std::string Da = "depósito01");
};

#endif
