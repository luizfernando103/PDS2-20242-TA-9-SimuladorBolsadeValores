#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <vector>
#include <map>

#include "user.hpp"

using namespace std;

class Ativo: public Acao {
private:
    int quantidade;
    int disponivel;

public:
    Ativo();
    Ativo(const string& nome, const string& codigo, float valor, int quant)
    : Acao(nome, codigo, valor), quantidade(quant), disponivel(quant) {}
};

class Mercado {
private:
    map<string, Ativo> ativos;
    map<string, Usuario> usuarios;
public:
   Mercado();
   void addAcao(string nome, string codigo, float valor, int quant);
   void addUsuario(Usuario user);

   void atualizarMercado();

   Acao& getAcao(const string& codigo);

   Usuario& getUsuario(const string& nome);
};

#endif
