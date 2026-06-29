#ifndef PERSON_INTERFACE_H
#define PERSON_INTERFACE_H

#include "../../interfaces/Archivable.hpp"
#include "../../interfaces/Printable.hpp"

class Person : public Printable, public Archivable {
public:
  virtual void searchItem() = 0;
};

#endif
