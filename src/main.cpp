#include <iostream>
using namespace std;
#include <vector>

enum Status {
    BORROWED,
    AVAILABLE,
    UNAVAILABLE
};

class Item {
public:
    string id;
    string name;
    Status status;
    string responsibleId; // id da pessoa responsável por esse item (pode ser a propria biblioteca id = "0")

    Item(string n, Status s, string ir, string i) {
        name = n;
        id = i;
        status = s;
        responsibleId = ir;
    }
};

class Person {
public:
    string name;
    string id;

    Person(string n, string i) {
        name = n;
        id = i;
    }
};

class LibraryRepository {
public:
    string id = "001";
    vector<Item> items;
    vector<Person> users;

    /*
    virtual void addItem(Item item) = 0;
    virtual void removeItem(Item item) = 0;
    virtual void updateItem(Item item) = 0;
    virtual Item findItemByName(string name) = 0;
    */

    void listItems() {
        cout << "LISTANDO ITEMS \n";
        for (int c = 0; c < items.size(); c++) {
            cout << "NOME: " << items[c].name
                 << ", STATUS: " << items[c].status
                 << ", ID DO RESPONSÁVEL: " << items[c].responsibleId;
            cout << "\n";
        }
        cout << "\n\n";
    }

    void listUsers() {
        cout << "LISTANDO USUÁRIOS: \n";
        for (int c = 0; c < users.size(); c++) {
            cout << "NOME: " << users[c].name
                 << ", ID: " << users[c].id;
            cout << "\n";
        }
    }


    void lendItem(string  idPerson, string idItem , int days) {
        
        for(int d = 0 ; d < users.size() ; d++){
            
            if( users[d].id == idPerson ){
                
                for(int c = 0 ; c < items.size() ; c++){
                    
                    if( items[c].id == idItem ){
                        
                        if (items[c].status == AVAILABLE) {
                            items[c].responsibleId = users[d].id;
                            items[c].status = BORROWED;
                            cout << "Item " << items[c].name << " (" << items[c].id
                            << ") emprestado a " << users[d].name << "\n\n";
                        } else {
                            cout << "Item " << items[c].name << " (" << items[c].id
                            << ") Não disponível para empréstimo \n\n";
                        }
                    }
                }
        
            
                
            }
       
        }
    }
    
    void returnItem(string idPerson, string idItem, int days) {
    bool userExists  = false; // Ver se existem antes de executar
    bool itemExists = false; // Falta implementar !!!
    
    for (int d = 0; d < users.size(); d++) {

        if (users[d].id == idPerson) {

            for (int c = 0; c < items.size(); c++) {

                if (items[c].id == idItem) {

                    if (items[c].status == BORROWED) {

                        if (items[c].responsibleId == idPerson) {

                            items[c].responsibleId = "0";

                            items[c].status = AVAILABLE;

                            cout << "Item " << items[c].name
                                 << " (" << items[c].id
                                 << ") devolvido por " << users[d].name
                                 << "\n\n";

                        } else {
                            cout << " esse usuário não pegou esse item emprestado\n\n";
                        }

                    } else {
                        cout << "Item não foi emprestado \n\n";
                    }
                }
            }
        
        }
    }
}
};

int main() {
    vector<Item> items = {
        Item("Dom Casmurro", AVAILABLE, "0", "100"),
        Item("Dom Casmurro", AVAILABLE, "0", "101"),
        Item("Dom Casmurro", UNAVAILABLE, "0", "102"),
        Item("1984", AVAILABLE, "0", "200"),
        Item("1984", UNAVAILABLE, "0", "201"),
        Item("The Hobbit", AVAILABLE, "0", "300"),
        Item("Clean Code", AVAILABLE, "0", "401"),
        Item("Clean Code", UNAVAILABLE, "0", "402"),
        Item("Clean Code", AVAILABLE, "0", "403"),
        Item("Clean Code", AVAILABLE, "0", "404"),
        Item("Clean Code", AVAILABLE, "0", "405"),
        Item("Animal Farm", UNAVAILABLE, "0", "500")
    };

    vector<Person> users = {
        Person("Ana", "002"),
        Person("João", "003"),
        Person("Maria", "004"),
        Person("Pedro", "005")
    };

    LibraryRepository library;
    library.items = items;
    library.users = users;
    
    
    library.lendItem("002", "100", 20);
    library.lendItem("003", "100", 20); // Já emprestado
    library.lendItem("003", "101", 20); // Emprestando outra cópia



    library.listUsers();
    cout << "\n\n";
    library.listItems();

    library.returnItem("002", "100", 20);
    library.returnItem("002", "100", 20);


    return 0;
}
