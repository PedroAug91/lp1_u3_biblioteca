#include <iostream>
#include "include/Person.hpp"

int main() {
	std::cout << "Hello, world!\n";

	Person *p = new Person("Pedro", "71063254493");

	p->greet();

	return 0;
}
