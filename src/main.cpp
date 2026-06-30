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

enum VisitStatus {
    SCHEDULEDv,
    AVAILABLEv,
    UNAVAILABLEv
};


int maxActiveLoansProfessor = 60;
int maxActiveLoansStudent = 3;


enum Horarios{
    M56,
    T34,
    N12
};






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
        cout << "ESTE ITEM É : Lorem Ipsum is simply dummy text of the printing and typesetting\n ame industry. Lorem Ipsum has been the industry's standard dummy text e\nver since 1966, when designers at Letraset and James Mosley, t\nhe librarian ";
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

class Person { // interface
public:

    virtual void searchItem(vector<Item*>& ItemList) = 0;
};


class Visitor : public Person{
    public:
    string name;
    
    void searchItem(vector<Item*>& ItemList) {
        cout<<"\nlistando todos os itens da biblioteca: \n\n";
        for(int c = 0  ; c < ItemList.size(); c++){
            cout<< "--> "<< ItemList[c]->name<< "\n";
        }
        cout<<"\n\n";
    }
    
    Visitor( string n  ){
        name = n;
    }
};

class AcademicMember :public Person{// classe abstrata
public:
    string name;
    string matricula; 
    int maxActiveLoans;
    int ActiveLoans;

    void searchItem(vector<Item*>& ItemList) {
        cout<<"\nlistando todos os itens da biblioteca: \n\n";
        for(int c = 0  ; c < ItemList.size(); c++){
            cout<< "--> "<< ItemList[c]->name<< "\n";
        }
        cout<<"\n\n";
    }
    
virtual void BorrowItem(vector<LoanableItem>& loanableList, string itemId)  {

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

virtual void ReturnItem(vector<LoanableItem>& loanableList, string itemId) {

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

class Visit final{
    public:
    time_t dia ; 
    Horarios horario;
    AcademicMember* Attendee;
    VisitStatus VisitState;
};

class RestrictedItem final : public Item {
public:

    Visit AccessAppointments[5][3]; // 4 dias, 3 horários

    void setStatus(Status s) override {
        cout << "O status de um RestrictedItem não pode ser alterado.\n";
    }

    void accessItem() override {
        cout << name << "\n";
        cout << "Esse item não está disponível ao acesso do público, agende uma consulta particular\n";
    }

    void printHorario(Horarios h) {
        switch (h) {
            case M56: cout << "09:00 - 11:00"; break;
            case T34: cout << "14:00 - 16:00"; break;
            case N12: cout << "17:00 - 19:00"; break;
        }
    }

    void getAvailableAppointments() {
        cout << "ESSES SÃO OS HORÁRIOS DISPONÍVEIS\n";

        for (int d = 0; d < 5; d++) {
            for (int h = 0; h < 3; h++) {

                if (AccessAppointments[d][h].VisitState == AVAILABLEv) {

                    time_t t = AccessAppointments[d][h].dia;
                    tm* data = localtime(&t);

                    cout << "Dia: " << data->tm_mday << "/"
                         << data->tm_mon + 1 << "/"
                         << data->tm_year + 1900 << "\n";

                    printHorario(AccessAppointments[d][h].horario);
                    cout << "\n\n";
                }
            }
        }
    }

    void ScheduleVisit(int D, int P, string Pname, string Pmatricula ){
        time_t base = time(nullptr);
        if(AccessAppointments[D][P].VisitState == AVAILABLEv){
            
        
        AccessAppointments[D][P].VisitState = SCHEDULEDv; 
        cout << "\n-----------------------------------------------  ";
        cout << "\n\n COMPROVANTE DE AGENDAMENTO:\n\n";
        cout << "Acesso ao item:"<< name << "(" << id << ")\n";
        cout << "Professor: " << Pname << "(" << Pmatricula << ")\n";
        cout << "Horário: ";
        printHorario(AccessAppointments[D][P].horario);
        cout<<" \n Data: ";
        tm* data = localtime(&AccessAppointments[D][P].dia);
        cout << data->tm_mday << "/"
        << data->tm_mon + 1 << "/"
        << data->tm_year + 1900 << "\n";
        cout << "\n-----------------------------------------------  ";
        }else{
            cout << "Horário não disponível, tente agendar em outro";
        }
    }

    RestrictedItem(string n, string i) : Item(n, UNAVAILABLE, i) {

        time_t base = time(nullptr);

        for (int d = 0; d < 5; d++) {
            for (int h = 0; h < 3; h++) { 

                AccessAppointments[d][h].VisitState = AVAILABLEv;
                AccessAppointments[d][h].dia = base + d * 24 * 60 * 60;
                AccessAppointments[d][h].horario = (Horarios)h;
            }
        }
    }
};




class Professor : public AcademicMember{
    public:
   static const int DefaultMaxActiveLoans = 10;
   
    void RequestRestrictedAccess(vector<RestrictedItem>& restrictedList){
        string IdItemRestrito;
        
        
        cout<< "insira o id do item restrito que deseja acessar ";
        cin >> IdItemRestrito;
        
        
        for(int c = 0 ; c < restrictedList.size(); c++){
            if(IdItemRestrito ==restrictedList[c].id ){
                cout<< "NOME DO ITEM: " << restrictedList[c].name<< "\n\n";
                restrictedList[c].getAvailableAppointments(); // Método que mostra os horários disponíveis para visitar 
                
                for (int d = 0; d < 5; d++) {
                    cout << "digite "<< d<<   " para";
                    time_t t = time(nullptr) + d * 24 * 60 * 60;
        
                    tm *data = localtime(&t);
        
                    cout << data->tm_mday << "/"
                     << data->tm_mon + 1 << "/"
                     << data->tm_year + 1900 << endl;
                }
                
            int day; 
            int period;
            cin>> day;
            cout << "digite 0 para 09:00 - 11:00 \n digite 1 para 14:00 -  16:00 \n digite 2 para 17:00 - 19:00 \n";
            cin>>  period;
                    
            restrictedList[c].ScheduleVisit(day, period, this->name, this->matricula);
                    
                
               break;
            }
        }
    


        
        
    }


    Professor(string n, string m ): AcademicMember(n, m,  DefaultMaxActiveLoans, 0)  {
    }
    
    
};




int main(){

    cout << "START\n";
    
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

vector<Visitor> VisitorList;

VisitorList.push_back(Visitor("Lucas"));
VisitorList.push_back(Visitor("Marina"));
VisitorList.push_back(Visitor("Pedro"));



vector<Item*> ItemList; ////////////////////////COMBINANDO TODOS OS ITENS EM UM UNICO VETOR

for (int i = 0; i < LoanableList.size(); i++) {
    ItemList.push_back(&LoanableList[i]);
}
for (int i = 0; i < restrictedList.size(); i++) {
    ItemList.push_back(&restrictedList[i]);
}
for (int i = 0; i < exhibitionList.size(); i++) {
    ItemList.push_back(&exhibitionList[i]);
}




   
   
   
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


VisitorList[0].searchItem(ItemList); // O acesso dos visitantes a pesquisar os livros se limita ao nome

AcademicUsers[1]->searchItem(ItemList); // Maior nível de acesso a informação

Professor* professor = dynamic_cast<Professor*>(AcademicUsers[12]);

if(professor != nullptr) {
    professor->RequestRestrictedAccess(restrictedList);
}else{
    cout << "Esse usuário não é um professor.\n";
}



    return 0;
}
