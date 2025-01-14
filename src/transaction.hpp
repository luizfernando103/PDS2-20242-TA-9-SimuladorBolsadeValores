#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>
#include "stock.hpp"

enum class TipoTransacao {
    BUY,
    SELL
};

class Transacao {
private:
    Acao acao;
    int quantidade;
    float preco;
    TipoTransacao tipo;
    std::time_t momento;

public:
    Transacao(const Acao& stock, int quant, float valor, TipoTransacao t);

    Acao getAcao() const;
    int getQuantidade() const;
    float getPreco() const;
    TipoTransacao getTipo() const;
    std::time_t getMomento() const;
    std::string toString() const;
};

#endif
