#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

using namespace std;

class Acao {
private:
    string empresa;
    string codigo;
    float valorAtual;

public:
    Acao();
    Acao(const string& empresa, const string& codigo, float valor);

    string getCodigo() const;
    
    string getEmpresa() const;

    float getPreco() const;

    void setPreco(float novoPreco);

    bool operator<(const Acao& other) const {
        return codigo < other.codigo;
    }
};

#endif