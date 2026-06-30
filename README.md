# Sistema de Gestão de Biblioteca

Repositório destinado ao trabalho da unidade final da disciplina de Linguagem
de Programação 1 do semestre letivo 2026.1 ministrada pelo professor Jerffeson
Gomes Dutra.

---

## Escopo

Sistema para gerenciamento de acervo e usuários de uma biblioteca universitária.
Permite o cadastro de itens (livros, materiais de exposição, itens restritos),
o controle de empréstimos e devoluções, o agendamento de visitas guiadas a itens
restritos, e a aplicação de multas por atraso. Os dados são persistidos em
arquivos texto no diretório `library_db/`.

## Regras de Negócio

### Usuários

- Existem três perfis acadêmicos: **Aluno**,
  **Professor** e
  **Bibliotecário**.
- Visitantes externos podem consultar o acervo, mas não realizam empréstimos.
- Todos os usuários são persistidos em arquivos com extensão `.usr` no diretório
  `library_db/`.

### Itens do Acervo

- **Item Emprestável** (`.lnb`): pode ser retirado da biblioteca por alunos e
  professores. Cada empréstimo tem prazo de 14 dias corridos. Ao ser emprestado,
  o status muda para `BORROWED` e a área de exibição é alterada para
  "não está na biblioteca".
- **Item Restrito** (`.rst`): não sai da biblioteca. Professores podem agendar
  visitas em uma grade de 5 dias × 3 horários (manhã 5-6, tarde 3-4, noite 1-2).
- **Item de Exposição** (`.exb`): permanece sempre na biblioteca em uma área de
  exibição específica.

### Empréstimos e Devoluções

- Apenas o **Bibliotecário** pode realizar empréstimos e receber devoluções.
- Alunos e professores **não** podem emprestar ou devolver itens por conta
  própria.
- O sistema registra a data/hora do empréstimo (`borrowedAt`) e a data de
  vencimento (`dueDate = borrowedAt + 14 dias`).
- Ao devolver, o item volta ao status `AVAILABLE` e é enviado para o
  "depósito de devoluções".
- Cada usuário pode consultar seus empréstimos ativos e os dias restantes
  (ou em atraso) através da opção "Ver meus dados".

### Multas

- O Bibliotecário pode aplicar multas manuais informando a quantidade de dias
  em atraso. O valor é calculado a R$ 1,50 por dia.

### Visitantes

- Visitantes podem listar itens do acervo (todas as categorias) sem necessidade
  de cadastro ou login.

### Diagrama de Classes

O diagrama de classes completo está disponível em:
[`docs/class_diagram.mmd`](docs/class_diagram.mmd)

Para visualizá-lo, use o [Mermaid Live Editor](https://mermaid.live/) ou
qualquer ferramenta compatível com a sintaxe Mermaid.

## Autores

- [Caio Victor Fernandes Freire](https://github.com/caiovictor4884)
- [João Pedro Augusto da Silva](https://github.com/pedroaug91)
- [João Maria Mauricio](https://github.com/mauchair)
- [Matheus Dias](https://github.com/mateusnoites)
