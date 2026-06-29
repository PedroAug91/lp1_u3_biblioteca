#include "include/Person.hpp"
#include <iostream>

Person::Person(std::string name, std::string cpf) {
	this->name = name;
	this->cpf = cpf;
	this->id = ++Person::last_id;
}

void Person::greet() {
	std::cout << "Hello, my name is " << this->name << "!\n";
}
