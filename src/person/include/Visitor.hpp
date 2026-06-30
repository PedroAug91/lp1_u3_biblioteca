#ifndef VISITOR_H
#define VISITOR_H

#include "Person.hpp"
#include <string>

class Visitor : public Person {
public:
  std::string name;

  void searchItem() override;
  void print() override;

  bool create(Person *p_person) override;
  bool read(std::string person_id) override;
  bool update(std::string person_id) override;
  bool remove(std::string person_id) override;

  Visitor(std::string n);
};

#endif
