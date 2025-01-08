#include "user.hpp"

Usuario::Usuario(){}

Usuario::Usuario(const string& nome, float saldo){
    this->nome = nome;
    this->saldo = saldo;
}

void Usuario::comprarAcao(Acao& acao, unsigned int quantidade){
    if(saldo >= acao.getPreco() * quantidade){
        saldo -= acao.getPreco() * quantidade;
        carteira[acao] += quantidade;
    }
    else{
        printf("Compra mal sucedida: Saldo insuficiente.");
    }
}
void Usuario::venderAcao(Acao& acao, unsigned int quantidade){
    if(carteira[acao] >= quantidade){
        saldo += acao.getPreco() * quantidade;
        carteira[acao] -= quantidade;
    }
    else{
        printf("Venda mal sucedida: Não possui essa quantidade de ações.");
    }
}

string Usuario::getNome() const{
    return nome;
}
    
map<Acao, unsigned int> Usuario::getCarteira() const{
    return carteira;
}

float Usuario::getSaldo() const{
    return saldo;
}
