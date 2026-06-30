#ifndef I_PRINTABLE_H
#define I_PRINTABLE_H

class Printable {
public:
  virtual void print() = 0;
  virtual ~Printable() = default;
};

#endif
