#include "transaction.hpp"
#include <sstream>
#include <iomanip>

Transacao::Transacao(const Acao& acao, int quant, float valor, TipoTransacao t)
    : acao(acao), quantidade(quant), preco(valor), tipo(t), momento(std::time(nullptr)) {}

Acao Transacao::getAcao() const {
    return acao;
}

int Transacao::getQuantidade() const {
    return quantidade;
}

float Transacao::getPreco() const {
    return preco;
}

TipoTransacao Transacao::getTipo() const {
    return tipo;
}

std::time_t Transacao::getMomento() const {
    return momento;
}

std::string Transacao::toString() const {
    std::ostringstream oss;
    oss << "Tipo: " << (tipo == TipoTransacao::BUY ? "Compra" : "Venda") << "\n"
        << "Ação: " << acao.getCodigo() << "\n"
        << "Quantidade: " << quantidade << "\n"
        << "Preço: " << std::fixed << std::setprecision(2) << preco << "\n"
        << "Data/Hora: " << std::asctime(std::localtime(&momento));
    return oss.str();
}
