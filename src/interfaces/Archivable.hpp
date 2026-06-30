#ifndef I_ARCHIVABLE_H
#define I_ARCHIVABLE_H

#include <string>

class Person;

class Archivable {
public:
	// person_id = matricula
	virtual bool create(Person *p_person) = 0;
	virtual bool read(std::string person_id) = 0;
	virtual bool update(std::string person_id) = 0;
	virtual bool remove(std::string person_id) = 0; 
};

#endif
