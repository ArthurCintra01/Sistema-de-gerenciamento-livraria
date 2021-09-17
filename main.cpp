#include "bookstore.h"
#include <iostream>
#include <vector>
#include <string>

void menu_cliente(){
    std::cout << "\n\tMenu para clientes: \n"
    <<"\n 1 - Comprar livro" 
    <<"\n 2 - Procurar informacao de um livro"
    <<"\n 3 - Descontos"
    <<"\n 4 - Ver informacoes da conta"
    <<"\n 5 - Mudar detalhes da conta"
    <<"\n 6 - Ver livros disponiveis"
    <<"\n 7 - Sair do programa"
    <<"\n Entre sua escolha: ";
}
void menu_funcionario(){
    std::cout << "\n\tMenu para funcionarios: \n"
    <<"\n 1 - Adicionar livro" 
    <<"\n 2 - Ver stock"
    <<"\n 3 - Procurar informacao de um livro"
    <<"\n 4 - Editar detalhes de um livro"
    <<"\n 5 - Ver informacoes da conta"
    <<"\n 6 - Mudar detalhes da conta"
    <<"\n 7 - Historico de contas"
    <<"\n 8 - Sair do programa"
    <<"\n Entre sua escolha: ";
}

int main(){
    std::cout<<std::endl<<"<Use sempre letra minuscula e nao use acento no programa!>"<<std::endl;
    std::cout<<"<Use underline no lugar de espacos!>"<<std::endl;
    store::Book temp;
    store::Stock stock;
    stock.fill_stock();
    store::Historico historico;
    historico.fill_vector();  
    int x,y,escolha;
    std::string nome,sobrenome,permissao,senha,titulo,autor;
    double saldo;
    std::cout<<"Criar conta(0), Usar conta existente(1): ";
    std::cin>>x;
    store::User usuario;
    if(x==0){
        std::cout<<"Criando nova conta: "<<std::endl;
        std::cout<<"Nome: ";
        std::cin>>nome;
        std::cout<<"Sobrenome: ";
        std::cin>>sobrenome;
        std::cout<<"Permissao (cliente,professor,estudante,funcionario): ";
        std::cin>>permissao;
        std::cout<<"Senha: ";
        std::cin>>senha;
        std::cout<<"Saldo: ";
        std::cin>>saldo;
        usuario.nome(nome);
        usuario.sobrenome(sobrenome);
        usuario.permission(permissao);
        usuario.senha(senha);
        usuario.carteira(saldo);
        historico.novo_usuario(usuario);
        std::cout<<"Nova conta criada!"<<std::endl;
    }
    if(x!=0 && x!=1){
        std::cout<<"resposta invalida";
        exit(0);
    }
    std::cout<<"Login: "<<std::endl<<"Nome: ";
    std::cin>>nome;
    std::cout<<"Senha: ";       
    std::cin>>senha;
    std::cout<<std::endl;
    usuario=historico.find_user(nome,senha);
    std::cout<<"Seu saldo atual e: "<<usuario.carteira()<<std::endl;
    while(1){
        if(usuario.permission()=="cliente"){
            store::Cliente cliente{usuario};
            //mostrando menu
            menu_cliente();
            std::cin >> escolha;
            std::cout<<std::endl;
            switch (escolha) {
                case 1:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    cliente.buybook(titulo,autor,stock,cliente);
                    std::cout<<"Seu saldo novo e: "<<cliente.carteira()<<std::endl;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_saldo(y,cliente.carteira()); 
                    break;
                case 2:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    temp=stock.find_book(titulo,autor);
                    if(temp.disponibilidade()==0){
                        std::cout<<"Este livro nao esta disponivel!"<<std::endl;
                        break;
                    }else{
                        std::cout<<"Livro encontrado!";
                    }
                    std::cout<<std::endl;
                    temp.imprime();
                    break;
                case 3:
                    std::cout<<"Sua conta possui permissao de Cliente, nao oferece nenhum desconto!";
                    break;
                case 4:
                    std::cout<<"informacoes da conta: "<<std::endl;
                    cliente.imprime();
                    break;
                case 5:
                    std::cout<<"Novo nome: ";
                    std::cin>>nome;
                    std::cout<<"Novo sobrenome: ";
                    std::cin>>sobrenome;
                    std::cout<<"Nova permissao (cliente,professor,estudante,funcionario): ";
                    std::cin>>permissao;
                    std::cout<<"Nova senha: ";
                    std::cin>>senha;
                    std::cout<<"Novo saldo: ";
                    std::cin>>saldo;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_user(y,nome,sobrenome,senha,permissao,saldo);
                    std::cout<<"Detalhes da conta alterados!"<<std::endl;
                    std::cout<<"Reinicie o programa!"<<std::endl;
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                case 6:
                    stock.imprime();
                    break;
                case 7:
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                }
            }
        if (usuario.permission()=="estudante"){
            store::Estudante estudante{usuario};
            //mostrando menu
            menu_cliente();
            std::cin >> escolha;
            std::cout<<std::endl;
            switch (escolha) {
                case 1:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    estudante.buybook(titulo,autor,stock,estudante);
                    std::cout<<"Seu saldo novo e: "<<estudante.carteira()<<std::endl;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_saldo(y,estudante.carteira()); 
                    break;
                case 2:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    temp=stock.find_book(titulo,autor);
                    if(temp.disponibilidade()==0){
                        std::cout<<"Este livro nao esta disponivel!"<<std::endl;
                        break;
                    }else{
                        std::cout<<"Livro encontrado!";
                    }
                    std::cout<<std::endl;
                    temp.imprime();
                    break;
                case 3:
                    std::cout<<"Sua conta possui permissao de estudante te dando 10 por cento de desconto em todos os livros!";
                    break;
                case 4:
                    std::cout<<"informacoes da conta: "<<std::endl;
                    estudante.imprime();
                    break;
                case 5:
                    std::cout<<"Novo nome: ";
                    std::cin>>nome;
                    std::cout<<"Novo sobrenome: ";
                    std::cin>>sobrenome;
                    std::cout<<"Nova permissao (cliente,professor,estudante,funcionario): ";
                    std::cin>>permissao;
                    std::cout<<"Nova senha: ";
                    std::cin>>senha;
                    std::cout<<"Novo saldo: ";
                    std::cin>>saldo;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_user(y,nome,sobrenome,senha,permissao,saldo);
                    std::cout<<"Detalhes da conta alterados!"<<std::endl;
                    std::cout<<"Reinicie o programa!"<<std::endl;
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                case 6:
                    stock.imprime();
                    break;
                case 7:
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                }
            }
        if (usuario.permission()=="professor"){
            store::Professor professor{usuario};
            //mostrando menu
            menu_cliente();
            std::cin >> escolha;
            std::cout<<std::endl;
            switch (escolha) {
                case 1:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    professor.buybook(titulo,autor,stock,professor);
                    std::cout<<"Seu saldo novo e: "<<professor.carteira()<<std::endl;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_saldo(y,professor.carteira()); 
                    break;
                case 2:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    temp=stock.find_book(titulo,autor);
                    if(temp.disponibilidade()==0){
                        std::cout<<"Este livro nao esta disponivel!"<<std::endl;
                        break;
                    }else{
                        std::cout<<"Livro encontrado!";
                    }
                    std::cout<<std::endl;
                    temp.imprime();
                    break;
                case 3:
                    std::cout<<"Sua conta possui permissao de professor te dando 20 por cento de desconto em todos os livros!";
                    break;
                case 4:
                    std::cout<<"informacoes da conta: "<<std::endl;
                    professor.imprime();
                    break;
                case 5:
                    std::cout<<"Novo nome: ";
                    std::cin>>nome;
                    std::cout<<"Novo sobrenome: ";
                    std::cin>>sobrenome;
                    std::cout<<"Nova permissao (cliente,professor,estudante,funcionario): ";
                    std::cin>>permissao;
                    std::cout<<"Nova senha: ";
                    std::cin>>senha;
                    std::cout<<"Novo saldo: ";
                    std::cin>>saldo;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_user(y,nome,sobrenome,senha,permissao,saldo);
                    std::cout<<"Detalhes da conta alterados!"<<std::endl;
                    std::cout<<"Reinicie o programa!"<<std::endl;
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                case 6:
                    stock.imprime();
                    break;
                case 7:
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                }
        }
        
        if(usuario.permission()=="funcionario"){
            store::Funcionario funcionario{usuario};
            //mostrando menu de funcionario
            menu_funcionario();
            std::cin >> escolha;
            std::cout<<std::endl;
            switch (escolha){
                case 1:
                //adicionando livro
                    double preco;
                    int qtd;
                    std::cout<<std::endl;
                    std::cout<<"Adicionando livro: "<<std::endl;
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    temp.titulo(titulo);
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    temp.autor(autor);
                    std::cout<<"preco do livro: ";
                    std::cin>>preco;
                    temp.preco(preco);
                    std::cout<<"quantidade de livro: ";
                    std::cin>>qtd;
                    temp.disponibilidade(qtd);
                    stock.addbook(temp);
                    break;
                case 2:
                //mostrando stock
                    stock.imprime();
                    break;
                case 3:
                    std::cout<<"titulo do livro: ";
                    std::cin>>titulo;
                    std::cout<<"autor do livro: ";
                    std::cin>>autor;
                    temp=stock.find_book(titulo,autor);
                    if(temp.disponibilidade()==0){
                        std::cout<<"Este livro nao esta disponivel!"<<std::endl;
                        break;
                    }else{
                        std::cout<<"Livro encontrado!";
                    }
                    std::cout<<std::endl;
                    temp.imprime();
                    break;
                case 4:
                    std::cout<<"Qual livro deseja alterar?"<<std::endl;
                    std::cout<<"Titulo: ";
                    std::cin>>titulo;
                    std::cout<<"Autor: ";
                    std::cin>>autor;
                    x=stock.book_position(titulo,autor);
                    if(x>-1){
                        std::cout<<"Livro Encontrado!"<<std::endl;
                        std::cout<<"Alterando dados: "<<std::endl;
                        std::cout<<"Novo titulo: ";
                        std::cin>>titulo;
                        std::cout<<"Novo Autor: ";
                        std::cin>>autor;
                        std::cout<<"Novo Preco: ";
                        std::cin>>preco;
                        std::cout<<"Nova Quantidade: ";
                        std::cin>>qtd;
                        stock.change_book(x,titulo,autor,preco,qtd);
                        break;
                    }else{
                        std::cout<<"livro nao encontrado!"<<std::endl;
                        break;
                    }
                case 5:
                    std::cout<<"informacoes da conta: "<<std::endl;
                    funcionario.imprime();
                    break;
                case 6:
                    std::cout<<"Novo nome: ";
                    std::cin>>nome;
                    std::cout<<"Novo sobrenome: ";
                    std::cin>>sobrenome;
                    std::cout<<"Nova permissao (cliente,professor,estudante,funcionario): ";
                    std::cin>>permissao;
                    std::cout<<"Nova senha: ";
                    std::cin>>senha;
                    std::cout<<"Novo saldo: ";
                    std::cin>>saldo;
                    y=historico.user_pos(usuario.nome(),usuario.senha());
                    historico.change_user(y,nome,sobrenome,senha,permissao,saldo);
                    std::cout<<"Detalhes da conta alterados!"<<std::endl;
                    std::cout<<"Reinicie o programa!"<<std::endl;
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
                case 7:
                    historico.imprime();
                    break;
                case 8:
                    historico.save_to_file();
                    stock.savetofile();
                    exit(0);
            }
        }
    }
    return 0;
}