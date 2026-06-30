#ifndef ITEM_H
#define ITEM_H

#include "../../interfaces/Archivable.hpp"
#include "../../interfaces/Printable.hpp"
#include "Status.hpp"
#include <cstdint>
#include <string>

class Item : public Printable, public Archivable {
private:
  Status status;

public:
  uint32_t id;
  std::string name;

  virtual void accessItem() = 0;

  void print() override;

  Status getStatus() const;
  virtual void setStatus(Status s);

  Item(std::string n, Status s, uint32_t i);

  virtual ~Item();
};

#endif
