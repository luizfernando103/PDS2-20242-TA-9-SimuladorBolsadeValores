#ifndef USER_H
#define USER_H

#include <string>
#include <map>
#include "stock.hpp"
#include "market.hpp"

using namespace std;

class Mercado;

class Usuario {
private:
    string nome;
    float saldo;
    map<Acao, unsigned int> carteira;
public:
    Usuario();
    
    Usuario(const string& nome, float saldo);

    void depositar(float valor);

    void comprarAcao(Acao& acao, unsigned int quantidade);

    void venderAcao(Acao& acao, unsigned int quantidade);

    string getNome() const;
    
    map<Acao, unsigned int> getCarteira() const;

    float getSaldo() const;
};

#endif
