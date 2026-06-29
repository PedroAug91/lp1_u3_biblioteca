#ifndef ITEM_H
#define ITEM_H

#include "../../interfaces/Archivable.hpp"
#include "../../interfaces/Printable.hpp"
#include "Status.hpp"
#include <string>

class Item : public Printable, public Archivable { // Classe abstrata
private:
  Status status;

public:
  std::string id;
  std::string name;

  virtual void accessItem() = 0;

  void print() override;

  Status getStatus() const;
  virtual void setStatus(Status s);

  Item(std::string n, Status s, std::string i);

  virtual ~Item();
};

#endif
