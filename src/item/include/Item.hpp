#ifndef ITEM_H
#define ITEM_H

#include "Status.hpp"
#include <string>

class Item { // Classe abstrata
private:
  Status status;

public:
  std::string id;
  std::string name;

  virtual void accessItem() = 0;

  Status getStatus() const;
  virtual void setStatus(Status s);

  Item(std::string n, Status s, std::string i);

  virtual ~Item();
};

#endif
