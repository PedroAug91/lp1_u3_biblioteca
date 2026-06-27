#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
	private:
		std::string name;
		std::string cpf;
		inline static int8_t last_id = 0;
	public:
		int8_t id;

		Person(std::string name, std::string cpf);
		void greet();
};

#endif
