#include "bookstore.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

namespace store{
//Book
Book::Book(std::string titulo,std::string autor,double preco,int qtd){
    titulo_=titulo;
    autor_=autor;
    preco_=preco;
    qtd_=qtd;
}
Book::Book(){
    titulo_="";
    autor_="";
    preco_=0;
    qtd_=0;
}
void Book::titulo(std::string n_titulo){
    titulo_=n_titulo;
}
void Book::autor(std::string n_autor){
    autor_=n_autor;
}
std::string Book::titulo(){
    return titulo_;
}
std::string Book::autor(){
    return autor_;
}
int Book::disponibilidade(){
    return qtd_;
}
void Book::disponibilidade(int n_qtd){
    qtd_=n_qtd;
}
double Book::preco(){
    return preco_;
}
void Book::preco(double n_preco){
    preco_=n_preco;
}
void Book::imprime(){
    std::cout<<"titulo: "<<titulo_<<std::endl;
    std::cout<<"autor: "<<autor_<<std::endl;
    std::cout<<"preco: "<<preco_<<" reais"<<std::endl;
    std::cout<<"disponibilidade: "<<qtd_<<std::endl;
}

//Stock
Stock::~Stock(){
    books.clear();
}

void Stock::fill_stock(){
    Book b;
    std::vector <std::string> col1 ,col2,col3,col4;
    std::string line;
    std::string campo;
    std::string filename="livros.txt";
    std::ifstream file;
    file.open(filename);
    if(file.is_open()){  
        while(std::getline(file,line)){
            std::stringstream s1(line);
            std::getline(s1,campo,',');
            col1.push_back(campo);
            std::getline(s1,campo,',');
            col2.push_back(campo);
            std::getline(s1,campo,',');
            col3.push_back(campo);
            std::getline(s1,campo,',');
            col4.push_back(campo);
            books.push_back(b);
            }             
        file.close();      
    }
    for(auto i=0;i<int(books.size());i++){
        books.at(i).titulo(col1.at(i));
        books.at(i).autor(col2.at(i));
        books.at(i).preco(std::stod(col3.at(i)));
        books.at(i).disponibilidade(std::stoi(col4.at(i)));
    } 
}
void Stock::addbook(Book b){
    Book temp;
    int x;
    temp=find_book(b.titulo(),b.autor());
    if(temp.disponibilidade()==0){
        books.push_back(b);
    }else{
        x=book_position(b.titulo(),b.autor());
        books.at(x).disponibilidade(books.at(x).disponibilidade()+1);
    }
    
}
void Stock::savetofile(){
    std::ofstream file;
    file.open("livros.txt");  
    for(auto i=0;i<int(books.size());i++){
        file<<books.at(i).titulo()<<","<<books.at(i).autor()<<","<<books.at(i).preco()<<","<<books.at(i).disponibilidade()<<std::endl;
    }
}
void Stock::change_book(int pos,std::string titulo,std::string autor,double preco,int qtd){
    books.at(pos).titulo(titulo);
    books.at(pos).autor(autor);
    books.at(pos).preco(preco);
    books.at(pos).disponibilidade(qtd);
    std::cout<<"detalhes modificados!"<<std::endl;
}
void Stock::imprime(){
    for(auto i=0;i<int(books.size());i++){
        books.at(i).imprime();
        std::cout<<std::endl;
    }
}
Book Stock::find_book(std::string titulo,std::string autor){
    for (auto i=0;i<int(books.size());i++){
        if(books.at(i).titulo() == titulo && books.at(i).autor()== autor){
            return books.at(i);
        }
    }
    Book b;
    b.disponibilidade(0);
    return b;
}
int Stock::book_position(std::string titulo,std::string autor){
    for (auto i=0;i<int(books.size());i++){
        if(books.at(i).titulo() == titulo && books.at(i).autor()== autor){
            return i;
        }
    }
    return -1;
}
int Stock::tamanho_stock(){
    return books.size();
}
std::vector<Book> Stock::vetor(){
    return books;
}
void Stock::delete_book(std::string titulo,std::string autor){
    books.at(book_position(titulo,autor)).disponibilidade(books.at(book_position(titulo,autor)).disponibilidade()-1);
}
//User 
User::User(){
    nome_="";
    sobrenome_="";
    carteira_=0;
    permission_="cliente";
}
User::User(std::string nome,std::string sobrenome,std::string permissao, double carteira){
    nome_=nome;
    sobrenome_=sobrenome;
    permission_=permissao;
    carteira_=carteira;
    senha_="1234";
}
void User::nome(std::string novo_nome){
    nome_=novo_nome;
}
void User::sobrenome(std::string novo_sobrenome){
    sobrenome_=novo_sobrenome;
}
void User::senha(std::string nova_senha){
    senha_=nova_senha;
}
void User::permission(std::string permission){
    permission_=permission;
}
std::string User::nome(){
    return nome_;
}
std::string User::sobrenome(){
    return sobrenome_;
}
std::string User::senha(){
    return senha_;
}
std::string User::permission(){
    return permission_;
}
double User::carteira(){
    return carteira_;
}
void User::carteira(double nova_carteira){
    carteira_=nova_carteira;
}
void User::imprime(){
    std::cout<<"Nome: "<<nome_<<std::endl;
    std::cout<<"Sobrenome: "<<sobrenome_<<std::endl;
    std::cout<<"Permissao: "<<permission_<<std::endl;
    std::cout<<"Senha: "<<senha_<<std::endl;
    std::cout<<"Carteira: "<<carteira_<<" reais"<<std::endl;
}
//Cliente
void Cliente::buybook(std::string titulo,std::string autor,Stock &stock,Cliente &cliente){
    Book book;
    book=stock.find_book(titulo,autor);
    if (book.disponibilidade()>0){
        if(cliente.carteira()>=book.preco()){
            std::cout<<"Compra permitida"<<std::endl;
            cliente.carteira(cliente.carteira()-book.preco());
            stock.delete_book(titulo,autor);
        }else{
            std::cout<<"Saldo insuficiente!"<<std::endl;
        }
    }else{
        std::cout<<"Livro fora de estoque"<<std::endl;
    }
}
//Estudante
void Estudante::buybook(std::string titulo,std::string autor,Stock &stock,Estudante &estudante){
    Book book;
    book=stock.find_book(titulo,autor);
    if (book.disponibilidade()>0){
        if(estudante.carteira()>=(book.preco()*0.9)){
            std::cout<<"Compra permitida"<<std::endl;
            estudante.carteira(estudante.carteira()-(book.preco()*0.9));
            stock.delete_book(titulo,autor);
        }else{
            std::cout<<"Saldo insuficiente!"<<std::endl;
        }
    }else{
        std::cout<<"Livro fora de estoque"<<std::endl;
    }
}
//Professor
void Professor::buybook(std::string titulo,std::string autor,Stock &stock,Professor &professor){
    Book book;
    book=stock.find_book(titulo,autor);
    if (book.disponibilidade()>0){
        if(professor.carteira()>=(book.preco()*0.8)){
            std::cout<<"Compra permitida"<<std::endl;
            professor.carteira(professor.carteira()-(book.preco()*0.8));
            stock.delete_book(titulo,autor);
        }else{
            std::cout<<"Saldo insuficiente!"<<std::endl;
        }
    }else{
        std::cout<<"Livro fora de estoque"<<std::endl;
    }
}
//funcionario
void Funcionario::addbook(Book b,Stock stock){
    stock.addbook(b);
}
//historico
Historico::~Historico(){
    users.clear();
}

void Historico::fill_vector(){
    User u;
    std::vector <std::string> col1 ,col2,col3,col4,col5;
    std::string line;
    std::string campo;
    std::string filename="Users.txt";
    std::ifstream file;
    file.open(filename);
    if(file.is_open()){  
        while(std::getline(file,line)){
            std::stringstream s1(line);
            std::getline(s1,campo,',');
            col1.push_back(campo);
            std::getline(s1,campo,',');
            col2.push_back(campo);
            std::getline(s1,campo,',');
            col3.push_back(campo);
            std::getline(s1,campo,',');
            col4.push_back(campo);
            std::getline(s1,campo,',');
            col5.push_back(campo);
            users.push_back(u);
        }             
        file.close();      
    }
    for(auto i=0;i<int(users.size());i++){
        users.at(i).nome(col1.at(i));
        users.at(i).sobrenome(col2.at(i));
        users.at(i).permission(col3.at(i));
        users.at(i).senha(col4.at(i));
        users.at(i).carteira(std::stod(col5.at(i)));
    }
}
User Historico::find_user(std::string nome,std::string senha){
    for (auto i=0;i<int(users.size());i++){
        if(users.at(i).nome() == nome && users.at(i).senha()== senha){
            return users.at(i);
        }
    }
    std::cout<<"Usuario nao encontrado entrando com conta padrao!"<<std::endl;
    User u1;
    return u1;
}
void Historico::novo_usuario(User usuario){
    users.push_back(usuario);
}
void Historico::imprime(){
    for(auto i=0;i<int(users.size());i++){
        users.at(i).imprime();
        std::cout<<std::endl;
    }
}
void Historico::save_to_file(){
    std::ofstream file;
    file.open("Users.txt");
    for(auto i=0;i<int(users.size());i++){
        file<<users.at(i).nome()<<","<<users.at(i).sobrenome()<<","<<users.at(i).permission()<<","<<users.at(i).senha()<<","<<users.at(i).carteira()<<std::endl;
    }
}
std::vector<User> Historico::vetor(){
    return users;
}
int Historico::user_pos(std::string nome,std::string senha){
    for (auto i=0;i<int(users.size());i++){
        if(users.at(i).nome() == nome && users.at(i).senha()== senha){
            return i;
        }
    }
    return -1;
}
void Historico::change_user(int pos,std::string nome,std::string sobrenome,std::string senha,std::string permission,double carteira){
    users.at(pos).nome(nome);
    users.at(pos).sobrenome(sobrenome);
    users.at(pos).senha(senha);
    users.at(pos).permission(permission);
    users.at(pos).carteira(carteira);
}
void Historico::change_saldo(int pos, double carteira){
    users.at(pos).carteira(carteira);
}
}