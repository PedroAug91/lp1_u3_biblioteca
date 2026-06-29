#include <iostream>
using namespace std; 
#include <vector>
#include <ctime>

time_t agora = time(nullptr); // Determina o tempo atual
//  time_t agora = time(nullptr) + i * 24 * 60 * 60 // Serve para testar avançando o tempo alguns dias 
// Necessário para implementar o prazo dos empréstimos

enum Status {
    BORROWED,
    AVAILABLE,
    UNAVAILABLE
};

int maxActiveLoansProfessor = 60;
int maxActiveLoansStudent = 3;


enum Horarios{
    M56,
    T34,
    N12
};





///////////////////////CLASSES ITEMS ///////////////////////////////////////////////

class Item { // Classe abstrata 
private:
    Status status;
public:
    string id;
    string name;

    
    virtual void accessItem() = 0;    
    

    Status getStatus() const {
        return status;
    }

    virtual void setStatus(Status s) {
        status = s;
    }

    Item(string n, Status s, string i) {
        name = n;
        id = i;
        setStatus(s);
        
    }
    

    virtual ~Item() {};
    
    

};



class PublicItem : public Item{
    private: 
       string DisplayArea; // Código que indica local de exposição  do livro
    public:
    string getDisplayArea() const {
        return DisplayArea;
    }

    virtual void setDisplayArea(string s) {
        DisplayArea = s;
    }
    
    
    
    void accessItem ()  override{
        cout << "DESCRIÇÃO DO ITEM: \n" ;
        cout << "nome: " << name<< "\n";
        cout << "código de identificação: " << id<< "\n";
        cout<< "O item pode ser visto livremente em" << getDisplayArea()<<"\n";
        cout << "ESTE ITEM É : Lorem Ipsum is simply dummy text of the printing and typesetting\name industry. Lorem Ipsum has been the industry's standard dummy text e\nver since 1966, when designers at Letraset and James Mosley, t\nhe librarian ";
        cout << "\n\n";
}
    PublicItem( string n, Status s, string i, string Da= "depósito01" ) : Item( n,  s,  i){
        setDisplayArea(Da);
    }
};

class LoanableItem : public PublicItem{
    public:
    string responsibleId;
    
        void accessItem ()  override{
        cout << "DESCRIÇÃO DO ITEM: \n" ;
        cout << "nome: " << name<< "\n";
        cout << "código de identificação: " << id<< "\n";
        cout<< "O item pode ser visto livremente em" << getDisplayArea()<<"\n";
        cout << "ESTE ITEM É : Lorem Ipsum is simply dummy text of the printing and typesetting\name industry. Lorem Ipsum has been the industry's standard dummy text e\nver since 1966, when designers at Letraset and James Mosley, t\nhe librarian ";
        cout << "\n\n";
    }
 
    LoanableItem( string n, Status s,  string i, string Da ="depósito01"  , string rid = "0") : PublicItem( n, s, i, Da) {
  
        responsibleId = rid;
    }
};

class ExhibitionItem : public PublicItem{
    public:
     void setDisplayArea(string s) override {
        cout << "Essa exposiçao não pode ser retirada de seu local:"<< getDisplayArea();
    }
    
     void accessItem ()  override{
        cout << "DESCRIÇÃO DO ITEM: \n" ;
        cout << "nome: " << name<< "\n";
        cout << "código de identificação: " << id<< "\n";
        cout<< "O item pode ser visto livremente em" << getDisplayArea()<<"\n";
        cout << "ESTE ITEM É : informações sobre a exposiçãoinformações sobre a exposição\ninformações sobre a exposiçãotandard dummy text e\nver since 1informações sobre a exposiçãoet and James Mosley, t\nhe librarian ";
        cout << "\n\n";
    }
    
        ExhibitionItem( string n, Status s,  string i, string Da ="Área de exposição01"  ) : PublicItem( n, s, i, Da) {
  
    }
    
};


//////////////////////////////////CLASSES PERSON ///////////////////////////////////

class Person { // interface
public:

    virtual void searchItem() = 0;
};

class AcademicMember :public Person{// classe abstrata
public:
    string name;
    string matricula; 
    int maxActiveLoans;
    int ActiveLoans;

    void searchItem() override{
        cout <<"procurando items\n\n";
    }
    
void BorrowItem(vector<LoanableItem>& loanableList, string itemId)  {

    for (int i = 0; i < loanableList.size(); i++) {

        if (loanableList[i].id == itemId) {

            if (loanableList[i].getStatus() == AVAILABLE) {
                if(ActiveLoans< maxActiveLoans){
                    loanableList[i].setStatus(BORROWED);
                    loanableList[i].responsibleId = matricula;
                    loanableList[i].setDisplayArea("não está na biblioteca");
                    ActiveLoans++;
                cout << "Item "
                     << loanableList[i].name
                     << " emprestado para "
                     << name << "que tem " <<  ActiveLoans << " empréstimo(s) ativos"<<endl;
                     
                }
                else{
                    cout << "usuário atingiu quantidade máxima de empréstimos: " << ActiveLoans <<"\n\n";
                }
            }
            else {

                cout << "Item indisponível." << endl;
            }

            return;
        }
    }

    cout << "Item não encontrado." << endl;
}

void ReturnItem(vector<LoanableItem>& loanableList, string itemId) {

    for (int c = 0; c < loanableList.size(); c++) {

        if (loanableList[c].id == itemId) {

            if (loanableList[c].getStatus() == BORROWED) {

                if (loanableList[c].responsibleId == matricula) {

                    loanableList[c].responsibleId = "0";
                    loanableList[c].setStatus(AVAILABLE) ;
                    loanableList[c].setDisplayArea("depósito de devoluções");
                    ActiveLoans--;
                    cout << "Item "
                         << loanableList[c].name
                         << " (" << loanableList[c].id
                         << ") devolvido por "
                         << name
                         << " que tem " <<  ActiveLoans << " empréstimo(s) ativos"<<endl;

                } else {

                    cout << "Esse usuário não pegou esse item emprestado.\n\n";

                }

            } else {

                cout << "O item não está emprestado.\n\n";

            }

            return;
        }
    }

    cout << "Item não encontrado.\n\n";
}
    
    
    AcademicMember( string n , string m, int maxLoans, int loans){
        name = n;
        matricula = m; 
        maxActiveLoans= maxLoans;
        ActiveLoans = loans;
    }
    
};

class Student : public AcademicMember{
    public:
    static const int DefaultMaxActiveLoans = 3;;
          // O que um estudante pode fazer que um professor não 
        Student(string n, string m ): AcademicMember(n, m , DefaultMaxActiveLoans , 0) {
        }
};


class Visit{
    time_t dia ; 
    Horarios horario;
    AcademicMember* participantes[5];
};

class RestrictedItem final :public Item{ //final para evitar que uma classe filha mude os métodos que restringem o acesso 
    public: 
    
    void setStatus(Status s) override {
        cout << "O status de um RestrictedItem não pode ser alterado.\n";
    }
    
    void accessItem() override {
        cout << name << "\n";
        cout << "Esse item não está disponível ao acesso do público, agende uma consulta particular\n";
    }
    
    Visit   AccessAppointments[4][2] ; // Para os 5 dias seguintes, para 3 horários em cada um desses dias 
    
    
    
    void RestrictedAccess(){ // algo para horários disponíveis e selecionar um bibliotecário como curador
        cout<<"algum texto de informações restritas";
    }
    
    RestrictedItem(string n, string i): Item(n, UNAVAILABLE, i){}
};

class Professor : public AcademicMember{
    public:
   static const int DefaultMaxActiveLoans = 10;
   
    void RequestRestrictedAccess(){
        cout<< "\n\nprimeiro mostra ao professor a tabela de horários disponíveis, depois o professor escolhe o horário.\n";
        cout<< "depois opcionalmente o professor pode inserir até 5 outros objetos academic member para participarem da visita\n";
        cout<< "Depois é emitido comprovante de agendamento (basicamente imprimir o struct)\n\n";
    }


    Professor(string n, string m ): AcademicMember(n, m,  DefaultMaxActiveLoans, 0)  {
    }
    
    
};






int main(){
    
////////////////////////VETORES DE OBJETOS DE TESTE ////////////////////////////////

vector<LoanableItem> LoanableList;

LoanableList.push_back(LoanableItem("Dom Casmurro", UNAVAILABLE , "002"));
LoanableList.push_back(LoanableItem("Clean Code", UNAVAILABLE , "003"));
LoanableList.push_back(LoanableItem("Animal Farm", UNAVAILABLE , "004"));
LoanableList.push_back(LoanableItem("1984", UNAVAILABLE , "005"));
LoanableList.push_back(LoanableItem("Dom Casmurro", AVAILABLE , "006"));
LoanableList.push_back(LoanableItem("Clean Code", AVAILABLE , "007"));
LoanableList.push_back(LoanableItem("Animal Farm", AVAILABLE , "008"));
LoanableList.push_back(LoanableItem("1984", AVAILABLE , "009"));
LoanableList.push_back(LoanableItem("Dom Casmurro", AVAILABLE , "010"));
LoanableList.push_back(LoanableItem("Clean Code", AVAILABLE , "011"));
LoanableList.push_back(LoanableItem("Animal Farm", AVAILABLE , "012"));
LoanableList.push_back(LoanableItem("1984", AVAILABLE , "013"));

vector<RestrictedItem> restrictedList;

restrictedList.push_back(RestrictedItem("Enciclopédia Britânica", "R001"));
restrictedList.push_back(RestrictedItem("Atlas Mundial", "R002"));
restrictedList.push_back(RestrictedItem("Dicionário Oxford", "R003"));
restrictedList.push_back(RestrictedItem("Manuscritos Históricos", "R004"));
restrictedList.push_back(RestrictedItem("Coleção de Mapas Antigos", "R005"));

vector<ExhibitionItem> exhibitionList;

exhibitionList.push_back(ExhibitionItem("Máscara Funerária Egípcia", AVAILABLE, "E001", "Sala Egito Antigo"));
exhibitionList.push_back(ExhibitionItem("Escultura Grega Clássica", AVAILABLE, "E002", "Galeria Grécia"));
exhibitionList.push_back(ExhibitionItem("Armadura Medieval", AVAILABLE, "E003", "Sala Idade Média"));
exhibitionList.push_back(ExhibitionItem("Pintura Renacentista", AVAILABLE, "E004", "Galeria Renascimento"));
exhibitionList.push_back(ExhibitionItem("Fóssil de Dinossauro", AVAILABLE, "E005", "Sala de Paleontologia"));


    
vector<AcademicMember*> AcademicUsers; //Mesmo vector para alunos e professores

AcademicUsers.push_back(new Student("Ana", "002"));
AcademicUsers.push_back(new Student("João", "003"));
AcademicUsers.push_back(new Student("gustavo", "004"));
AcademicUsers.push_back(new Student("João", "005"));
AcademicUsers.push_back(new Student("Ana", "006"));
AcademicUsers.push_back(new Student("Carlos", "007"));
AcademicUsers.push_back(new Professor("gustavo", "008"));
AcademicUsers.push_back(new Professor("João", "009"));
AcademicUsers.push_back(new Student("Ana", "010"));
AcademicUsers.push_back(new Student("Carlos", "011"));
AcademicUsers.push_back(new Professor("Carlos", "012"));
AcademicUsers.push_back(new Professor("Mariana", "013"));
AcademicUsers.push_back(new Professor("Roberto", "014"));
   
   
   
   
   ///////////////////////////////////////  AÇÕES DE TESTE /////////////////////////////////////////////////////
AcademicUsers[0]->BorrowItem(LoanableList, "007"); 
AcademicUsers[1]->BorrowItem(LoanableList, "007");  // Livro já emprestado por outra pessoa
AcademicUsers[1]->BorrowItem(LoanableList, "009"); 
AcademicUsers[0]->ReturnItem(LoanableList, "007");
AcademicUsers[1]->ReturnItem(LoanableList, "009");

AcademicUsers[0]->BorrowItem(LoanableList, "010"); //Limite de emprestimo por aluno
AcademicUsers[0]->BorrowItem(LoanableList, "011"); 
AcademicUsers[0]->BorrowItem(LoanableList, "012"); 
AcademicUsers[0]->BorrowItem(LoanableList, "013"); 

AcademicUsers[12]->BorrowItem(LoanableList, "007"); //Limite de emprestimo por professor maior que aluno
AcademicUsers[12]->BorrowItem(LoanableList, "006"); 
AcademicUsers[12]->BorrowItem(LoanableList, "008"); 
AcademicUsers[12]->BorrowItem(LoanableList, "009"); 

    return 0;
}
