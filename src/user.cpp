#include <iostream>

#include "user.hpp"
#include "market.hpp"

Usuario::Usuario(){}

Usuario::Usuario(const string& nome, float saldo){
    this->nome = nome;
    this->saldo = saldo;
}

void Usuario::depositar(float valor){
    saldo += valor;
}

void Usuario::comprarAcao(Acao& acao, unsigned int quantidade){
    saldo -= acao.getPreco() * quantidade;
    carteira[acao] += quantidade;
}

void Usuario::venderAcao(Acao& acao, unsigned int quantidade){
    saldo += acao.getPreco() * quantidade;
    carteira[acao] -= quantidade;
    if(carteira[acao]==0){
        carteira.erase(acao);
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
