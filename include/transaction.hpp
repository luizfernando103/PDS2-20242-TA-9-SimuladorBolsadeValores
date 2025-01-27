#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>
#include "stock.hpp"

enum class TipoTransacao {
    COMPRA,
    VENDA
};

class Transacao {
private:
    string usuario;
    Acao acao;
    int quantidade;
    float preco;
    TipoTransacao tipo;
    time_t momento;

public:
    Transacao(string user, Acao stock, int quant, float valor, TipoTransacao t);
    Transacao(string tempo, string usuario, string tipo, Acao stock, int quant);

    Acao getAcao() const;
    int getQuantidade() const;
    float getPreco() const;
    TipoTransacao getTipo() const;
    time_t getMomento() const;
    string toString() const;
};


#endif
