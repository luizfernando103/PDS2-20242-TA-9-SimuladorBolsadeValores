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
    vector<float> historicoPrecos;

public:
    Acao();
    Acao(const string& empresa, const string& codigo, float valor);

    void atualizarPreco(float newPrice);
    string getCodigo() const;
    
    string getEmpresa() const;

    float getPreco() const;

    const vector<float>& getHistorico() const;

    bool operator<(const Acao& other) const {
        return codigo < other.codigo;
    }
};

#endif