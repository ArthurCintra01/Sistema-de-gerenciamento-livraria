#ifndef BOOKSTORE_H
#define BOOKSTORE_H

#include <iostream>
#include <vector>

namespace store{

class Book{  
    int qtd_;
    double preco_;
    std::string titulo_;
    std::string autor_;
    public:
        std::string titulo();
        void titulo(std::string n_titulo);
        std::string autor();
        void autor(std::string n_autor);
        int disponibilidade();
        void disponibilidade(int n_qtd);
        double preco();
        void preco(double n_preco);
        void imprime();
        Book();
        Book(std::string titulo,std::string autor,double preco,int qtd);
};

class Stock{
    std::vector <Book> books;
    public:
        std::vector<Book> vetor();
        void delete_book(std::string titulo,std::string autor);
        ~Stock();
        void fill_stock();
        void addbook(Book b);
        void change_book(int position,std::string titulo,std::string autor,double preco,int qtd);
        Book find_book(std::string titulo,std::string autor);
        int book_position(std::string titulo,std::string autor);
        int tamanho_stock();
        void savetofile();
        void imprime();
};

class User{
    protected:
    std::string nome_;
    std::string sobrenome_;
    std::string senha_;
    std::string permission_;
    double carteira_;
    public:
        User();
        User(std::string nome,std::string sobrenome,std::string permissao,double carteira);
        std::string nome();
        std::string sobrenome();
        std::string senha();
        void nome(std::string novo_nome);
        void sobrenome(std::string novo_sobrenome);
        void senha(std::string nova_senha);
        void permission(std::string permission);
        std::string permission();
        double carteira();
        void carteira(double nova_carteira);
        void imprime();
};

class Historico{
    std::vector <User> users;
    public:
        ~Historico();
        void change_user(int pos,std::string nome,std::string sobrenome,std::string senha,std::string permission,double carteira);
        void change_saldo(int pos,double saldo);
        std::vector<User> vetor();
        int user_pos(std::string nome,std::string senha);
        void fill_vector();
        void novo_usuario(User usuario);
        void save_to_file();
        User find_user(std::string nome,std::string senha);
        void imprime();
};

class Cliente:public User{
    public:
    void buybook(std::string titulo,std::string autor,Stock &stock,Cliente &cliente);
};

class Estudante:public User{
    public:
    void buybook(std::string titulo,std::string autor,Stock &stock,Estudante &estudante);
};
class Professor:public User{
    public:
    void buybook(std::string titulo,std::string autor,Stock &stock,Professor &professor);
};
class Funcionario:public User{
    public:
    void addbook(Book book,Stock stock);
};

}
#endif