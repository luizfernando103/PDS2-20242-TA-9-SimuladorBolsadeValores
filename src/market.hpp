#ifndef MARKET_H
#define MARKET_H

#include <string>
#include <vector>
#include <map>

#include "user.hpp"
#include "transaction.hpp"

using namespace std;

class Usuario;

class Ativo: public Acao {
private:
    Acao acao;
    int quantidade;
    int disponivel;
    vector<float> historicoPrecos;
public:
    Ativo();
    /*
    Ativo(const string& nome, const string& codigo, float valor, int quant)
    : Acao(nome, codigo, valor), quantidade(quant), disponivel(quant) {
        acao = Acao(nome, codigo, valor);
    }
    */
    Ativo(const string& nome, const string& codigo, float valor, int quant, vector<float>& historicoPrecos)
    : Acao(nome, codigo, valor), quantidade(quant), disponivel(quant), historicoPrecos(historicoPrecos){
        acao = Acao(nome, codigo, valor);
        historicoPrecos.push_back(valor);
    }
    int getQuantidade() const;
    int getDisponivel() const;

    Acao& getAcao();

    void setDisponivel(int quant);

    void atualizarPreco(float newPrice);
    const vector<float>& getHistorico() const;
};

class Mercado {
private:
    map<string, Ativo> ativos;
    map<string, Usuario> usuarios;
    vector<Transacao> operacoes;
public:
    Mercado();
    void addAtivo(string nome, string codigo, float valor, int quant, vector<float>& historico);
    void removeAtivo(Ativo& atv);
    void addUsuario(Usuario user);
    void removeUsuario(Usuario& user);
    bool Compra(string usuario, string codigo, int quantidade);

    bool Venda(string usuario, string codigo, int quantidade);

    void LerTransacao(string tempo, string usuario, string tipo, string codigo, int quantidade);

    void atualizarMercado();

    Ativo& getAtivo(const string& codigo);

    Usuario& getUsuario(const string& nome);

    map<string, Ativo>& getAtivos();
    
    map<string, Usuario>& getUsuarios();

    vector<Transacao>& getTransacoes();
};

#endif
